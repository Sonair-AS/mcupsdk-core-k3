# Release Notes 10.01.00 {#RELEASE_NOTES_10_01_00_PAGE}

[TOC]

\attention Also refer to individual module pages for more details on each feature, unsupported features, important usage guidelines.

\note The examples will show usage of SW modules and APIs on a specific CPU instance and OS combination. \n
      Unless explicitly noted otherwise, the SW modules would work in both FreeRTOS and no-RTOS environment. \n

## Device and Validation Information

SOC    | Supported CPUs              | EVM                                                     | Host PC
-------|-----------------------------|---------------------------------------------------------|-----------------------------------
AM275x | R5F, C75                    | @VAR_BOARD_NAME EVM (referred to as am275x-evm in code) | Windows 10 64b or Ubuntu 22.04 64b

## Features Added in This Release

Feature                                                                                  | Module
-----------------------------------------------------------------------------------------|-----------------------------------
R5F: I2C, UDMA, MCASP, UART, OSPI, McSPI, GPIO, SCI Client, DM Timer, IPC                | Drivers
C7X: I2C, UDMA, MCASP, UART, GPIO, SCI Client, DM Timer, IPC                             | Drivers
SBL: OSPI NOR, SD, UART, EMMC                                                            | Bootloader

## Dependent Tools and Compiler Information

Tools/ Component        | Supported CPUs           | Version
------------------------|--------------------------|-----------------------
Code Composer Studio    | R5F, C75                 | 12.8.1
SysConfig               | R5F, C75                 | 1.22.0, build 3893
TI ARM CLANG            | R5F                      | 3.2.0.LTS
C7000-CGT               | C75                      | 4.1.0.LTS
FreeRTOS Kernel         | R5F, C75                 | 11.1.0
TIFS                    | NA                       | v10.01.09

## Key Features

### OS Kernel

OS              | Supported CPUs            | SysConfig Support
----------------|---------------------------|-------------------
FreeRTOS Kernel | R5F, C75                  | NA
FreeRTOS POSIX  | R5F, C75                  | NA
No RTOS         | R5F                       | NA

### Driver Porting Layer (DPL)

Module            | Supported CPUs | SysConfig Support | OS support
------------------|----------------|-------------------|------------------
Address Translate | R5F            | Yes               | FreeRTOS, NORTOS
Cache             | R5F, C75       | Yes               | FreeRTOS, NORTOS
Clock             | R5F, C75       | Yes               | FreeRTOS, NORTOS
CycleCounter      | R5F, C75       | NA                | FreeRTOS, NORTOS
Debug             | R5F, C75       | Yes               | FreeRTOS, NORTOS
Heap              | R5F, C75       | NA                | FreeRTOS, NORTOS
Hwi               | R5F, C75       | Yes               | FreeRTOS, NORTOS
MPU               | R5F, C75       | Yes               | FreeRTOS, NORTOS
Semaphore         | R5F, C75       | NA                | FreeRTOS, NORTOS
Task              | R5F, C75       | NA                | FreeRTOS
Timer             | R5F            | Yes               | FreeRTOS, NORTOS

### Secondary Bootloader (SBL)

SBL Mode  | Supported CPUs | SysConfig Support | PHY Support | DMA Support | OS support
----------|----------------|-------------------|-------------|-------------|--------------------------------------------------------
OSPI NOR  | WKUP-R5F       | Yes               | Yes         |   Yes       | NORTOS
EMMC      | WKUP-R5F       | Yes               | NA          |   NA        | NORTOS
UART      | WKUP-R5F       | Yes               | NA          |   No        | NORTOS
SD        | WKUP-R5F       | Yes               | NA          |   NA        | NORTOS


### SOC Device Drivers

Peripheral | Supported CPUs  | SysConfig Support
-----------|-----------------|-------------------
GPIO       | R5F, C7X        | YES
I2C        | R5F, C7X        | YES
IPC        | R5F, C7X        | YES
MCAN       | R5F             | YES
MCASP      | R5F, C7X        | YES
MCSPI      | R5F             | YES
MMCSD      | R5F             | YES
Pinmux     | R5F, C7X        | YES
SOC        | R5F, C7X        | YES
SCI Client | R5F, C7X        | YES
UART       | R5F, C7X        | YES
UDMA       | R5F, C7X        | YES


### Board Device Drivers

Peripheral | Supported CPUs | SysConfig Support
-----------|----------------|-------------------
EEPROM     | R5F            | Yes
Flash      | WKUP-R5F       | Yes
LED        | R5F            | Yes

## Fixed Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Applicable Releases
</tr>
<tr>
    <td> NA
    <td> NA
    <td> NA
    <td> NA
</tr>
</table>

## Known Issues


<table>
<tr>
    <th> ID
    <th> Head Line
    <th> Module
    <th> Reported in release
    <th> Workaround
</tr>
<tr>
    <td> NA
    <td> NA
    <td> NA
    <td> NA
    <td> NA
</tr>
</table>

## Limitations

<table>
<tr>
    <th> S.No
    <th> Head Line
    <th> Module
</tr>
<tr>
    <td> 1
    <td> The **ROM** startup model for runtime initializations in TI ARM CLANG is not supported/tested in the SDK
    <td> NA
</tr>
</table>
</table>