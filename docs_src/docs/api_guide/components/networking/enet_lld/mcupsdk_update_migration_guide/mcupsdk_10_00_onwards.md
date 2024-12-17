# Version Updates from earlier SDKs to Latest {#enet_mcupsdk_10_00_update}

[TOC]
## Change Set
Change-1 : ENET(CPSW) and ENET(ICSS) pinmux configuration.
Change-2 : Support to configure link parameters in Sysconfig GUI tool.
Change-3 : ENET(CPSW) and ENET(ICSS) Example paths have been changed.
Change-4 : Support to add and configure Ethernet PHY module through sysconfig-GUI tool.

## While upgrading from 10.00 SDK
### Change-1 Description
In MCU+ SDK version of 10.01, ENET(CPSW) and ENET(ICSS) related examples showcasing various features have been moved from ${MCU_PLUS_SDK_PATH}/examples/networking to ${MCU_PLUS_SDK_PATH}/source/networking/enet/core/examples

### Change-1 Impact
The above change makes older build commands to build Networking examples no longer supported, and it has to be updated with correct path.

### Change-1 Solution
Please use "make help DEVICE=<dev_name>" to get the correct location and build commands for the examples.
\note For Windows , please use "gmake" instead of "make"
 
### Change-2 Description
In MCU+ SDK version of 10.01, support to add custom PHY and configure it through sysconfig tool has been added, and this needs updates in corresponding example.syscfg file to be compatible with latest changes

### Change-2 Impact
This will need addition of the corresponding sysconfig tool changes to add the ethernet phy module and configure it.

### Change-2 Solution
- Refer \ref phy_integration_guide_top
