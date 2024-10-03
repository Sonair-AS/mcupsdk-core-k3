/*
 *  Copyright (C) 2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file bootloader_mcelf.c
 *
 *  \brief Bootloader MCELF Driver API source file.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <kernel/dpl/SystemP.h>
#include <kernel/dpl/CacheP.h>
#include <drivers/bootloader.h>
#include <board/flash.h>
#if defined (DRV_VERSION_MMCSD_V0) || defined (DRV_VERSION_MMCSD_V1)
#include <drivers/bootloader/bootloader_mmcsd_raw.h>
#endif
#include <drivers/bootloader/soc/bootloader_soc.h>
#include <drivers/bootloader/bootloader_priv.h>
#include <string.h>
#include <drivers/device_manager/sciclient.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Flash data region base address */
#define FLASH_BASE_ADDRESS                    (CSL_FSS0_DAT_REG1_BASE)

/* MCELF note segment types */
#define SEGMENT_MAP_NOTE_TYPE                 (0xBBBB7777)
#define ENTRY_POINTS_NOTE_TYPE                (0xCCCC9999)
#define VENDOR_ID_NOTE_TYPE                   (0xAAAA5555)

#define BOOTLOADER_MCELF_META_DATA_SIZE_MAX   (ELF_HEADER_MAX_SIZE + \
                                               (ELF_MAX_SEGMENTS * ELF_P_HEADER_MAX_SIZE) \
                                               + ELF_NOTE_SEGMENT_MAX_SIZE)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    uint32_t noteSegmentSz;
    /**< Size of the note segment */
    uint32_t noteSegmentOffset;
    /**< Offset of the note segment */
    Bootloader_ELFNote *noteSegmentPtr;
    /**< Pointer to store address of note segment */
    uint8_t *noteSegmentMapPtr;
    /**< Pointer to the map type note segment */
} Bootloader_NoteSegInfo;

/* ========================================================================== */
/*                             Global Variables                               */
/* ========================================================================== */

/* Buffer to store the elf header, program header table(PHT) and note segment */
uint8_t gElfBuffer[BOOTLOADER_MCELF_META_DATA_SIZE_MAX];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Function to initialize CPU core */
static int32_t Bootloader_initCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo);

/* Function to parse the note segment info*/
static int32_t Bootloader_parseNoteSegment(Bootloader_Handle handle,
                                    Bootloader_BootImageInfo *bootImageInfo,
                                    Bootloader_NoteSegInfo *noteSegInfo,
                                    uint8_t elfClass);

/* Functions to call TISCI APIs for authentication */
static int32_t Bootloader_authInit(uint32_t certLoadAddr);
static int32_t Bootloader_authUpdate(uint32_t segAddr, uint32_t segSize, bool final_pkt, uint64_t dst);
static int32_t Bootloader_authFinish();

/* ========================================================================== */
/*                             Function Definitions                           */
/* ========================================================================== */

int32_t Bootloader_parseAndLoadMultiCoreELF(Bootloader_Handle handle, Bootloader_BootImageInfo *bootImageInfo)
{
    int32_t status = SystemP_SUCCESS;

    uint32_t numSegments = 0U;

    uint8_t x509Header[4U];
    uint32_t certLoadAddr = 0xFFFFFFFFU;
    uint32_t certLen = 0U;

    uint8_t elfClass = ELFCLASS_32;

    Bootloader_ELFH32 *elfPtr32 = NULL;
    Bootloader_ELFPH32 *elfPhdrPtr32 = NULL;

    Bootloader_ELFH64 *elfPtr64 = NULL;
    Bootloader_ELFPH64 *elfPhdrPtr64 = NULL;

    Bootloader_NoteSegInfo noteSegInfo =
    {
        .noteSegmentSz = 0U,
        .noteSegmentOffset = 0U,
        .noteSegmentPtr = NULL,
        .noteSegmentMapPtr = NULL,
    };

    /* Array to check if core is initialized */
    uint8_t initCpuDone[CSL_CORE_ID_MAX] = {0U};

    Bootloader_Config *config = (Bootloader_Config *)handle;

    if(config->fxns->imgReadFxn == NULL || config->fxns->imgSeekFxn == NULL)
    {
        status = SystemP_FAILURE;
    }

    if(status == SystemP_SUCCESS)
    {
        /* Read the x509 certificate header */
        config->fxns->imgReadFxn(x509Header, 4U, config->args);
        certLen = Bootloader_getX509CertLen(x509Header);

#if !defined (SKIP_AUTH_FLOW)
        if(Bootloader_socIsAuthRequired() == (uint32_t)1U)
        {
            if(config->bootMedia == BOOTLOADER_MEDIA_FLASH)
            {
                Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)(config->args);
                if(flashArgs->flashType == CONFIG_FLASH_TYPE_SERIAL_NOR)
                {
                    certLoadAddr = FLASH_BASE_ADDRESS + flashArgs->appImageOffset;

                    /* Enable OSPI Phy if configured to do so*/
                    flashArgs->enablePhyPipeline = TRUE;
                    status = config->fxns->imgCustomFxn(config->args);
                }
            }

            /* Check if the certificate length is within valid range */
            if((certLen > (uint32_t)0x100U) && (certLen < (uint32_t)0x800U) && status == SystemP_SUCCESS)
            {
                status = Bootloader_authInit(certLoadAddr);
            }
            else
            {
                status = SystemP_FAILURE;
            }

            if(status == SystemP_SUCCESS)
            {
                config->fxns->imgSeekFxn(certLen, config->args);
                /* Read the ELF metadata from the bootmedia */
                status = config->fxns->imgReadFxn(gElfBuffer, BOOTLOADER_MCELF_META_DATA_SIZE_MAX, config->args);

                char elfStr[] = { 0x7F, 'E', 'L', 'F' };
                if(memcmp(elfStr, gElfBuffer, 4U) != 0U)
                {
                    status = SystemP_FAILURE;
                }
                else
                {
                    elfClass = gElfBuffer[ELFCLASS_IDX];
                    if(elfClass == ELFCLASS_64)
                    {
                        elfPtr64 = (Bootloader_ELFH64 *)gElfBuffer;
                        numSegments = elfPtr64->ePhnum;

                        /* Check if number of PHT entries are <= MAX */
                        if (numSegments > ELF_MAX_SEGMENTS)
                        {
                            status = SystemP_FAILURE;
                        }

                        if(status == SystemP_SUCCESS)
                        {
                            elfPhdrPtr64 = (Bootloader_ELFPH64*) &gElfBuffer[elfPtr64->ePhoff];

                            /* Note segment is always first */
                            noteSegInfo.noteSegmentSz = elfPhdrPtr64[0U].filesz;
                            noteSegInfo.noteSegmentPtr = (Bootloader_ELFNote *) &gElfBuffer[elfPhdrPtr64[0U].offset];
                            noteSegInfo.noteSegmentOffset = elfPhdrPtr64[0U].offset;
                        }
                    }
                    else if(elfClass == ELFCLASS_32)
                    {
                        elfPtr32 = (Bootloader_ELFH32 *)gElfBuffer;
                        numSegments = elfPtr32->ePhnum;

                        /* Check if number of PHT entries are <= MAX */
                        if (numSegments > ELF_MAX_SEGMENTS)
                        {
                            status = SystemP_FAILURE;
                        }

                        if(status == SystemP_SUCCESS)
                        {
                            elfPhdrPtr32 = (Bootloader_ELFPH32 *) &gElfBuffer[elfPtr32->ePhoff];

                            /* Note segment is always first */
                            noteSegInfo.noteSegmentSz = elfPhdrPtr32[0U].filesz;
                            noteSegInfo.noteSegmentPtr = (Bootloader_ELFNote *) &gElfBuffer[elfPhdrPtr32[0U].offset];
                            noteSegInfo.noteSegmentOffset = elfPhdrPtr32[0U].offset;
                        }
                    }
                    else
                    {
                        status = SystemP_FAILURE;
                    }

                    if(status == SystemP_SUCCESS)
                    {
                        /* Parse the note segment */
                        status = Bootloader_parseNoteSegment(handle, bootImageInfo, &noteSegInfo, elfClass);
                    }
                }
            }

            if(status == SystemP_SUCCESS)
            {
                uint32_t i = 1U, cslCoreId = 0U, mcelfCoreId = 0U, imgAddr;
                bool isFinalPkt = FALSE;

                if(config->bootMedia == BOOTLOADER_MEDIA_FLASH)
                {
                    Bootloader_FlashArgs *flashArgs = (Bootloader_FlashArgs *)(config->args);
                    /* Enable OSPI Phy if configured to do so*/
                    flashArgs->enablePhyPipeline = TRUE;
                    status = config->fxns->imgCustomFxn(config->args);
                    imgAddr = (uint32_t) FLASH_BASE_ADDRESS + flashArgs->appImageOffset + certLen;
                }

                if(elfClass == ELFCLASS_32)
                {
                    /* Do auth update for the elf header, PHT and note segment */
                    status = Bootloader_authUpdate((uint32_t) &gElfBuffer[0], \
                                        (uint32_t) elfPtr32->eEhsize + \
                                        (elfPtr32->ePhnum * elfPtr32->ePhentsize) + \
                                            elfPhdrPtr32[0].filesz, \
                                            FALSE, \
                                            (uint64_t) &gElfBuffer[0U]);

                    if(status == SystemP_SUCCESS)
                    {
                        /* Loop over the segments and do auth update */
                        for(i = 1U; i < elfPtr32->ePhnum; i++)
                        {
                            mcelfCoreId = *(noteSegInfo.noteSegmentMapPtr + (i - 1U));
                            cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);

                            if(!initCpuDone[cslCoreId])
                            {
                                status = Bootloader_initCpu(handle, &bootImageInfo->cpuInfo[cslCoreId]);
                                initCpuDone[cslCoreId] = 1U;
                            }

                            if (status == SystemP_SUCCESS)
                            {
                                if(elfPhdrPtr32[i].filesz != 0U && elfPhdrPtr32[i].type == PT_LOAD)
                                {
                                    uint32_t addr = Bootloader_socTranslateSectionAddr(cslCoreId, elfPhdrPtr32[i].vaddr);

                                    /* Add check for SBL reserved memory */
                                    Bootloader_resMemSections *resMem;
                                    uint32_t resSectionCnt, start, end;
                                    resMem = Bootloader_socGetSBLMem();
                                    for (resSectionCnt = 0U; resSectionCnt < resMem->numSections; resSectionCnt++)
                                    {
                                        start = resMem->memSection[resSectionCnt].memStart;
                                        end = resMem->memSection[resSectionCnt].memEnd;
                                        if((addr > start) && (addr < end))
                                        {
                                            status = SystemP_FAILURE;
                                            DebugP_log("Application image has a load address (0x%08X) in the SBL reserved memory range!!\r\n", addr);
                                            break;
                                        }
                                    }

                                    if (status == SystemP_SUCCESS)
                                    {
                                        if (i == elfPtr32->ePhnum-1)
                                        {
                                            isFinalPkt = TRUE;
                                        }
                                        status = Bootloader_authUpdate( imgAddr + elfPhdrPtr32[i].offset, \
                                                                (uint32_t) elfPhdrPtr32[i].filesz, \
                                                                isFinalPkt, \
                                                                (uint64_t) addr);

                                        ((Bootloader_Config *)handle)->bootImageSize += elfPhdrPtr32[i].filesz;
                                    }
                                }
                                else
                                {
                                    /* NO LOAD segment, do nothing */
                                }
                            }

                            if (status != SystemP_SUCCESS)
                            {
                                break;
                            }
                        }
                    }
                }
                else if(elfClass == ELFCLASS_64)
                {
                    /* Do auth update for the elf header, PHT and note segment */
                    status = Bootloader_authUpdate((uint32_t) &gElfBuffer[0], \
                                        (uint32_t) elfPtr64->eEhsize + \
                                        (elfPtr64->ePhnum * elfPtr64->ePhentsize) + \
                                            elfPhdrPtr64[0].filesz, \
                                            FALSE, \
                                            (uint64_t) &gElfBuffer[0U]);
                    if(status == SystemP_SUCCESS)
                    {
                        /* Loop over the segments and do auth update */
                        for(i = 1; i < elfPtr64->ePhnum; i++)
                        {
                            mcelfCoreId = *(noteSegInfo.noteSegmentMapPtr + (i - 1U));
                            cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);

                            if(!initCpuDone[cslCoreId])
                            {
                                status = Bootloader_initCpu(handle, &bootImageInfo->cpuInfo[cslCoreId]);
                                initCpuDone[cslCoreId] = 1;
                            }

                            if(elfPhdrPtr64[i].filesz != 0U && elfPhdrPtr64[i].type == PT_LOAD)
                            {
                                uint32_t addr = Bootloader_socTranslateSectionAddr(cslCoreId, elfPhdrPtr64[i].vaddr);

                                /* Add check for SBL reserved memory */
                                Bootloader_resMemSections *resMem;
                                uint32_t resSectionCnt, start, end;
                                resMem = Bootloader_socGetSBLMem();
                                for (resSectionCnt = 0U; resSectionCnt < resMem->numSections; resSectionCnt++)
                                {
                                    start = resMem->memSection[resSectionCnt].memStart;
                                    end = resMem->memSection[resSectionCnt].memEnd;
                                    if((addr > start) && (addr < end))
                                    {
                                        status = SystemP_FAILURE;
                                        DebugP_log("Application image has a load address (0x%08X) in the SBL reserved memory range!!\r\n", addr);
                                        break;
                                    }
                                }

                                if (status == SystemP_SUCCESS)
                                {
                                    if (i == elfPtr64->ePhnum-1)
                                    {
                                        isFinalPkt = TRUE;
                                    }
                                    status = Bootloader_authUpdate( imgAddr + elfPhdrPtr64[i].offset, \
                                                            (uint32_t) elfPhdrPtr64[i].filesz, \
                                                            isFinalPkt, \
                                                            (uint64_t) addr);
                                    ((Bootloader_Config *)handle)->bootImageSize += elfPhdrPtr64[i].filesz;
                                }
                            }
                            else
                            {
                                /* NO LOAD segment, do nothing */
                            }

                            if (status != SystemP_SUCCESS)
                            {
                                break;
                            }
                        }
                    }
                }
            }

            if(status == SystemP_SUCCESS)
            {
                status = Bootloader_authFinish();
            }

        }
#else
        /* Add for GP device */
#endif
    }
    return status;
}

int32_t Bootloader_bootCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;

    status = Bootloader_initCpu(handle, cpuInfo);

    if(status == SystemP_SUCCESS)
    {
        status = Bootloader_runCpu(handle, cpuInfo);
    }

    return status;
}

/* This API should only be called after the bootimage is parsed */
uint32_t Bootloader_isCorePresent(Bootloader_Handle handle, uint32_t cslCoreId)
{
    uint32_t retVal = 0U;

    if(handle != NULL)
    {
        Bootloader_Config *config = (Bootloader_Config *)handle;
        if((config->coresPresentMap & ((uint32_t)1 << cslCoreId)) != (uint32_t)0)
        {
            retVal = 1U;
        }
    }

    return retVal;
}

void Bootloader_CpuInfo_init(Bootloader_CpuInfo *cpuInfo)
{
    cpuInfo->cpuId = CSL_CORE_ID_MAX;
    cpuInfo->clkHz = 0U;
    cpuInfo->entryPoint = (uintptr_t)BOOTLOADER_INVALID_ID;
    cpuInfo->smpEnable  = false;
}

void Bootloader_BootImageInfo_init(Bootloader_BootImageInfo *bootImageInfo)
{
    uint16_t i;

    for(i=0U; i<(uint16_t)CSL_CORE_ID_MAX; i++)
    {
        Bootloader_CpuInfo_init(&bootImageInfo->cpuInfo[i]);
        bootImageInfo->cpuInfo[i].cpuId = (uint32_t)i;
        bootImageInfo->cpuInfo[i].clkHz = Bootloader_socCpuGetClkDefault((uint32_t)i);
    }
}

static int32_t Bootloader_initCpu(Bootloader_Handle handle, Bootloader_CpuInfo *cpuInfo)
{
    int32_t status = SystemP_SUCCESS;
    uint8_t numOfCores;
    uint8_t core;

    uint32_t *selfCpuList  = Bootloader_socGetSelfCpuList();

    if(cpuInfo->smpEnable == true)
    {
        numOfCores = FREERTOS_SMP_NO_OF_CORES;
    }
    else
    {
        numOfCores = 1U;
    }

    for( core = 0U; core < numOfCores; core ++)
    {
        if(cpuInfo->cpuId == selfCpuList[0U])
        {
            status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

            if(SystemP_SUCCESS == status)
            {
                uintptr_t entryPoint = cpuInfo->entryPoint;

                if( cpuInfo->entryPoint == BOOTLOADER_INVALID_ID)
                {
                    entryPoint = 0U;
                }
                status = Bootloader_socCpuSetEntryPoint(cpuInfo->cpuId, entryPoint);
            }

            if(SystemP_SUCCESS == status)
            {
                status = Bootloader_socMemInitCpu(cpuInfo->cpuId);
            }
        }
        else
        {
            status = Bootloader_socCpuRequest(cpuInfo->cpuId);

            if(SystemP_SUCCESS == status)
            {
                status = Bootloader_socCpuSetClock(cpuInfo->cpuId, cpuInfo->clkHz);

                if(SystemP_SUCCESS == status)
                {
                    Bootloader_Config *config = (Bootloader_Config *)handle;
                    status = Bootloader_socCpuPowerOnReset(cpuInfo->cpuId,config->socCoreOpMode);
                }
            }
        }

        if(SystemP_SUCCESS != status)
        {
            break;
        }

        cpuInfo ++;
    }

    return status;
}

static int32_t Bootloader_parseNoteSegment(Bootloader_Handle handle,
                                    Bootloader_BootImageInfo *bootImageInfo,
                                    Bootloader_NoteSegInfo *noteSegInfo,
                                    uint8_t elfClass)
{
    int32_t status = SystemP_SUCCESS;
    uint32_t idx = 0U, sgMpIdx = 0U, alignSize = 4U, mcelfCoreId = 0U, cslCoreId = 0U;
    uint32_t noteSegmentStart = 0U;
    uint32_t numEntries = 0U, i =0U;
    Bootloader_CpuInfo *cpuInfo = NULL;

    Bootloader_Config *config = (Bootloader_Config *)handle;

    noteSegmentStart = (uint32_t) &noteSegInfo->noteSegmentPtr->namesz;

    while(idx < noteSegInfo->noteSegmentSz)
    {
        /* Read the type */
        idx += (ELF_NOTE_NAMESZ_SIZE + ELF_NOTE_DESCSZ_SIZE + ELF_NOTE_TYPE_SIZE);
        if(noteSegInfo->noteSegmentPtr->type == ENTRY_POINTS_NOTE_TYPE)
        {
            idx += noteSegInfo->noteSegmentPtr->namesz;
            if(noteSegInfo->noteSegmentPtr->namesz % alignSize != 0U)
            {
                idx += (alignSize - (noteSegInfo->noteSegmentPtr->namesz % alignSize));
            }

            if(elfClass == ELFCLASS_32)
            {
                numEntries = noteSegInfo->noteSegmentPtr->descsz / 8U;
                for (i = 0U; i < numEntries; i++)
                {
                    mcelfCoreId = gElfBuffer[noteSegInfo->noteSegmentOffset + idx];
                    cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);
                    cpuInfo = &bootImageInfo->cpuInfo[cslCoreId];

                    cpuInfo->entryPoint = gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 4U] | \
                                            (gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 5U] << 8U) | \
                                            (gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 6U] << 16U)| \
                                            (gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 7U] << 24U);

                    if (Bootloader_socIsSmpEnable(mcelfCoreId) == true)
                    {
                        cpuInfo->smpEnable = true;
                    }

                    config->coresPresentMap |= ((uint32_t)1U << cslCoreId);

                    idx += 8U;
                }
            }
            else if(elfClass == ELFCLASS_64)
            {
                numEntries = noteSegInfo->noteSegmentPtr->descsz / 12U;
                for (i = 0U; i < numEntries; i++)
                {
                    mcelfCoreId = gElfBuffer[noteSegInfo->noteSegmentOffset + idx];
                    cslCoreId = Bootloader_socElfToCslCoreId(mcelfCoreId);
                    cpuInfo = &bootImageInfo->cpuInfo[cslCoreId];

                    cpuInfo->entryPoint = gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 4U] | \
                                            (gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 5U] << 8U) | \
                                            (gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 6U] << 16U) | \
                                            (gElfBuffer[noteSegInfo->noteSegmentOffset + idx + 7U] << 24U);

                    if (Bootloader_socIsSmpEnable(mcelfCoreId) == true)
                    {
                        cpuInfo->smpEnable = true;
                    }

                    config->coresPresentMap |= ((uint32_t)1U << cslCoreId);

                    idx += 12U;
                }
            }

            break;
        }
        else if(noteSegInfo->noteSegmentPtr->type == SEGMENT_MAP_NOTE_TYPE)
        {
            /* Start of values in segment map */
            sgMpIdx = idx + noteSegInfo->noteSegmentPtr->namesz;
            noteSegInfo->noteSegmentMapPtr = &gElfBuffer[noteSegInfo->noteSegmentOffset + sgMpIdx];

            idx += noteSegInfo->noteSegmentPtr->namesz + noteSegInfo->noteSegmentPtr->descsz;
            if(noteSegInfo->noteSegmentPtr->namesz % alignSize != 0U)
            {
                idx += (alignSize - (noteSegInfo->noteSegmentPtr->namesz % alignSize));
            }

            if(noteSegInfo->noteSegmentPtr->descsz % alignSize != 0U)
            {
                idx += (alignSize - (noteSegInfo->noteSegmentPtr->descsz % alignSize));
            }

            noteSegInfo->noteSegmentPtr = (Bootloader_ELFNote *)(noteSegmentStart + idx);
        }
        else if(noteSegInfo->noteSegmentPtr->type == VENDOR_ID_NOTE_TYPE)
        {
            idx += noteSegInfo->noteSegmentPtr->namesz + noteSegInfo->noteSegmentPtr->descsz;
            if(noteSegInfo->noteSegmentPtr->namesz % alignSize != 0U)
            {
                idx += (alignSize - (noteSegInfo->noteSegmentPtr->namesz % alignSize));
            }
            if(noteSegInfo->noteSegmentPtr->descsz % alignSize != 0U)
            {
                idx += (alignSize - (noteSegInfo->noteSegmentPtr->descsz % alignSize));
            }

            noteSegInfo->noteSegmentPtr = (Bootloader_ELFNote *)(noteSegmentStart + idx);
        }
        else
        {
            status = SystemP_FAILURE;
        }
    }

    if(sgMpIdx == 0U)
    {
        status = SystemP_FAILURE;
    }
    else
    {
        status = SystemP_SUCCESS;
    }

    return status;
}

static int32_t Bootloader_authInit(uint32_t certLoadAddr)
{
    int32_t status, authStatus = SystemP_FAILURE;
    struct tisci_security_mesg_mcelf_init_req request;
    struct tisci_security_mesg_mcelf_init_resp response;

    Sciclient_ReqPrm_t  reqParam = {0U};
    Sciclient_RespPrm_t respParam = {0U};

    request.hdr.type = TISCI_MSG_MMELF_PROC_AUTH_BOOT_INIT;
    request.hdr.seq = 0U;
    request.hdr.flags = TISCI_MSG_FLAG_AOP;
    request.certificate_address_hi = 0U ;
    request.certificate_address_lo = certLoadAddr;

    reqParam.messageType    = (uint16_t) TISCI_MSG_MMELF_PROC_AUTH_BOOT_INIT;
    reqParam.flags          = (uint32_t) TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload    = (const uint8_t *) &request;
    reqParam.reqPayloadSize = (uint32_t) sizeof (request);
    reqParam.timeout        = (uint32_t) SystemP_WAIT_FOREVER;

    respParam.flags           = (uint32_t) 0U; /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t)  sizeof (response);

    status = Sciclient_service(&reqParam, &respParam);
    if ((status == SystemP_SUCCESS)  && (respParam.flags == TISCI_MSG_FLAG_ACK))
    {
        authStatus = SystemP_SUCCESS;
    }
    else
    {
        authStatus = SystemP_FAILURE;
    }

    return authStatus;
}

static int32_t Bootloader_authUpdate(uint32_t segAddr, uint32_t segSize, bool final_pkt, uint64_t dst)
{
    int32_t status;
    struct tisci_security_mesg_mcelf_update_req request;
    struct tisci_security_mesg_mcelf_update_resp response;

    Sciclient_ReqPrm_t  reqParam = {0U};
    Sciclient_RespPrm_t respParam = {0U};

    request.hdr.type = TISCI_MSG_MMELF_PROC_AUTH_BOOT_UPDATE;
    request.hdr.seq = 0U;
    request.hdr.flags = TISCI_MSG_FLAG_AOP;
    request.address_hi = 0U;
    request.address_lo = segAddr;
    request.segment_size = segSize;
    request.final_pkt = final_pkt;
    request.dest_address = dst;

    reqParam.messageType = (uint16_t)TISCI_MSG_MMELF_PROC_AUTH_BOOT_UPDATE;
    reqParam.flags = (uint32_t)TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload = (const uint8_t *)&request;
    reqParam.reqPayloadSize = (uint32_t)sizeof(request);
    reqParam.timeout = (uint32_t)SystemP_WAIT_FOREVER;


    respParam.flags = (uint32_t)0U; /* Populated by the API */
    respParam.pRespPayload = (uint8_t *)&response;
    respParam.respPayloadSize = (uint32_t)sizeof(response);

    status = Sciclient_service(&reqParam, &respParam);

    if ((status == SystemP_SUCCESS) && (respParam.flags == TISCI_MSG_FLAG_ACK))
    {
        status = SystemP_SUCCESS;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

static int32_t Bootloader_authFinish()
{
    int32_t status;
    struct tisci_security_mesg_mcelf_finish_req request;
    struct tisci_security_mesg_mcelf_finish_resp response;

    Sciclient_ReqPrm_t  reqParam = {0U};
    Sciclient_RespPrm_t respParam = {0U};

    request.hdr.type = TISCI_MSG_MMELF_PROC_AUTH_BOOT_FINISH;
    request.hdr.seq = 0U;
    request.hdr.flags = TISCI_MSG_FLAG_AOP;

    reqParam.messageType    = (uint16_t) TISCI_MSG_MMELF_PROC_AUTH_BOOT_FINISH;
    reqParam.flags          = (uint32_t) TISCI_MSG_FLAG_AOP;
    reqParam.pReqPayload    = (const uint8_t *) &request;
    reqParam.reqPayloadSize = (uint32_t) sizeof (request);
    reqParam.timeout        = (uint32_t) SystemP_WAIT_FOREVER;;

    respParam.flags           = (uint32_t) 0U;   /* Populated by the API */
    respParam.pRespPayload    = (uint8_t *) &response;
    respParam.respPayloadSize = (uint32_t)  sizeof (response);

    status = Sciclient_service(&reqParam, &respParam);
    if ((status == SystemP_SUCCESS)  && (respParam.flags == TISCI_MSG_FLAG_ACK))
    {
        status = SystemP_SUCCESS;
    }
    else
    {
        status = SystemP_FAILURE;
    }

    return status;
}

