# Datasheet {#DATASHEET_AM62X_EVM}

[TOC]

## Introduction

This datasheet provides the performance numbers of various device drivers in MCU PLUS SDK for @VAR_SOC_NAME


## Generic Setup details

<table>
    <tr>
        <th>SOC Details</th>
        <th>Core</th>
        <th>Value</th>
    </tr>
    <tr>
        <td rowspan=2>Core Operating Speed</td>
        <td>R5F</td>
        <td>400 MHz</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>1.4 GHz</td>
    </tr>
    <tr>
        <td rowspan=2>Cache Status</td>
        <td>R5F</td>
        <td>Enabled</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>Enabled</td>
    </tr>
</table>

<table>
    <tr>
        <th>Optimization Details</th>
        <th>Core</th>
        <th>Value</th>
    </tr>
    <tr>
        <td>Build Profile</td>
        <td>R5F, A53</td>
        <td>Release</td>
    </tr>
    <tr>
        <td rowspan=2>Compiler flags</td>
        <td>R5F</td>
        <td>-mcpu=cortex-r5 -mfloat-abi=hard -mfpu=vfpv3-d16 -Wall -Werror -g -mthumb -Wno-gnu-variable-sized-type-not-at-end -Wno-unused-function</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>-mcpu=cortex-a53+fp+simd -mabi=lp64 -mcmodel=large -mstrict-align -mfix-cortex-a53-835769 -mfix-cortex-a53-843419 -Wall -Werror -g        -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Wno-unused-but-set-variable -fdata-sections -ffunction-sections</td>
    </tr>
    <tr>
        <td rowspan=2>Linker flags</td>
        <td>R5F</td>
        <td>-Wl,--diag_suppress=10063 -Wl,--ram_model -Wl,--reread_libs</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>-Wl,-static -Wl,--gc-sections -Wl,--build-id=none -lstdc++ -lgcc -lm -lc -lrdimon</td>
    </tr>
    <tr>
        <td rowspan=2>Code Placement</td>
        <td>R5F</td>
        <td>HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>DDR</td>
    </tr>
    <tr>
        <td rowspan=2>Data Placement</td>
        <td>R5F</td>
        <td>HSM RAM (For SBL Stage1), DDR (SBL Stage2 and others)</td>
    </tr>
    <tr>
        <td>A53</td>
        <td>DDR</td>
    </tr>
</table>


## Performance Numbers

### AM62X Dhrystone Benchmark performance

Core : **a530-0**

Benchmarks                      | am62x-sk      | am62x-sk-lp    | am62x-sip-sk |
--------------------------------|---------------|----------------|--------------|
cpu_clock (MHz)                 |   1400        |  1400          |  1400        |
dhrystone_per_mhz (DMIPS/MHz)   |   2.8577      |  2.8577        |  2.8577      |
dhrystone_per_second            |   7029351.2   |  7029351.2     |  7029351.2   |

### AM62X-SK SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 190 KB
- Size of images loaded by stage2  : 1028 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.621
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.299
SBL Stage1: Board_driversOpen           |    1.267
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_waitForMcuPbist         |    8.658
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.574
SBL Stage1: App_loadSelfcoreImage       |    4.026
----------------------------------------|--------------
SBL Stage1: Total time taken            |   41.339

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.790
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.382
SBL Stage2: Board_driversOpen           |    0.151
SBL Stage2: Sciclient Get Version       |   10.252
SBL Stage2: App_loadImages              |    2.687
SBL Stage2: App_loadSelfcoreImage       |    4.503
SBL Stage2: App_loadLinuxImages         |   11.179
----------------------------------------|--------------
SBL Stage2: Total time taken            |   31.948

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK SBL OSPI performance (HS-SE)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 190 KB
- Size of images loaded by stage2  : 1028 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.672
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.299
SBL Stage1: Board_driversOpen           |    1.261
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_waitForMcuPbist         |    8.659
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.658
SBL Stage1: App_loadSelfcoreImage       |    4.106
----------------------------------------|--------------
SBL Stage1: Total time taken            |   41.549

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.801
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.370
SBL Stage2: Board_driversOpen           |    0.152
SBL Stage2: Sciclient Get Version       |   10.262
SBL Stage2: App_loadImages              |    2.766
SBL Stage2: App_loadSelfcoreImage       |    4.577
SBL Stage2: App_loadLinuxImages         |   11.254
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.195

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK-SIP SBL OSPI performance (HS-FS)

- Software/Application used        : sbl_ospi_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 190 KB
- Size of images loaded by stage2  : 1028 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 8D-8D-8D

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.705
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.302
SBL Stage1: Board_driversOpen           |    1.268
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_waitForMcuPbist         |    0.005
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.586
SBL Stage1: App_loadSelfcoreImage       |    4.049
----------------------------------------|--------------
SBL Stage1: Total time taken            |   50.811

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.794
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.380
SBL Stage2: Board_driversOpen           |    0.152
SBL Stage2: Sciclient Get Version       |   10.263
SBL Stage2: App_loadImages              |    2.675
SBL Stage2: App_loadSelfcoreImage       |    4.516
SBL Stage2: App_loadLinuxImages         |   11.425
----------------------------------------|--------------
SBL Stage2: Total time taken            |   32.209

- The time taken for Board_driversOpen is mostly for the PHY tuning of OSPI. If this needs to be further reduced, one can pre-train the PHY, note down delay values and set it directly instead of the tuning procedure.

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

### AM62X-SK LP SBL OSPI NAND performance (HS-FS)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 188 KB
- Size of images loaded by stage2  : 1121 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.178
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.209
SBL Stage1: Board_driversOpen           |   26.407
SBL Stage1: Sciclient Get Version       |   10.201
SBL Stage1: App_waitForMcuPbist         |    5.000
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    3.909
SBL Stage1: App_loadSelfcoreImage       |    7.522
----------------------------------------|--------------
SBL Stage1: Total time taken            |   79.124

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.816
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.270
SBL Stage2: Board_driversOpen           |   26.055
SBL Stage2: Sciclient Get Version       |   10.241
SBL Stage2: App_loadImages              |    2.159
SBL Stage2: App_loadSelfcoreImage       |    8.960
SBL Stage2: App_loadLinuxImages         |   40.233
----------------------------------------|--------------
SBL Stage2: Total time taken            |   90.739

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- MCU PBIST is started before the DDR init/ It is done in HW in parallel while the DDR init is completed. Due to this MCU PBIST wait time is low.

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL OSPI NAND performance (HS-SE)

- Software/Application used        : sbl_ospi_nand_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 188 KB
- Size of images loaded by stage2  : 1121 KB
- Boot Media Clock                 : 166.667 MHz
- Mode                             : PHY enabled, DMA enabled
- Protocol                         : 1S-8S-8S

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.110
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |    0.207
SBL Stage1: Board_driversOpen           |   26.409
SBL Stage1: Sciclient Get Version       |   10.201
SBL Stage1: App_waitForMcuPbist         |    0.005
SBL Stage1: App_waitForMcuLbist         |    7.689
SBL Stage1: App_loadImages              |    4.001
SBL Stage1: App_loadSelfcoreImage       |    7.617
----------------------------------------|--------------
SBL Stage1: Total time taken            |   79.244

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.817
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |    0.269
SBL Stage2: Board_driversOpen           |   26.009
SBL Stage2: Sciclient Get Version       |   10.254
SBL Stage2: App_loadImages              |    2.241
SBL Stage2: App_loadSelfcoreImage       |    9.058
SBL Stage2: App_loadLinuxImages         |   40.288
----------------------------------------|--------------
SBL Stage2: Total time taken            |   90.941

- Here the CPU load or section copy takes place from the OSPI memory to DDR, this would be slower that mem to mem copy.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- Out of the ~35 ms taken for System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 160 KB
- Size of images loaded by stage2  : 1028 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.478
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |  107.627
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_loadImages              |    6.521
SBL Stage1: App_loadSelfcoreImage       |    7.824
----------------------------------------|--------------
SBL Stage1: Total time taken            |  137.635

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.619
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.839
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.258
SBL Stage2: App_loadImages              |    5.280
SBL Stage2: App_loadSelfcoreImage       |    9.446
SBL Stage2: App_loadLinuxImages         |   26.995
----------------------------------------|--------------
SBL Stage2: Total time taken            |   75.440

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 160 KB
- Size of images loaded by stage2  : 1028 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |    5.589
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   58.015
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.202
SBL Stage1: App_loadImages              |    6.507
SBL Stage1: App_loadSelfcoreImage       |    7.805
----------------------------------------|--------------
SBL Stage1: Total time taken            |   88.122

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.605
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.871
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.253
SBL Stage2: App_loadImages              |    5.295
SBL Stage2: App_loadSelfcoreImage       |    9.447
SBL Stage2: App_loadLinuxImages         |   26.963
----------------------------------------|--------------
SBL Stage2: Total time taken            |   75.437

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK-SIP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 160 KB
- Size of images loaded by stage2  : 1028 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.682
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   20.717
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_loadImages              |    7.480
SBL Stage1: App_loadSelfcoreImage       |    8.784
----------------------------------------|--------------
SBL Stage1: Total time taken            |   70.869

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.586
SBL Stage2: Board_init                  |    0.000
SBL Stage2: Drivers_open                |   20.673
SBL Stage2: Board_driversOpen           |    0.000
SBL Stage2: Sciclient Get Version       |   10.261
SBL Stage2: App_loadImages              |    5.498
SBL Stage2: App_loadSelfcoreImage       |    9.594
SBL Stage2: App_loadLinuxImages         |   26.886
----------------------------------------|--------------
SBL Stage2: Total time taken            |   75.501

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-FS)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 160 KB
- Size of images loaded by stage2  : 1121 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.281
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   40.780
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.203
SBL Stage1: App_loadImages              |    6.485
SBL Stage1: App_loadSelfcoreImage       |    7.903
----------------------------------------|--------------
SBL Stage1: Total time taken            |   88.655

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.629
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   20.862
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.256
SBL Stage2: App_loadImages              |    5.276
SBL Stage2: App_loadSelfcoreImage       |    9.469
SBL Stage2: App_loadLinuxImages         |   29.554
----------------------------------------|--------------
SBL Stage2: Total time taken            |   78.051

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.

### AM62X-SK LP SBL EMMC performance (HS-SE)

- Software/Application used        : sbl_emmc_linux_multistage, ipc_rpmsg_echo_linux, linux and HSM App Images
- Cores booted by stage1 SBL       : m4f0-0 r5f0-0
- Cores booted by stage2 SBL       : hsm-m4f0-0 r5f0-0 a530-0
- Size of images loaded by stage1  : 160 KB
- Size of images loaded by stage2  : 1121 KB
- Boot Media Clock                 : 200.000 MHz
- Mode                             : HS200

SBL Stage1 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage1: System_init                 |   23.157
SBL Stage1: Board_init                  |    0.000
SBL Stage1: Drivers_open                |   114.273
SBL Stage1: Board_driversOpen           |    0.000
SBL Stage1: Sciclient Get Version       |   10.201
SBL Stage1: App_loadImages              |    6.941
SBL Stage1: App_loadSelfcoreImage       |    8.389
----------------------------------------|--------------
SBL Stage1: Total time taken            |  162.964

SBL Stage2 boot time breakdown          |   Time (ms)
----------------------------------------|--------------
SBL Stage2: System_init                 |    2.6432
SBL Stage2: Board_init                  |    0.001
SBL Stage2: Drivers_open                |   20.824
SBL Stage2: Board_driversOpen           |    0.001
SBL Stage2: Sciclient Get Version       |   10.249
SBL Stage2: App_loadImages              |    5.728
SBL Stage2: App_loadSelfcoreImage       |    9.956
SBL Stage2: App_loadLinuxImages         |   30.047
----------------------------------------|--------------
SBL Stage2: Total time taken            |   79.439

- The emmc driver initialization is done as part of Drivers_open.

- The time taken for Sciclient Get Version can be avoided if the version check is disabled

- System Init is mostly attributed to DDR initialization.


### IPC performance

#### IPC NOTIFY

- 10000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Average Message Latency (us)
------------|-------------|------------------------------
 r5f0-0     | m4f0-0      |  1.71
 r5f0-0     | a530-0      |  1.71

#### IPC RPMSG

- 1000 messages are sent and average one way message latency is measured

Local Core  | Remote Core | Message Size | Average Message Latency (us) | Max Latency (us) | Message Count
------------|-------------|--------------|------------------------------|------------------|--------------
      r5f0-0|       m4f0-0|             4|                        23.137|                24|         1000
      r5f0-0|       m4f0-0|            32|                        31.709|                32|         1000
      r5f0-0|       m4f0-0|            64|                        41.591|                42|         1000
      r5f0-0|       m4f0-0|           112|                        56.574|                57|         1000
      r5f0-0|       a530-0|             4|                        11.098|                12|         1000
      r5f0-0|       a530-0|            32|                        14.690|                15|         1000
      r5f0-0|       a530-0|            64|                        19.054|                20|         1000
      r5f0-0|       a530-0|           112|                        25.538|                26|         1000

### EMMC Performance
**r5f0-0:**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1	            | 36.80		         | 44.15
 SDR50 | 4	            | 41.53		         | 43.47
 SDR50 | 6	            | 41.74		         | 43.91
 DDR50 | 1	            | 40.36		         | 78.99
 DDR50 | 4	            | 57.42	             | 76.91
 DDR50 | 6	            | 57.18		         | 78.28
 HS200 | 1	            | 51.08		         | 151.59
 HS200 | 4	            | 57.62		         | 145.42
 HS200 | 6	            | 54.96		         | 148.82
**a53 :**
Mode   | Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
-------|----------------|--------------------|-----------------
 SDR50 | 1              | 41.02              | 46.12
 SDR50 | 4              | 43.26              | 45.38
 SDR50 | 6              | 43.52              | 45.79
 DDR50 | 1              | 46.23              | 85.60
 DDR50 | 4              | 63.20              | 83.07
 DDR50 | 6              | 61.31              | 84.46
 HS200 | 1              | 59.57              | 177.85
 HS200 | 4              | 54.39              | 167.17
 HS200 | 6              | 64.34              | 172.91

### OSPI NOR Flash Performance
**r5f0-0:**
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 0.44		        | 247.46
 5	           | 0.45		        | 248.68
 10	           | 0.45		        | 248.83

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          3.58 ms
Fast Tuning Window          |          1.15 ms

**a53 :**
 - Flash protocol: FLASH_CFG_PROTO_8D_8D_8D
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 0.45		        | 325.76
 5	           | 0.46		        | 326.94
 10	           | 0.46		        | 327.08

DQS Tuning Algorithm        |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          2.98 ms
Fast Tuning Window          |          0.97 ms

### OSPI NAND Flash Performance
**r5f0-0:**
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - PHY : enabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 2.07		        | 46.76
 5	           | 2.07		        | 46.76
 10	           | 2.07		        | 46.76

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          1.12  ms
Fast Tuning Window          |          0.63  ms

**a53 :**
 - Flash protocol: FLASH_CFG_PROTO_1S_8S_8S
 - PHY : disabled
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1             | 2.58               | 53.57
 5             | 2.58               | 55.24
 10            | 2.58               | 56.82

Non-DQS Tuning Algorithm    |    Tuning Time (ms)
----------------------------|------------------------
Default Tuning Window       |          0.96  ms
Fast Tuning Window          |          0.54  ms

### GPMC NAND Flash Performance
**r5f0-0:**
 - Flash type: PARALLEL NAND
 - DMA : enabled

Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 6.51		        | 19.93
 5	           | 6.50		        | 19.93
 10	           | 6.50		        | 19.93

**a53 :**
Data size(MiB) | Write speed(MiBps) | Read speed(MiBps)
---------------|--------------------|-----------------
 1	           | 9.71		        | 22.13
 5	           | 9.67		        | 22.13
 10	           | 9.66		        | 22.13


 ### CPSW Performance

#### TCP Test
- Software/Application used : enet_lwip_cpsw
- iperf test type           : TCP iperf
- iperf command used        : iperf -c 192.168.0.158 -i 10 -t 100 -r

#### TCP Performance(am62x-sk):

 TCP direction           | B/W (Mb/s)                     | CPU load(%)
-------------------------|--------------------------------|--------------
 TCP RX                  | 77                             | 12
 TCP TX                  | 76.5                           | 17
 TCP Biderectional       | TX = 51 +  RX = 50             | 22



#### UDP Test
- Software/Application used : enet_lwip_cpsw
- iperf test type           : UDP iperf
- iperf command used        : iperf -c 192.168.0.158 -u -b 60M -l 256 -i 10 -t 100 -r

#### UDP TX Performance(am62x-sk):

  - For Packet Size: 512 B

 Tx Side BW/Packet Size  | CPU load(%)                    | Packet loss(%)
-------------------------|--------------------------------|-----------------------
 25 Mbps                 | 100                            | 0
 50 Mbps                 | 100                            | 0
 100 Mbps                | 100                            | 0.07


#### UDP RX Performance(am62x-sk):
- For Packet Size: 256 B

 Tx Side BW/Packet Size  | CPU load(%)                    | Packet loss(%)
-------------------------|--------------------------------|-----------------------
 25 Mbps                 | 19                             | 11
 50 Mbps                 | 36.26                          | 11
 100 Mbps                | 69.6                           | 12

- For Packet Size: 512 B

 Tx Side BW/Packet Size  | CPU load(%)                    | Packet loss(%)
-------------------------|--------------------------------|-----------------------
 25 Mbps                 | 10                             | 11
 50 Mbps                 | 20                             | 11
 100 Mbps                | 39                             | 11

- For Packet Size: 1500 B

 Tx Side BW/Packet Size  | CPU load(%)                    | Packet loss(%)
-------------------------|--------------------------------|-----------------------
 25 Mbps                 | 5                              | 51
 100 Mbps                | 16                             | 53


