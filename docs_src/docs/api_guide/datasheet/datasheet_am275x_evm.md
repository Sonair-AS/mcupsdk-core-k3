# Datasheet {#DATASHEET_AM275X_EVM}

[TOC]

This datasheet provides the performance numbers of various device drivers in FreeRTOS SDK for @VAR_SOC_NAME

## Generic Setup details

SOC Details             | Values
------------------------|------------------------------
Core                    | R5F
Core Operating Speed    | 800 MHz
Cache Status            | Enabled

SOC Details             | Values
------------------------|------------------------------
Core                    | C75
Core Operating Speed    | 1000 MHz
Cache Status            | Enabled

Optimization Details    | Values
------------------------|------------------------------
Build Profile           | Release
R5F Compiler flags      | -mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -Wall -Werror -g -mthumb -Wno-gnu-variable-sized-type-not-at-end -Wno-unused-function
R5F Linker flags        | -Wl,--diag_suppress=10063 -Wl,--ram_model -Wl,--reread_libs
Code Placement          | MSRAM
Data Placement          | MSRAM
C7 Compiler flags       | -mv7524  --abi=eabi -q -mo -pden -pds=238 -pds=880 -pds1110 --endian=little  --disable_inlining -ea.se71 --emit_warnings_as_errors --diag_suppress=770 --diag_suppress=69 --diag_suppress=70 -Dxdc_target_name__=C71 --opt_level=3 --symdebug:none
C7 Linker flags         | --silicon_version=7524 -z --emit_warnings_as_errors --diag_suppress=10063 --ram_model --warn_sections -q -x
Code Placement          | MSRAM / L2RAM
Data Placement          | MSRAM / L2RAM

## Performance Numbers
### SBL OSPI NOR performance (HS-FS)

- Software/Application used        : sbl_ospi, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 461 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        614
System_init                      |       1886
Board_init                       |          2
FreeRtosTask Create              |        255
Drivers_open                     |         96
Board_driversOpen                |          0
sciServer_init                   |      15061
SBL Drivers_open                 |       3172
SBL Board_driversOpen            |       2929
Sciclient Get Version            |      10014
R5FSS0_0 Image Load              |       1617
R5FSS0_1 Image Load              |       1565
R5FSS1_0 Image Load              |       1569
R5FSS1_1 Image Load              |       1556
DSP 0 Image Load                 |       6969
DSP 1 Image Load                 |       6794
---------------------------------|--------------
SBL Total Time Taken             |      54107

### SBL Fast-xSPI NOR performance (HS-FS)

- Software/Application used        : sbl_ospi, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 460 KB
- Boot Media Clock                 : 133.333 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        765
System_init                      |       1877
Board_init                       |          2
FreeRtosTask Create              |        256
Drivers_open                     |         98
Board_driversOpen                |          0
sciServer_init                   |      15070
SBL Drivers_open                 |       3170
SBL Board_driversOpen            |        112
Sciclient Get Version            |      10019
R5FSS0_0 Image Load              |       1656
R5FSS0_1 Image Load              |       1599
R5FSS1_0 Image Load              |       1603
R5FSS1_1 Image Load              |       1585
DSP 0 Image Load                 |       7075
DSP 1 Image Load                 |       6908
---------------------------------|--------------
SBL Total Time Taken             |      51801

#### R5FSS0_0 boot time using Fast-xSPI Bootmode
 - GPIO toggle time from R5FSS0_0 (Measured from PORz)
   - 37.52524 ms

 - Cores booted by SBL : r5fss0-0, r5fss0-1, r5fss1-0, r5fss1-1, c75ss0-0, c75ss1-0
 - R5FSS0-0 image size = ~ 1 MB and remaining cores by default ipc rpmsg images

#### C7x audio chime time using Fast-xSPI Bootmode
 - C7x audio out time (Measured from PORz)
   - 72.69178 ms

 - Cores booted by SBL : r5fss0-0, r5fss0-1, r5fss1-0, r5fss1-1, c75ss0-0, c75ss1-0
 - C75SS0-0 image size = ~ 1 MB and remaining cores by default ipc rpmsg images
 - Includes DAC configuration time


### SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc, ipc_rpmsg_echo
- Cores booted by SBL              : r5fss0-0 r5fss0-1 r5fss1-0 r5fss1-1 c75ss0-0 c75ss1-0
- Size of images loaded            : 461 KB
- Boot Media Clock                 : 200.00 MHz
- Mode                             : HS200

SBL boot time breakdown          |   Time (us)
---------------------------------|--------------
TIFS init                        |        500
System_init                      |        700
Board_init                       |          0
FreeRtosTask Create              |        255
Drivers_open                     |         57
Board_driversOpen                |          0
sciServer_init                   |        103
SBL Drivers_open                 |      18196
Sciclient Get Version            |      10047
R5FSS0_0 Image Load              |      11872
R5FSS0_1 Image Load              |      11529
R5FSS1_0 Image Load              |      10814
R5FSS1_1 Image Load              |      11525
DSP 0 Image Load                 |      18333
DSP 1 Image Load                 |      15761
---------------------------------|--------------
SBL Total Time Taken             |     109696

### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 c75ss0-0   | c75ss1-0      | 1.748
 r5f0-0     | r5f0-1        | 1.171
 r5f0-0     | r5f1-0        | 1.285
 r5f0-0     | r5f1-1        | 1.161
 r5f0-0     | c75ss0-0      | 1.118
 r5f0-0     | c75ss1-0      | 1.120

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured
Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) |
------------|-------------|--------------|------------------------------|------------------|
      r5f0-0|       r5f0-1|            32|                         8.289|                 9|
      r5f0-0|       r5f0-1|            64|                        10.050|                11|
      r5f0-0|       r5f0-1|           112|                        12.826|                14|
      r5f0-0|       r5f1-0|            32|                         8.223|                 9|
      r5f0-0|       r5f1-0|            64|                         9.989|                10|
      r5f0-0|       r5f1-0|           112|                        12.749|                13|
      r5f0-0|       r5f1-1|            32|                         8.257|                 9|
      r5f0-0|       r5f1-1|            64|                        10.047|                10|
      r5f0-0|       r5f1-1|           112|                        12.813|                13|
      r5f0-0|     c75ss0-0|            32|                         9.326|                10|
      r5f0-0|     c75ss0-0|            64|                        10.148|                11|
      r5f0-0|     c75ss0-0|           112|                        11.397|                12|
      r5f0-0|     c75ss1-0|            32|                         9.382|                10|
      r5f0-0|     c75ss1-0|            64|                        10.197|                11|
      r5f0-0|     c75ss1-0|           112|                        11.487|                13|

### EMMC Performance

Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
SDR50  | 1	       | 40.54		    | 45.01
DDR50  | 1	       | 67.55		    | 82.00
HS200  | 1	       | 94.21		    | 157.80

### OSPI NOR Flash Performance
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1             | 0.41               | 284.11
 2             | 0.41               | 284.60

 ### XIP Benchmark
- Core :	R5F
- Core Operating Speed : 800 MHz

- Software/Application used : xip_benchmark

- 1) FIR operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    24048
Code/Data not cached                    |    66115
Code/Data not cached 1 of 10 iterations |    28257

- 2) MEMCPY operation

Caching status                          | Cycles taken
----------------------------------------|-------------
Code/Data fully cached                  |    1566
Code/Data not cached                    |    4497
Code/Data not cached 1 of 10 iterations |    1864
