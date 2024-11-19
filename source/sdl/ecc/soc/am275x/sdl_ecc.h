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
 * @file  sdl_ecc.h
 *
 * @brief
 *  Header file contains enumerations, structure definitions and function
 *  declarations for SDL ECC interface.
 *  ============================================================================
 */

#ifndef INCLUDE_SDL_SOC_ECC_H_
#define INCLUDE_SDL_SOC_ECC_H_

#include <stdint.h>
#include <stdbool.h>

#include <sdl/ecc/sdl_ip_ecc.h>

#include <sdl/esm/sdl_esm.h>
#include <sdl/include/am275x/soc_config.h>
#include <sdl/include/am275x/sdlr_soc_baseaddress.h>
#include <sdl/include/am275x/sdlr_soc_ecc_aggr.h>
#include <sdl/esm/soc/sdl_esm_soc.h>                             
#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @addtogroup SDL_ECC_AGGR_ENUM
 *  @{
 *
 */

/** ---------------------------------------------------------------------------
 * \brief This enumerator indicate ECC memory type
 *
 * ----------------------------------------------------------------------------
 */
typedef uint32_t SDL_ECC_MemType;

#define SDL_C7X256V1_ECC_AGGR                                                                                                   (0U)
#define SDL_WKUP_VTM0_K3VTM_N16FFC_ECCAGGR                                                                                      (1U)
#define SDL_PSRAMECC0_PSRAM256X32E_ECC_AGGR                                                                                     (2U)
#define SDL_IDOM0_PULSAR_PLL_ECC_AGGR10                                                                                         (3U)
#define SDL_IDOM0_PULSAR_PLL_ECC_AGGR8                                                                                          (4U)
#define SDL_MSRAM_1MB4_MSRAM32KX256E_ECC_AGGR                                                                                   (5U)
#define SDL_WKUP_R5FSS0_PULSAR_UL_CPU0_ECC_AGGR                                                                                 (6U)
#define SDL_FSS1_FSS_HB_WRAP_ECC_AGGR                                                                                           (7U)
#define SDL_FSS1_FSS_OSPI0_OSPI_WRAP_ECC_AGGR                                                                                   (8U)
#define SDL_FSS1_FSS_OSPI1_OSPI_WRAP_ECC_AGGR                                                                                   (9U)
#define SDL_ECC_AGGR3_AM275_R5_MAIN_IP_ECC_AGGR                                                                                 (10U)
#define SDL_SA3_SS0_SA3SS_AM62A_DMSS_ECCAGGR                                                                                    (11U)
#define SDL_SA3_SS0_SA3SS_AM62A_SA_UL_ECC_AGGR                                                                                  (12U)
#define SDL_MSRAM_1MB2_MSRAM32KX256E_ECC_AGGR                                                                                   (13U)
#define SDL_MSRAM_1MB1_MSRAM32KX256E_ECC_AGGR                                                                                   (14U)
#define SDL_C7X256V0_ECC_AGGR                                                                                                   (15U)
#define SDL_MSRAM_1MB0_MSRAM32KX256E_ECC_AGGR                                                                                   (16U)
#define SDL_CPSW0_CPSW_3GUSS_AM62L_CORE_ECC_CPSW_ECC_AGGR                                                                       (17U)
#define SDL_MMCSD0_EMMCSD8SS_ECC_AGGR_TXMEM                                                                                     (18U)
#define SDL_MMCSD0_EMMCSD8SS_ECC_AGGR_RXMEM                                                                                     (19U)
#define SDL_PDMA4_AM275_PDMA_SPI1_ECCAGGR                                                                                       (20U)
#define SDL_ECC_AGGR0_AM275_SEC_HSM_ECC_AGGR                                                                                    (21U)
#define SDL_IDOM0_MAIN_PLL_ECC_AGGR6_IDOM0_MAIN_PLL_ECC_AGGR                                                                    (22U)
#define SDL_IDOM0_MAIN_PLL_ECC_AGGR4_IDOM0_MAIN_PLL_ECC_AGGR                                                                    (23U)
#define SDL_SMS0_SMS_HSM_ECC                                                                                                    (24U)
#define SDL_SMS0_SMS_TIFS_ECC                                                                                                   (25U)
#define SDL_FSS0_FSS_OF_UL_FSAS_FOTA_FSS_OF_UL_FOTA_ACC_ECC_AGGR                                                                (26U)
#define SDL_FSS0_FSS_OF_UL_OSPI0_OSPI_WRAP_ECC_AGGR                                                                             (27U)
#define SDL_MSRAM_1MB3_MSRAM32KX256E_ECC_AGGR                                                                                   (28U)
#define SDL_USB0_USB2SS_16FFC_USB2SS_CORE_ECC_AGGR                                                                              (29U)
#define SDL_WKUP_PSRAMECC_8K0_PSRAM8KX32E_ECC_AGGR                                                                              (30U)
#define SDL_MLB0_MLBSS2P0_MLBDIM_WRAP_ECC_AGGR                                                                                  (31U)
#define SDL_MCAN0_MCANSS_MSGMEM_WRAP_ECC_AGGR                                                                                   (32U)
#define SDL_ADC12FCC0_ADC12FC_16FFC_ADC12_CORE_FIFO_RAM_ECC_AGGR                                                                (33U)
#define SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR                                                                                      (34U)
#define SDL_R5FSS0_PULSAR_SL_CPU1_ECC_AGGR                                                                                      (35U)
#define SDL_R5FSS1_PULSAR_SL_CPU0_ECC_AGGR                                                                                      (36U)
#define SDL_R5FSS1_PULSAR_SL_CPU1_ECC_AGGR                                                                                      (37U)
#define SDL_WKUP_ECC_AGGR1_AM275_DM_MCU_ECC_AGGR                                                                                (38U)
#define SDL_WKUP_ECC_AGGR0_AM275_DM_DM_ECC_AGGR                                                                                 (39U)
#define SDL_PDMA1_SAM62_PDMA_UART_ECCAGGR                                                                                       (40U)
#define SDL_MSRAM_1MB5_MSRAM32KX256E_ECC_AGGR                                                                                   (41U)
#define SDL_PDMA0_SAM67_PDMA_SPI_ECCAGGR                                                                                        (42U)
#define SDL_IDOM1_MAIN_PLL_ECC_AGGR5_IDOM1_MAIN_PLL_ECC_AGGR                                                                    (43U)
#define SDL_IDOM1_MAIN_PLL_ECC_AGGR7_IDOM1_MAIN_PLL_ECC_AGGR                                                                    (44U)
#define SDL_MCAN3_MCANSS_MSGMEM_WRAP_ECC_AGGR                                                                                   (45U)
#define SDL_MCAN2_MCANSS_MSGMEM_WRAP_ECC_AGGR                                                                                   (46U)
#define SDL_MCAN1_MCANSS_MSGMEM_WRAP_ECC_AGGR                                                                                   (47U)
#define SDL_DMASS0_ECC_AGGR_0                                                                                                   (48U)
#define SDL_MCAN4_MCANSS_MSGMEM_WRAP_ECC_AGGR                                                                                   (49U)
#define SDL_IDOM1_PULSAR_PLL_ECC_AGGR9                                                                                          (50U)
#define SDL_IDOM1_PULSAR_PLL_ECC_AGGR11                                                                                         (51U)
#define SDL_WKUP_ECC_AGGR2_AM275_WKUP_SAFE_ECC_AGGR                                                                             (52U)
#define SDL_WKUP_PSRAM2KX32E0_PSRAM2KX32E_ECC_AGGR                                                                              (53U)
#define SDL_ECC_AGGR2_AM275_MAIN_SYS_IP_ECC_AGGR                                                                                (54U)
#define SDL_ECC_MEMTYPE_MAX                                                                                         		(SDL_ECC_AGGR2_AM275_MAIN_SYS_IP_ECC_AGGR + 1U)

/** \brief Select memory subtype ATCM0 BANK0 */
#define SDL_ECC_R5F_MEM_SUBTYPE_ATCM0_BANK0_VECTOR_ID                                                                       (SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_PULSAR_SL_ATCM0_BANK0_RAM_ID)
/** \brief Select memory subtype ATCM0 BANK1 */
#define SDL_ECC_R5F_MEM_SUBTYPE_ATCM0_BANK1_VECTOR_ID                                                                       (SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_PULSAR_SL_ATCM0_BANK1_RAM_ID)
/** \brief Select memory subtype B0TCM0 BANK0 */
#define SDL_ECC_R5F_MEM_SUBTYPE_B0TCM0_BANK0_VECTOR_ID                                                                      (SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_PULSAR_SL_B0TCM0_BANK0_RAM_ID)
/** \brief Select memory subtype B0TCM0 BANK1 */
#define SDL_ECC_R5F_MEM_SUBTYPE_B0TCM0_BANK1_VECTOR_ID                                                                      (SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_PULSAR_SL_B0TCM0_BANK1_RAM_ID)
/** \brief Select memory subtype B1TCM0 BANK0 */
#define SDL_ECC_R5F_MEM_SUBTYPE_B1TCM0_BANK0_VECTOR_ID                                                                      (SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_PULSAR_SL_B1TCM0_BANK0_RAM_ID)
/** \brief Select memory subtype B1TCM0 BANK1 */
#define SDL_ECC_R5F_MEM_SUBTYPE_B1TCM0_BANK1_VECTOR_ID                                                                      (SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_PULSAR_SL_B1TCM0_BANK1_RAM_ID)
/** \brief Select memory subtype VIM RAM */
#define SDL_ECC_R5F_MEM_SUBTYPE_KS_VIM_RAM_VECTOR_ID                                                                        (SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR_CPU0_KS_VIM_RAMECC_RAM_ID)

/** @} */

#define SDL_ECC_MEM_TYPE                         SDL_R5FSS0_PULSAR_SL_CPU0_ECC_AGGR

/** ---------------------------------------------------------------------------
 * \brief This structure defines the elements of ECC Group checker for Interconnect
 * SDL_ECC_RamIdType
 * ----------------------------------------------------------------------------
 */
typedef struct SDL_GrpChkConfig_s
{
    uint32_t checkerType;
    uint32_t dataWidth;
    /**< Length of memory bus covered in bits */
}  SDL_GrpChkConfig_t;

#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* INCLUDE_SDL_SOC_ECC_H_*/
