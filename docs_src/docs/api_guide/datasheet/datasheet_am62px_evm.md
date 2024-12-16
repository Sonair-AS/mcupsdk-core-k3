# Datasheet {#DATASHEET_AM62PX_EVM}

[TOC]

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for @VAR_SOC_NAME


## Generic Setup details

SOC Details             | Values
------------------------|------------------------------
Core                    | R5F
Core Operating Speed    | 800 MHz
Cache Status            | Enabled

Optimization Details    | Values
------------------------|------------------------------
Build Profile           | Release
R5F Compiler flags      | -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -Wall -Werror -g -mthumb -Wno-gnu-variable-sized-type-not-at-end -Wno-unused-function
R5F Linker flags        | -Wl,--diag_suppress=10063 -Wl,--ram_model -Wl,--reread_libs
Code Placement          | HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)
Data Placement          | HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)

## Performance Numbers

### SBL OSPI NOR performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 233 KB
- Size of images loaded by stage2  : 859 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.276
SBL Stage1: App_waitForMcuPbist         |    0.002
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.091
SBL Stage1: SBL Drivers_open            |    0.134
SBL Stage1: Board_driversOpen           |    0.008
SBL Stage1: SBL Board_driversOpen       |    1.269
SBL Stage1: App_loadSelfcoreImage       |    4.535
----------------------------------------|--------------
SBL Stage1: Total time taken            |   44.320

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.148
SBL Stage2: Board_init                  |    0.003
SBL Stage2: FreeRtosTask Create         |    0.260
SBL Stage2: SBL Drivers_open            |    1.011
SBL Stage2: SBL Board_driversOpen       |    0.130
SBL Stage2: App_loadImages              |    3.694
SBL Stage2: App_loadMCUImages           |    6.539
SBL Stage2: App_loadLinuxImages         |   18.973
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.759

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : wkup-r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0
- Size of images loaded by stage1  : 206 KB
- Size of images loaded by stage2  : 914 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS400

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   38.159
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.000
SBL Stage1: SBL Drivers_open            |   20.582
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: App_loadSelfcoreImage       |    9.201
----------------------------------------|--------------
SBL Stage1: Total time taken            |   67.944


SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.053
SBL Stage2: Board_init                  |    0.000
SBL Stage2: FreeRtosTask Create         |    0.260
SBL Stage2: SBL Drivers_open            |   22.975
SBL Stage2: App_loadImages              |    5.220
SBL Stage2: App_loadMCUImages           |    7.951
SBL Stage2: App_loadLinuxImages         |   19.305
----------------------------------------|--------------
SBL Stage2: Total time taken            |   57.767

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~38 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
wkup-r5f0-0 | mcu-r5f0-0  |  1.23

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
 wkup-r5f0-0|   mcu-r5f0-0|            32|                        14.696|                15|         1000
 wkup-r5f0-0|   mcu-r5f0-0|            64|                        21.326|                21|         1000
 wkup-r5f0-0|   mcu-r5f0-0|           112|                        30.804|                31|         1000


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 31.61	             | 45.01
 SDR50 | 4	            | 41.38		         | 45.55
 SDR50 | 6	            | 41.59		         | 44.25
 DDR50 | 1	            | 53.25		         | 81.85
 DDR50 | 4	            | 53.62		         | 83.63
 DDR50 | 6	            | 71.20		         | 79.33
 HS200 | 1	            | 70.56	     	     | 157.70
 HS200 | 4	            | 109.64		     | 169.40
 HS200 | 6	            | 74.31 		     | 152.66
 HS400 | 1	            | 71.93		         | 249.19
 HS400 | 4	            | 109.97		     | 267.29
 HS400 | 6	            | 108.35		     | 226.37

### OSPI NOR Flash Performance
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 0.43		        | 283.56
 5	           | 0.44		        | 284.78
 10	           | 0.45		        | 284.93

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          3.45 ms
Fast Tuning Window          |          1.15 ms

 ### GPIO latency
GPIO latency is measured by connecting 2 GPIOs externaly and configuring one GPIO as input and the other as output. Then 1 is written to GPIO output and
measure the time between writing 1 to GPIO output to rececving the interrupt at GPIO input.

Core      | GPIO In      | GPIO Out     | Latency (us)
----------|--------------|--------------|-------------
 mcu-r5f  | MCU_GPIO0_15 | MCU_GPIO0_16 |   2