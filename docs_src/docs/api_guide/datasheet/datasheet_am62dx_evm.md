# Datasheet {#DATASHEET_AM62DX_EVM}

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

### SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_multistage, ipc_rpmsg_echo, and HSM App Images
- Cores booted by stage1 SBL       : r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 236 KB
- Size of images loaded by stage2  : 264 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   22.063
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.001
SBL Stage1: SBL Drivers_open            |    0.193
SBL Stage1: Board_driversOpen           |    0.007
SBL Stage1: SBL Board_driversOpen       |    1.312
SBL Stage1: Sciclient Get Version       |   10.169
SBL Stage1: App_loadSelfcoreImage       |    5.609
----------------------------------------|--------------
SBL Stage2: Total time taken            |   39.356

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.801
SBL Stage2: Board_init                  |    0.002
SBL Stage2: FreeRtosTask Create         |    0.258
SBL Stage2: SBL Drivers_open            |    0.718
SBL Stage2: SBL Board Drivers_open      |    0.118
SBL Stage2: App_loadImages              |    3.034
SBL Stage2: App_loadMCUImages           |    5.375
SBL Stage2: App_loadA53Images           |    6.429
SBL Stage2: App_loadDSPImage            |   16.189
----------------------------------------|--------------
SBL Stage2: Total time taken            |   33.927

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~23 ms taken for System Init is mostly attributed to DDR initialization.

### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_multistage, ipc_rpmsg_echo and HSM App Images
- Cores booted by stage1 SBL       : r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 mcu-r5f0-0 r5f0-0 a530-0 c75ss0
- Size of images loaded by stage1  : 236 KB
- Size of images loaded by stage2  : 264 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   21.979
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   20.636
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.185
SBL Stage1: App_loadImages              |   10.318
----------------------------------------|--------------
SBL Stage1: Total time taken            |   63.120

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    1.818
SBL Stage2: Board_init                  |    0.002
SBL Stage2: FreeRtosTask Create         |    0.258
SBL Stage2: Drivers_open                |   16.656
SBL Stage2: App_loadImages              |    5.438
SBL Stage2: App_loadMCUImage            |    6.889
SBL Stage2: App_loadA53Images           |    7.678
SBL Stage2: App_loadDSPImage            |   14.908
----------------------------------------|--------------
SBL Stage2: Total time taken            |   53.651

- The emmc driver initialization is done as part of Drivers_open.

- Out of the ~23 ms taken for System Init is mostly attributed to DDR initialization.

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured.
- All cores are running from DDR with the exception of MCU-R5 from MSRAM

Local Core  | Remote Core | Average Message Latency (ns)
------------|-------------|------------------------------
 mcu-r5f0-0	| c75ss0	  | 1955ns
 mcu-r5f0-0	| a530-0	  | 1216ns
 mcu-r5f0-0	| r5f0-0	  | 1644ns
 a530-0	    | c75ss0	  | 1956ns
 c75ss0	    | r5f0-0	  | 1957ns
 a530-0	    | r5f0-0	  | 1000ns

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) |
------------|-------------|--------------|------------------------------|------------------|
      r5f0-0|       a530-0|             4|                         7.012|                 9|
      r5f0-0|   mcu-r5f0-0|             4|                         9.233|                12|
      r5f0-0|       c75ss0|             4|                        80.315|                93|
      r5f0-0|       a530-0|            32|                         9.681|                12|
      r5f0-0|       a530-0|            64|                        12.611|                15|
      r5f0-0|       a530-0|           112|                        17.279|                20|
      r5f0-0|   mcu-r5f0-0|            32|                        15.532|                18|
      r5f0-0|   mcu-r5f0-0|            64|                        22.497|                25|
      r5f0-0|   mcu-r5f0-0|           112|                        32.896|                35|
      r5f0-0|       c75ss0|            32|                        89.689|               103|
      r5f0-0|       c75ss0|            64|                        91.952|               125|
      r5f0-0|       c75ss0|           112|                       110.982|               125|


### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 40.57		         | 45.01
 SDR50 | 4	            | 41.55		         | 45.55
 SDR50 | 6	            | 35.20		         | 45.58
 DDR50 | 1	            | 67.95		         | 81.88
 DDR50 | 4	            | 71.06		         | 83.63
 DDR50 | 6	            | 71.26		         | 83.73
 HS200 | 1	            | 98.36		         | 158.16
 HS200 | 4	            | 62.39		         | 169.34
 HS200 | 6	            | 108.10		     | 169.80


### OSPI Performance
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
  1	           | 0.40		        | 283.86
  5	           | 0.41		        | 284.83
 10	           | 0.42		        | 284.96

### McASP (audio) Latency
 - Measured in am62a-sk
 - McASP operating at 48KHz, I2C mode
 - RX to TX pin to pin latency is measured
 - Rx To Tx pin to pin latency ~792us

### Boot latency
 - Measured from MCU_PORz to the first response of MCU-R5 and C7x cores
 - OSPI boot mode with SBL running OSPI in 8D-8D-8D mode (Phy enabled, DMA enabled)
 - HSM image size ~7KB
 - MCU R5 image size ~1MB
 - Boot time as observed in HS-FS device

#### MCU R5 boot time
 - GPIO toggle time from MCUR5 main (Measured from MCU_PORz)
  - 112 ms

#### C7x audio chime time
 - C7x audio out time (Measured from MCU_PORz)
 - Includes DAC configuration time
  - 185 ms

