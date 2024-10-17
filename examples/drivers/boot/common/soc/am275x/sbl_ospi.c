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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdlib.h>
#include <drivers/device_manager/sciclient.h>
#include "FreeRTOS.h"
#include "task.h"
#include <drivers/bootloader.h>
#include "ti_drivers_config.h"
#include "ti_drivers_open_close.h"
#include "ti_board_open_close.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define SCRATCH_BUFFER_SIZE                             (0x1000U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle);
int32_t App_loadImages(Bootloader_LoadImageParams *bootLoadParams);
int32_t App_runCpus(Bootloader_LoadImageParams *bootLoadParams);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

uint8_t gScratchBuffer[SCRATCH_BUFFER_SIZE];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* call this API to stop the booting process and spin, do that you can connect
 * debugger, load symbols and then make the 'loop' variable as 0 to continue execution
 * with debugger connected.
 */
void loop_forever()
{
    volatile uint32_t loop = 1U;
    while(loop)
        ;
}

int32_t App_boardDriversOpen()
{
    int32_t status = SystemP_SUCCESS;

    gFlashHandle[CONFIG_FLASH_SBL] = NULL;

    gFlashConfig[CONFIG_FLASH_SBL].attrs->driverInstance = CONFIG_OSPI_SBL;

    gFlashHandle[CONFIG_FLASH_SBL] = Flash_open(CONFIG_FLASH_SBL, &gFlashParams[CONFIG_FLASH_SBL]);
    if(NULL == gFlashHandle[CONFIG_FLASH_SBL])
    {
        DebugP_logError("FLASH open failed for instance %d !!!\r\n", CONFIG_FLASH_SBL);
        status = SystemP_FAILURE;
    }

    return status;
}

void App_driversOpen()
{
    gOspiHandle[CONFIG_OSPI_SBL] = NULL;

    gOspiHandle[CONFIG_OSPI_SBL] = OSPI_open(CONFIG_OSPI_SBL, &gOspiParams[CONFIG_OSPI_SBL]);
    if(NULL == gOspiHandle[CONFIG_OSPI_SBL])
    {
        DebugP_logError("OSPI open failed for instance %d !!!\r\n", CONFIG_OSPI_SBL);
    }

    gUartHandle[CONFIG_UART_SBL] = NULL;

    gUartHandle[CONFIG_UART_SBL] = UART_open(CONFIG_UART_SBL, &gUartParams[CONFIG_UART_SBL]);
    if(NULL == gUartHandle[CONFIG_UART_SBL])
    {
        DebugP_logError("UART open failed for instance %d !!!\r\n", CONFIG_UART_SBL);
    }
}

void App_boardDriversClose()
{
    Flash_close(gFlashHandle[CONFIG_FLASH_SBL]);
    gFlashHandle[CONFIG_FLASH_SBL] = NULL;
}

void App_driversClose()
{
    OSPI_close(gOspiHandle[CONFIG_OSPI_SBL]);
    gOspiHandle[CONFIG_OSPI_SBL] = NULL;

    UART_close(gUartHandle[CONFIG_UART_SBL]);
    gUartHandle[CONFIG_UART_SBL] = NULL;
}

void App_bootMultipleCoreFlash()
{
    int32_t status = SystemP_SUCCESS;

    DebugP_log("\r\n");
    DebugP_log("Starting OSPI Bootloader ... \r\n");

    Module_clockSBLEnable();
    Module_clockSBLSetFrequency();

    App_driversOpen();
    Bootloader_profileAddProfilePoint("SBL Drivers_open");

    flashFixUpOspiBoot(gOspiHandle[CONFIG_OSPI_SBL], gFlashHandle[CONFIG_FLASH_SBL]);

    status = App_boardDriversOpen();
    DebugP_assertNoLog(status == SystemP_SUCCESS);
    Bootloader_profileAddProfilePoint("SBL Board_driversOpen");

    status = Sciclient_getVersionCheck(1);
    Bootloader_profileAddProfilePoint("Sciclient Get Version");

    if(SystemP_SUCCESS == status)
    {
        Bootloader_LoadImageParams bootArray[CONFIG_BOOTLOADER_NUM_INSTANCES];
        uint32_t imageSize = 0U;

        for(uint8_t inst = 0U; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
        {
            Bootloader_Params_init(&bootArray[inst].bootParams);
            Bootloader_BootImageInfo_init(&bootArray[inst].bootImageInfo);
            bootArray[inst].bootHandle = Bootloader_open(inst, &bootArray[inst].bootParams);
            bootArray[inst].loadStatus = BOOTLOADER_IMAGE_NOT_LOADED;

            if(bootArray[inst].bootHandle != NULL)
            {
                ((Bootloader_Config *)bootArray[inst].bootHandle)->scratchMemPtr = gScratchBuffer;
		    	status = App_loadImages(&bootArray[inst]);
            }

            if(SystemP_SUCCESS == status)
            {
                imageSize += Bootloader_getMulticoreImageSize(bootArray[inst].bootHandle);
            }
            else
            {
                DebugP_logError("App_loadImages failed !!!\r\n");
                break;
            }
        }

        Bootloader_profileUpdateAppimageSize(imageSize);
        Bootloader_profileUpdateMediaAndClk(BOOTLOADER_MEDIA_FLASH, OSPI_getInputClk(gOspiHandle[CONFIG_OSPI_SBL]));

        if(SystemP_SUCCESS == status)
		{
            /* Use CONFIG_UART_SBL (UART0) for SBL logs */
            DebugP_uartSetDrvIndex(CONFIG_UART_SBL);

			/* Print SBL log as Linux prints log to the same UART port */
			Bootloader_profilePrintProfileLog();
			DebugP_log("Image loading done, switching to application ...\r\n");
			DebugP_log("Starting linux and RTOS/Baremetal applications\r\n");
			UART_flushTxFifo(gUartHandle[CONFIG_UART_SBL]);

            /* Restore CONFIG_UART_APP (WKUP_UART) for application logs */
            DebugP_uartSetDrvIndex(CONFIG_UART_APP);
		}

         /* Deinitialise the flash and driver peripherial used by bootloader before starting other cores,
          * so that other systems can access and reinitialise it.
          */
        App_boardDriversClose();
        App_driversClose();

        if(SystemP_SUCCESS == status)
        {
            for(uint8_t inst = 0U; inst < CONFIG_BOOTLOADER_NUM_INSTANCES; inst++)
            {
		        status = App_runCpus(&bootArray[inst]);
                if(SystemP_SUCCESS != status)
                {
                    DebugP_logError("App_runCpus failed !!!\r\n");
                    break;
                }
            }
        }
    }

    if(status != SystemP_SUCCESS )
    {
        /* Use CONFIG_UART_SBL (UART0) for SBL logs */
        DebugP_uartSetDrvIndex(CONFIG_UART_SBL);

        /* Open UART to print failure log */
        gUartHandle[CONFIG_UART_SBL] = UART_open(CONFIG_UART_SBL, &gUartParams[CONFIG_UART_SBL]);
        if(NULL == gUartHandle[CONFIG_UART_SBL])
        {
            DebugP_logError("UART open failed for instance %d !!!\r\n", CONFIG_UART_SBL);
        }

        DebugP_log("SBL booting cores failed!!\r\n");

        UART_close(gUartHandle[CONFIG_UART_SBL]);
        gUartHandle[CONFIG_UART_SBL] = NULL;

        /* Restore CONFIG_UART_APP (WKUP_UART) for application logs */
        DebugP_uartSetDrvIndex(CONFIG_UART_APP);
    }
}

void sbl_ospi_main(void * args)
{
    App_bootMultipleCoreFlash();

    vTaskDelete(NULL);
}

static void flashFixUpOspiBoot(OSPI_Handle oHandle, Flash_Handle fHandle)
{
    OSPI_setProtocol(oHandle, OSPI_FLASH_PROTOCOL(1U, 1U, 8U, 0U));
    OSPI_enableSDR(oHandle);
    OSPI_clearDualOpCodeMode(oHandle);
    Flash_reset(fHandle);
    OSPI_setProtocol(oHandle, OSPI_FLASH_PROTOCOL(1U, 1U, 1U, 0U));
}
