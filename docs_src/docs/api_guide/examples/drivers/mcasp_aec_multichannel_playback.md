# MCASP AEC Multichannel Playback {#EXAMPLES_DRIVERS_MCASP_MULTICHANNEL_AEC}

[TOC]

# Introduction

This example demonstrates the multichannel playback using Audio Expansion Card.


## Audio Expansion Card Connections
- The AEC board needs to be powered with a DC Supply voltage of typical 14.4V across ( VBAT & GND ) or ( PVDD & GND ) with J14 shorted
- Make the STANDBY switches TAS0 & TAS1 on AEC in ON position
- Press the PORz switch (SW8) on the @VAR_BOARD_NAME_LOWER after turning on the supply

Speakers needs to be connected to the 8 channel audio out on each card connected to AEC1 & AEC2 slots on @VAR_BOARD_NAME_LOWER for hearing the audio.

- Mcasp is configured in TDM mode with 8 slots for each instance
- Audio out is played on 8 channels of each, thus 16 channels in total

# Supported Combinations {#EXAMPLES_DRIVERS_MCASP_MULTICHANNEL_AEC_COMBOS}

\cond SOC_AM62DX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | c75ss0-0_freertos
 Toolchain      | ti-c7000
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/mcasp/mcasp_aec_multichannel_playback

\endcond
# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Connect audio devices as mentioned in the introduction
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref DRIVERS_MCASP_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code
[MCASP] AEC Audio playback example started.
Enter your response on UART terminal
Stop the demo? (y/n) : y
\endcode
