/*
 * Copyright (C) 2022 Texas Instruments Incorporated
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \defgroup DRV_PINMUX_MODULE APIs for PINMUX
 *  \ingroup DRV_MODULE
 *
 *  This module contains APIs to program and use the pinmux module.
 *
 *  @{
 */

/**
 *  \file pinmux.h
 *
 *  \brief PINMUX Driver API/interface file.
 *
 * \brief  This file contains pad configure register offsets and bit-field
 *         value macros for different configurations,
 *
 *           BIT[21]        TXDISABLE       disable the pin's output driver
 *           BIT[18]        RXACTIVE        enable the pin's input buffer (typically kept enabled)
 *           BIT[17]        PULLTYPESEL     set the iternal resistor pull direction high or low (if enabled)
 *           BIT[16]        PULLUDEN        internal resistor disable (0 = enabled / 1 = disabled)
 *           BIT[3:0]       MUXMODE         select the desired function on the given pin
 */

#ifndef PINMUX_AM275X_H_
#define PINMUX_AM275X_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Macros & Typedefs                              */
/* ========================================================================== */

/**
 *  \anchor Pinmux_DomainId_t
 *  \name Pinmux Domain ID
 *  @{
 */
#define PINMUX_DOMAIN_ID_MAIN          (0U)
#define PINMUX_DOMAIN_ID_MCU           (1U)
/** @} */

/** \brief Macro to mark end of pinmux config array */
#define PINMUX_END                      (-1)

/** \brief Pin mode - it is at 0th bit. No shift requried */
#define PIN_MODE(mode)                  ((uint32_t) mode)
/** \brief Resistor enable */
#define PIN_PULL_DISABLE                (((uint32_t) 0x1U) << 16U)
/** \brief Pull direction */
#define PIN_PULL_DIRECTION              (((uint32_t) 0x1U) << 17U)
/** \brief Receiver enable */
#define PIN_INPUT_ENABLE                (((uint32_t) 0x1U) << 18U)
/** \brief Driver disable */
#define PIN_OUTPUT_DISABLE              (((uint32_t) 0x1U) << 21U)
/** \brief Wakeup enable */
#define PIN_WAKEUP_ENABLE               (((uint32_t) 0x1U) << 29U)

/** \brief Main domain pad config register offset in control module */
enum Pinmux_MainOffsets
{
    PIN_OSPI0_CLK        = 0x4000,
    PIN_OSPI0_LBCLKO     = 0x4004,
    PIN_OSPI0_DQS        = 0x4008,
    PIN_OSPI0_D0         = 0x400C,
    PIN_OSPI0_D1         = 0x4010,
    PIN_OSPI0_D2         = 0x4014,
    PIN_OSPI0_D3         = 0x4018,
    PIN_OSPI0_D4         = 0x401C,
    PIN_OSPI0_D5         = 0x4020,
    PIN_OSPI0_D6         = 0x4024,
    PIN_OSPI0_D7         = 0x4028,
    PIN_OSPI0_CSN0       = 0x402C,
    PIN_OSPI0_CSN1       = 0x4030,
    PIN_OSPI0_CSN2       = 0x4034,
    PIN_OSPI0_CSN3       = 0x4038,
    PIN_MCASP0_ACLKX     = 0x403C,
    PIN_MCASP0_AFSX      = 0x4040,
    PIN_MCASP0_AXR0      = 0x4044,
    PIN_MCASP0_AXR1      = 0x4048,
    PIN_MCASP0_AXR2      = 0x404C,
    PIN_MCASP0_AXR3      = 0x4050,
    PIN_MCASP0_AXR4      = 0x4054,
    PIN_MCASP0_AXR5      = 0x4058,
    PIN_MCASP0_AXR6      = 0x405C,
    PIN_MCASP0_AXR7      = 0x4060,
    PIN_MCASP0_AXR8      = 0x4064,
    PIN_MCASP0_AXR9      = 0x4068,
    PIN_MCASP0_AXR10     = 0x406C,
    PIN_MCASP0_AXR11     = 0x4070,
    PIN_MCASP0_AXR12     = 0x4074,
    PIN_MCASP0_AXR13     = 0x4078,
    PIN_MCASP0_AXR14     = 0x407C,
    PIN_MCASP0_AXR15     = 0x4084,
    PIN_MCASP1_ACLKX     = 0x4088,
    PIN_MCASP1_AFSX      = 0x408C,
    PIN_MCASP1_AXR0      = 0x4090,
    PIN_MCASP1_AXR1      = 0x4094,
    PIN_MCASP1_AXR2      = 0x4098,
    PIN_MCASP1_AXR3      = 0x409C,
    PIN_MCASP2_ACLKX     = 0x40A0,
    PIN_MCASP2_AFSX      = 0x40A4,
    PIN_MCASP2_AXR0      = 0x40A8,
    PIN_MCASP2_AXR1      = 0x40AC,
    PIN_MCASP2_AXR2      = 0x40B0,
    PIN_MCASP2_AXR3      = 0x40B4,
    PIN_MCASP2_AXR4      = 0x40B8,
    PIN_MCASP2_AXR5      = 0x40BC,
    PIN_MCASP3_ACLKX     = 0x40C0,
    PIN_MCASP3_AFSX      = 0x40C4,
    PIN_MCASP3_AXR0      = 0x40C8,
    PIN_MCASP3_AXR1      = 0x40CC,
    PIN_MCASP3_AXR2      = 0x40D0,
    PIN_MCASP3_AXR3      = 0x40D4,
    PIN_MCASP4_ACLKX     = 0x40E0,
    PIN_MCASP4_AFSX      = 0x40E4,
    PIN_MCASP4_AXR0      = 0x40E8,
    PIN_MCASP4_AXR1      = 0x40EC,
    PIN_MCASP4_AXR2      = 0x40F0,
    PIN_MLB0_MLBSIG      = 0x40FC,
    PIN_MLB0_MLBCLK      = 0x4100,
    PIN_MLB0_MLBDAT      = 0x4104,
    PIN_OSPI1_CLK        = 0x4108,
    PIN_OSPI1_LBCLKO     = 0x410C,
    PIN_OSPI1_DQS        = 0x4110,
    PIN_OSPI1_D0         = 0x4114,
    PIN_OSPI1_D1         = 0x4118,
    PIN_OSPI1_D2         = 0x411C,
    PIN_OSPI1_D3         = 0x4120,
    PIN_OSPI1_CSN0       = 0x4124,
    PIN_RGMII1_TX_CTL    = 0x412C,
    PIN_RGMII1_TXC       = 0x4130,
    PIN_RGMII1_TD0       = 0x4134,
    PIN_RGMII1_TD1       = 0x4138,
    PIN_RGMII1_TD2       = 0x413C,
    PIN_RGMII1_TD3       = 0x4140,
    PIN_RGMII1_RX_CTL    = 0x4144,
    PIN_RGMII1_RXC       = 0x4148,
    PIN_RGMII1_RD0       = 0x414C,
    PIN_RGMII1_RD1       = 0x4150,
    PIN_RGMII1_RD2       = 0x4154,
    PIN_RGMII1_RD3       = 0x4158,
    PIN_MDIO0_MDIO       = 0x415C,
    PIN_MDIO0_MDC        = 0x4160,
    PIN_RGMII2_TX_CTL    = 0x4164,
    PIN_RGMII2_TXC       = 0x4168,
    PIN_RGMII2_TD0       = 0x416C,
    PIN_RGMII2_TD1       = 0x4170,
    PIN_RGMII2_TD2       = 0x4174,
    PIN_OSPI1_CSN1       = 0x4128,
    PIN_RGMII2_TD3       = 0x4178,
    PIN_RGMII2_RX_CTL    = 0x417C,
    PIN_RGMII2_RXC       = 0x4180,
    PIN_RGMII2_RD0       = 0x4184,
    PIN_RGMII2_RD1       = 0x4188,
    PIN_RGMII2_RD2       = 0x418C,
    PIN_RGMII2_RD3       = 0x4190,
    PIN_SPI2_D0          = 0x4194,
    PIN_SPI2_D1          = 0x4198,
    PIN_SPI2_CS2         = 0x419C,
    PIN_AUDIO_EXT_REFCLK0    = 0x41A0,
    PIN_SPI2_CS1         = 0x41A4,
    PIN_SPI2_CS3         = 0x41A8,
    PIN_SPI2_CS0         = 0x41AC,
    PIN_SPI2_CLK         = 0x41B0,
    PIN_SPI0_CS0         = 0x41B4,
    PIN_SPI0_CS1         = 0x41B8,
    PIN_SPI0_CLK         = 0x41BC,
    PIN_SPI0_D0          = 0x41C0,
    PIN_SPI0_D1          = 0x41C4,
    PIN_UART0_RXD        = 0x41C8,
    PIN_UART0_TXD        = 0x41CC,
    PIN_UART0_CTSN       = 0x41D0,
    PIN_UART0_RTSN       = 0x41D4,
    PIN_MCAN0_TX         = 0x41D8,
    PIN_MCAN0_RX         = 0x41DC,
    PIN_I2C0_SCL         = 0x41E0,
    PIN_I2C0_SDA         = 0x41E4,
    PIN_I2C1_SCL         = 0x41E8,
    PIN_I2C1_SDA         = 0x41EC,
    PIN_EXT_REFCLK1      = 0x41F0,
    PIN_EXTINTN          = 0x41F4,
    PIN_MMC0_DAT7        = 0x41F8,
    PIN_MMC0_DAT6        = 0x41FC,
    PIN_MMC0_DAT5        = 0x4200,
    PIN_MMC0_DAT4        = 0x4204,
    PIN_MMC0_DAT3        = 0x4208,
    PIN_MMC0_DAT2        = 0x420C,
    PIN_MMC0_DAT1        = 0x4210,
    PIN_MMC0_DAT0        = 0x4214,
    PIN_MMC0_CLK         = 0x4218,
    PIN_MMC0_CMD         = 0x4220,
    PIN_SPI1_CS0         = 0x4224,
    PIN_SPI1_CS1         = 0x4228,
    PIN_SPI1_CLK         = 0x422C,
    PIN_SPI1_D0          = 0x4230,
    PIN_SPI1_D1          = 0x4234,
    PIN_GPIO1_47         = 0x423C,
    PIN_GPIO1_48         = 0x4240,
    PIN_GPIO1_49         = 0x4244,
    PIN_USB0_DRVVBUS     = 0x4254,
    PIN_GPIO1_72         = 0x42AC,
    PIN_ADC0_AIN0        = 0x42B0,
    PIN_ADC0_AIN1        = 0x42B4,
    PIN_ADC0_AIN2        = 0x42B8,
    PIN_ADC0_AIN3        = 0x42BC,
    PIN_ADC0_AIN4        = 0x42C0,
    PIN_ADC0_AIN5        = 0x42C4,
    PIN_ADC0_AIN6        = 0x42C8,
    PIN_ADC0_AIN7        = 0x42CC,
    PIN_OSPI1_D4         = 0x42D0,
    PIN_OSPI1_D5         = 0x42D4,
    PIN_OSPI1_D6         = 0x42D8,
    PIN_OSPI1_D7         = 0x42DC
};

/** \brief Wakeup domain pad config register offset in control module */
enum Pinmux_McuOffsets
{
	PIN_EMU1            = 0x407C,
	PIN_EMU0            = 0x4078,
	PIN_WKUP_CLKOUT0    = 0x4084,
	PIN_PMIC_LPM_EN0    = 0x4080,
	PIN_WKUP_I2C0_SDA   = 0x4050,
	PIN_WKUP_I2C0_SCL   = 0x404C,
	PIN_MCU_GPIO0_16    = 0x4040,
	PIN_MCU_GPIO0_15    = 0x403C,
	PIN_MCU_GPIO0_14    = 0x4038,
	PIN_MCU_GPIO0_13    = 0x4034,
	PIN_WKUP_UART0_RTSN = 0x4030,
	PIN_WKUP_UART0_CTSN = 0x402C,
	PIN_WKUP_UART0_TXD  = 0x4028,
	PIN_WKUP_UART0_RXD  = 0x4024,
	PIN_MCU_GPIO0_8     = 0x4020,
	PIN_MCU_GPIO0_7     = 0x401C,
	PIN_MCU_GPIO0_6     = 0x4018,
	PIN_MCU_GPIO0_5     = 0x4014,
	PIN_MCU_GPIO0_4     = 0x4010,
	PIN_MCU_GPIO0_3     = 0x400C,
	PIN_MCU_GPIO0_2     = 0x4008,
	PIN_WKUP_TIMER_IO1  = 0x4004,
	PIN_WKUP_TIMER_IO0  = 0x4000
};


/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/** \brief Structure defining the pin configuration parameters */
typedef struct Pinmux_PerCfg
{
    int16_t     offset;
    /**< Register offset for configuring the pin.
     *   Refer \ref Pinmux_MainOffsets and \ref Pinmux_McuOffsets.
     *   Set this to #PINMUX_END to demark the end of configuration array */
    uint32_t    settings;
    /**< Value to be configured.
     *   Active mode configurations like mux mode, pull resistor and
     *   buffer mode.
     *
     *   To set a value use like   : "| PIN_PULL_DISABLE"
     *   To reset a value use like : "& (~PIN_PULL_DIRECTION)"
     *
     *   For example,
     *   PIN_MODE(7) | ((PIN_PULL_DISABLE | PIN_INPUT_ENABLE) & (~PIN_PULL_DIRECTION)
     */
} Pinmux_PerCfg_t;

/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  This API configures the pinmux based on the domain
 *
 *  \param  pinmuxCfg   Pointer to list of pinmux configuration array.
 *                      This parameter cannot be NULL and the last entry should
 *                      be initialized with #PINMUX_END so that this function
 *                      knows the end of configuration.
 *  \param  domainId    Domain ID to set pinmux configuration.
 *                      Refer \ref Pinmux_DomainId_t
 */
void Pinmux_config(const Pinmux_PerCfg_t *pinmuxCfg, uint32_t domainId);

/**
 *  \brief  This API unlocks the PAD config control MMRs for the given domain
 *
 *  \param  domainId    Domain ID to unlock the PAD config MMRs.
 *                      Refer \ref Pinmux_DomainId_t
 */
void Pinmux_unlockMMR(uint32_t domainId);

/**
 *  \brief  This API locks the PAD config control MMRs for the given domain
 *
 *  \param  domainId    Domain ID to lock the PAD config MMRs.
 *                      Refer \ref Pinmux_DomainId_t
 */
void Pinmux_lockMMR(uint32_t domainId);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef PINMUX_AM275X_H_ */

/** @} */


