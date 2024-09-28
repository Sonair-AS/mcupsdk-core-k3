#
# Auto generated makefile
#

export MCU_PLUS_SDK_PATH?=$(abspath ../../../../../..)
include $(MCU_PLUS_SDK_PATH)/imports.mak


PROFILE?=release

LD=$(CGT_GCC_AARCH64_PATH)/bin/aarch64-none-elf-ld

MULTI_CORE_BOOTIMAGE_PATH=$(abspath .)
MULTI_CORE_BOOTIMAGE_NAME:=ipc_rpmsg_echo_system.$(PROFILE).appimage
MULTI_CORE_BOOTIMAGE_NAME_SIGNED:=$(MULTI_CORE_BOOTIMAGE_NAME).signed
MULTI_CORE_BOOTIMAGE_NAME_XIP:=ipc_rpmsg_echo_system.$(PROFILE).appimage_xip

CORE_0=--script ../wkup-r5fss0-0_freertos/example.syscfg --context wkup-r5fss0-0 --output ../wkup-r5fss0-0_freertos/ti-arm-clang/generated
CORE_1=--script ../c75ss0-0_freertos/example.syscfg --context c75ss0-0 --output ../c75ss0-0_freertos/ti-c7000/generated
CORE_2=--script ../c75ss1-0_freertos/example.syscfg --context c75ss1-0 --output ../c75ss1-0_freertos/ti-c7000/generated
CORE_3=--script ../r5fss0-0_freertos/example.syscfg --context r5fss0-0 --output ../r5fss0-0_freertos/ti-arm-clang/generated
CORE_4=--script ../r5fss0-1_freertos/example.syscfg --context r5fss0-1 --output ../r5fss0-1_freertos/ti-arm-clang/generated
CORE_5=--script ../r5fss1-0_freertos/example.syscfg --context r5fss1-0 --output ../r5fss1-0_freertos/ti-arm-clang/generated
CORE_6=--script ../r5fss1-1_freertos/example.syscfg --context r5fss1-1 --output ../r5fss1-1_freertos/ti-arm-clang/generated

CORES = \
    $(CORE_6) \
    $(CORE_5) \
    $(CORE_4) \
    $(CORE_3) \
    $(CORE_2) \
    $(CORE_1) \
    $(CORE_0) \

all: syscfg
	$(MAKE) -C ../wkup-r5fss0-0_freertos/ti-arm-clang/ all
	$(MAKE) -C ../c75ss0-0_freertos/ti-c7000/ all
	$(MAKE) -C ../c75ss1-0_freertos/ti-c7000/ all
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ all
	$(MAKE) -C ../r5fss0-1_freertos/ti-arm-clang/ all
	$(MAKE) -C ../r5fss1-0_freertos/ti-arm-clang/ all
	$(MAKE) -C ../r5fss1-1_freertos/ti-arm-clang/ all
	$(MAKE) $(MULTI_CORE_BOOTIMAGE_NAME)

clean:
	$(MAKE) -C ../wkup-r5fss0-0_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../c75ss0-0_freertos/ti-c7000/ clean
	$(MAKE) -C ../c75ss1-0_freertos/ti-c7000/ clean
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../r5fss0-1_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../r5fss1-0_freertos/ti-arm-clang/ clean
	$(MAKE) -C ../r5fss1-1_freertos/ti-arm-clang/ clean
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME)
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME_SIGNED)
	$(RM) $(MULTI_CORE_BOOTIMAGE_NAME_XIP)

scrub:
	$(MAKE) -C ../wkup-r5fss0-0_freertos/ti-arm-clang/ scrub
	$(MAKE) -C ../c75ss0-0_freertos/ti-c7000/ scrub
	$(MAKE) -C ../c75ss1-0_freertos/ti-c7000/ scrub
	$(MAKE) -C ../r5fss0-0_freertos/ti-arm-clang/ scrub
	$(MAKE) -C ../r5fss0-1_freertos/ti-arm-clang/ scrub
	$(MAKE) -C ../r5fss1-0_freertos/ti-arm-clang/ scrub
	$(MAKE) -C ../r5fss1-1_freertos/ti-arm-clang/ scrub
ifeq ($(OS),Windows_NT)
	$(RM) \*.appimage
	$(RM) \*.appimage.signed
	$(RM) \*.appimage_xip
else
	$(RM) *.appimage
	$(RM) *.appimage.signed
	$(RM) *.appimage_xip
endif

syscfg:
	@echo Generating SysConfig files ...
	$(SYSCFG_NODE) $(SYSCFG_CLI_PATH)/dist/cli.js --device AM275x --product $(SYSCFG_SDKPRODUCT) $(CORES)

syscfg-gui:
	$(SYSCFG_NWJS) $(SYSCFG_PATH) --product $(SYSCFG_SDKPRODUCT) --device AM275x --part AM2754 --package ANJ $(CORES)

#
# Generation of multi-core boot image which can be loaded by Secondary Boot Loader (SBL)
#
ifeq ($(OS),Windows_NT)
EXE_EXT=.exe
endif
BOOTIMAGE_TEMP_OUT_FILE=temp_stdout_$(PROFILE).txt

BOOTIMAGE_CORE_ID_wkup-r5fss0-0 = 0
BOOTIMAGE_CORE_ID_r5fss0-0      = 1
BOOTIMAGE_CORE_ID_r5fss0-1      = 2
BOOTIMAGE_CORE_ID_r5fss1-0      = 3
BOOTIMAGE_CORE_ID_r5fss1-1      = 4
BOOTIMAGE_CORE_ID_c75ss0-0      = 5
BOOTIMAGE_CORE_ID_c75ss1-0      = 6
BOOTIMAGE_CORE_ID_hsm-m4fss0-0  = 7
SBL_RUN_ADDRESS=0x43C00000
SBL_DEV_ID=55
MULTI_CORE_IMAGE_GEN = $(SYSCFG_NODE) $(MCU_PLUS_SDK_PATH)/tools/boot/multicoreImageGen/multicoreImageGen.js
OUTRPRC_CMD = $(SYSCFG_NODE) $(MCU_PLUS_SDK_PATH)/tools/boot/out2rprc/elf2rprc.js

MULTI_CORE_APP_PARAMS = \
    ../wkup-r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_wkup-r5fss0-0) \
    ../c75ss0-0_freertos/ti-c7000/ipc_rpmsg_echo.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_c75ss0-0) \
    ../c75ss1-0_freertos/ti-c7000/ipc_rpmsg_echo.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_c75ss1-0) \
    ../r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_r5fss0-0) \
    ../r5fss0-1_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_r5fss0-1) \
    ../r5fss1-0_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_r5fss1-0) \
    ../r5fss1-1_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc@$(BOOTIMAGE_CORE_ID_r5fss1-1) \

MULTI_CORE_APP_PARAMS_XIP = \
    ../wkup-r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc_xip@$(BOOTIMAGE_CORE_ID_wkup-r5fss0-0) \
    ../c75ss0-0_freertos/ti-c7000/ipc_rpmsg_echo.$(PROFILE).rprc_xip@$(BOOTIMAGE_CORE_ID_c75ss0-0) \
    ../c75ss1-0_freertos/ti-c7000/ipc_rpmsg_echo.$(PROFILE).rprc_xip@$(BOOTIMAGE_CORE_ID_c75ss1-0) \
    ../r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc_xip@$(BOOTIMAGE_CORE_ID_r5fss0-0) \
    ../r5fss0-1_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc_xip@$(BOOTIMAGE_CORE_ID_r5fss0-1) \
    ../r5fss1-0_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc_xip@$(BOOTIMAGE_CORE_ID_r5fss1-0) \
    ../r5fss1-1_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc_xip@$(BOOTIMAGE_CORE_ID_r5fss1-1) \

MULTI_CORE_BOOTIMAGE_DEPENDENCY = \
    ../wkup-r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc \
    ../c75ss0-0_freertos/ti-c7000/ipc_rpmsg_echo.$(PROFILE).rprc \
    ../c75ss1-0_freertos/ti-c7000/ipc_rpmsg_echo.$(PROFILE).rprc \
    ../r5fss0-0_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc \
    ../r5fss0-1_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc \
    ../r5fss1-0_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc \
    ../r5fss1-1_freertos/ti-arm-clang/ipc_rpmsg_echo.$(PROFILE).rprc \

$(MULTI_CORE_BOOTIMAGE_DEPENDENCY):

$(MULTI_CORE_BOOTIMAGE_NAME): $(MULTI_CORE_BOOTIMAGE_DEPENDENCY)
	@echo  Boot multi-core image: $@ ...
	$(MULTI_CORE_IMAGE_GEN) --devID $(SBL_DEV_ID) --out $(MULTI_CORE_BOOTIMAGE_NAME) $(MULTI_CORE_APP_PARAMS) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(MULTI_CORE_IMAGE_GEN) --devID $(SBL_DEV_ID) --out $(MULTI_CORE_BOOTIMAGE_NAME_XIP) $(MULTI_CORE_APP_PARAMS_XIP) >> $(BOOTIMAGE_TEMP_OUT_FILE)
	$(RM) $(BOOTIMAGE_TEMP_OUT_FILE)
	@echo  Boot multi-core image: $(MULTI_CORE_BOOTIMAGE_PATH)/$@ Done !!!
	@echo  .
