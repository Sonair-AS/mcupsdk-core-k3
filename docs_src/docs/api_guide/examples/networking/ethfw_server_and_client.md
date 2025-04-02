# Ethernet Firmware {#ETHFW_SERVER_AND_CLIENT}

# Introduction
This Ethernet Firmware example demonstrates ability to perform traffic steering from CPSW to multiple cores. This uses hardware capabilities of CPSW to direct unicast traffic, and a shared memory based layer to send multicast and broadcast traffic.

Ethernet Firmware server is the application which owns the CPSW peripheral, and controls the behaviour. Ethernet firmware clients are the applications which are running on different cores, which send requests to ethernet firmware server based on their requirements.

\note This is in work-in-progress state currently, and complete feature list and functionality will be updates as functional validation progresses.

\attention For more information, please refer to the link ``https://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-j784s4/latest/exports/docs/ethfw/docs/user_guide/ethfw_c_ug_top.html``

# Supported Combinations

\cond SOC_AM62PX
## Ethernet Firmware Server

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | wkup-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/ethfw/apps/app_remoteswitchcfg_server/sitara/
 
## Ethernet Firmware Client

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0_freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | source/networking/ethfw/apps/app_remoteswitchcfg_client/sitara/
 
## Other Clients supported

 Client Env     | Supported Core + OS
 ---------------|-----------
 MCAL Client    | mcu-r5fss0-0_freertos
 Linux Client   | A53-linux

\endcond

# Steps to Run the Example

## Prerequisites
- EVM Board
- CAT6 Ethernet cable

## Build the example

- When using CCS projects to build, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- When using makefiles to build, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)

## HW Setup

- Connect the One end of the CAT6 cable to the EVM and the other end of the CAT6 cable to network.

## Run the example
\attention If you need to reload and run again, a CPU power-cycle is MUST.

\note CCS loading is not supported for any core. Applications are tested with OSPI boot mode

- Load wkup-r5 Server binary to the evm via OSPI boot mode.
- Load other binaries via SBL flow or U-boot flow.
- You will see logs in the UART terminal as shown in the next section.
- The prints will indicate the IP address acquired by clients against their corresponding MAC addresses

## Sample output

\code
==========================
       TSN CPSW App
==========================
Enabling clocks!
start to open driver.
EnetAppUtils_reduceCoreMacAllocation: Reduced Mac Address Allocation for CoreId:0 From 4 To 2

Init all configs
----------------------------------------------
sitara-cpsw: init config
Mdio_open: MDIO Manual_Mode enabled
sitara-cpsw: Open port 1
EnetPhy_bindDriver: PHY 15: OUI:080028 Model:23 Ver:01 <-> 'dp83867' : OK
sitara-cpsw: Open port 2
PHY 15 is alive
sitara-cpsw: Create RX task for regular traffic
initQs() txFreePktInfoQ initialized with 4 pkts
MAC port addr: 70:ff:76:1d:ec:f2
Start: uniconf_task
sitara-cpsw: default RX flow started
EnetApp_uniconfTask: dbname: NULL
EnetApp_gptpYangConfig:domain=0
Start: gptp2d_task
Start: aaf_dolby_task
EnetApp_initTsn:TSN app start done!
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_SINGLE_CLOCK_MODE=1
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_USE_HW_PHASE_ADJUSTMENT=1
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_CLOCK_COMPUTE_INTERVAL_MSEC=100
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_FREQ_OFFSET_IIR_ALPHA_START_VALUE=1
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_FREQ_OFFSET_IIR_ALPHA_STABLE_VALUE=4
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_PHASE_OFFSET_IIR_ALPHA_START_VALUE=1
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_PHASE_OFFSET_IIR_ALPHA_STABLE_VALUE=4
EnetApp_gptpNonYangConfig:XL4_EXTMOD_XL4GPTP_MAX_DOMAIN_NUMBER=1
Waiting for GPTP ready!!

GPTP ready!!

CPSW_ALE_IOCTL_ADD_VLAN: 110
CPSW_ALE_IOCTL_ADD_VLAN: 110
Logger_task: started
unibase-1.1.4
INF:cbase:tilld0: has mac: 70:FF:76:1D:EC:F2
INF:cbase:tilld1: has mac: 00:00:00:00:00:00
INF:cbase:cb_lld_task_create: uniconf_task stack_size=16384
INF:uconf:simpledb_open:no data is imported
INF:uconf:get_next_nameid:a new mod=xl4-data, enum=0
INF:uconf:get_next_nameid:a new mod=xl4-extmod, enum=1
INF:uconf:uc_hwal_open:
INF:cbase:cb_rawsock_open:combase-1.1.3
INF:cbase:cb_rawsock_open:dmaTxChId=-1 numRxChannels=1 dmaRxChId=-1 nTxPkts=0 nRxPkts=0 pktSize=0
INF:uconf:get_next_nameid:a new mod=ietf-interfaces, enum=2
INF:uconf:get_next_nameid:a new mod=ieee1588-ptp-tt, enum=3
INF:uconf:get_next_nameid:a new mod=ieee802-dot1q-bridge, enum=4
INF:uconf:get_next_nameid:a new mod=excelfore-tsn-remote, enum=5
INF:uconf:get_next_nameid:a new mod=excelfore-netconf-server, enum=6
INF:uconf:get_next_nameid:a new mod=ietf-netconf-monitoring, enum=7
INF:uconf:get_next_nameid:a new mod=ietf-yang-library, enum=8
INF:uconf:get_next_nameid:a new mod=ieee802-dot1ab-lldp, enum=9
INF:uconf:get_INF:gptp:000000-506248:domainIndex=0, GM changed old=00:00:00:00:00:00:00:00, new=70:FF:76:FF:FE:1D:EC:F2
INF:gptp:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=2
Cpsw_handleLinkUp: Port 1: Link up: 1-Gbps Full-Duplex
MAC Port 1: link up
INF:cbase:cbl_query_response:tilld0: link UP, speed=1000, duplex=1 !!!!
INF:gptp:index=1 speed=1000, duplex=full
      5.388s : CPU load =   8.83 %
domain=0, offset=0nsec, hw-adjrate=0ppb
        gmsync=true, last_setts64=0nsec
     10.389s : CPU load =   2.11 %
     15.390s : CPU load =   2.05 %
domain=0, offset=0nsec, hw-adjrate=0ppb
        gmsync=true, last_setts64=0nsec
     20.391s : CPU load =   2.07 %
INF:gptp:md_pdelay_resp_sm_recv_req:port=1, set receivedNonCMLDSPdelayReq=1
WRN:gptp:000024-000662:waiting_for_pdelay_interval_timer_proc:portIndex=1, sourcePortIdentity=00:68:EB:FF:FE:BC:85:09, thisClock=70:FF:76:FF:FE:1D:EC:F2, neighborPropDelay=7340
INF:gptp:waiting_for_pdelay_interval_timer_proc:portIndex=1, not asCapable
INF:gptp:waiting_for_pdelay_interval_timer_proc:set asCapableAcrossDomains, portIndex=1
INF:gptp:set asCapable for domainIndex=0, portIndex=1
INF:gptp:000025-001701:gptpgcfg_set_asCapable:domainInde=0, portIndex=1, ascapable=1
INF:gptp:000025-125373:gm_stable:gm_unstable_proc:domainIndex=0
INF:gptp:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=1
INF:gptp:000025-125730:gm_stable:gm_unstable_proc:domainIndex=0
INF:gptp:000025-249853:setSyncTwoStep_txSync:domainIndex=0, portIndex=1, sync gap=25250msec
INF:gptp:000025-250644:setFollowUp_txFollowUp:domainIndex=0, portIndex=1, fup gap=25250msec
     25.392s : CPU load =   2.40 %
INF:gptp:000025-586573:domainIndex=0, GM changed old=70:FF:76:FF:FE:1D:EC:F2, new=00:68:EB:FF:FE:BC:85:09
INF:gptp:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=0
INF:gptp:000025-587096:gm_stable:gm_unstable_proc:domainIndex=0
INF:gptp:gptpclock_set_gmsync:gptpInstanceIndex=0, domainIndex=0, gmstate=1
INF:gptp:set_phase_offsetGM:domainIndex=0, New adjustment(New GM?)
INF:gptp:set_phase_offsetGM:domainIndex=0, offset adjustment, diff=1729593297172961483
INF:gptp:set_phase_offsetGM:domainIndex=0, offset adjustment by Freq., diff=-11200
INF:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-8670nsec
INF:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate skip update, GMdiff=-6050nsec
INF:avtp:avbtp_rec_ts_check:big skip from old_pts=0 to timestamp=1729593323415821858
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:gptp:set_phase_offsetGM:domainIndex=0, stable
IFV:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate to 16894ppb, GMdiff=-3500nsec
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
IFV:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate to 34041ppb, GMdiff=-1316nsec
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
IFV:gptp:domainIndex=0, clock_master_sync_receive:the master clock rate to 47115ppb, GMdiff=309nsec
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits
INF:avtp:[RX] frame337 wlen=6144 bits

\endcode

# See Also

\ref NETWORKING
