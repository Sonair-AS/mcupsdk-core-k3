let common = system.getScript("/common");

let mmcsd_input_clk_freq = 200000000;

const mmcsd_config_r5f = [
	{
		name              : "MMC0",
		ctrlBaseAddr      : "CSL_MMCSD0_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD0_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		intrNum           : 161,
		busWidth          : "MMCSD_BUS_WIDTH_8BIT",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_AUTO", /* Make this configurable later */
		clockIds          : [ "TISCI_DEV_MMCSD0" ],
		clockFrequencies  : [
			{
				moduleId  : "TISCI_DEV_MMCSD0",
				clkId     : "TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK",
				clkRate   : mmcsd_input_clk_freq,
			},
		],
	},
];


const mmcsd_config_c75 = [
	{
		name              : "MMC0",
		ctrlBaseAddr      : "CSL_MMCSD0_CTL_CFG_BASE",
		ssBaseAddr        : "CSL_MMCSD0_SS_CFG_BASE",
		inputClkFreq      : mmcsd_input_clk_freq,
		intrNum           : 165 + 256,
		busWidth          : "MMCSD_BUS_WIDTH_8BIT",
		tuningType        : "MMCSD_PHY_TUNING_TYPE_AUTO", /* Make this configurable later */
		clockIds          : [ "TISCI_DEV_MMCSD0" ],
		clockFrequencies  : [
			{
				moduleId  : "TISCI_DEV_MMCSD0",
				clkId     : "TISCI_DEV_MMCSD0_EMMCSDSS_XIN_CLK",
				clkRate   : mmcsd_input_clk_freq,
			},
		],
	},
];


const operating_modes_sd = [
    { name : "HS", displayName : "HS"},
];

const operating_modes_emmc = [
    { name : "SDR50", displayName : "SDR50"},
    { name : "DDR50", displayName : "DDR50"},
    { name : "HS200", displayName : "HS200"},
];

function getOperatingModesSD() {
    return operating_modes_sd;
}

function getOperatingModesEMMC() {
    return operating_modes_emmc;
}

function getDefaultOperatingModeEMMC() {
    return { name : "HS200", displayName : "HS200"};
}

function getDefaultOperatingModeSD() {
    return { name : "HS", displayName : "HS"};
}

function getDefaultConfig() {
    if(common.getSelfSysCfgCoreName().includes("r5f"))
    {
        return mmcsd_config_r5f[0];
    }

    if(common.getSelfSysCfgCoreName().includes("c75"))
    {
        return mmcsd_config_c75[0];
    }
}

function getConfigArr() {
    if(common.getSelfSysCfgCoreName().includes("r5f"))
    {
        return mmcsd_config_r5f;
    }
    if(common.getSelfSysCfgCoreName().includes("c75"))
    {
        return mmcsd_config_c75;
    }


}

exports = {
	getDefaultConfig,
	getConfigArr,
    getOperatingModesSD,
    getOperatingModesEMMC,
    getDefaultOperatingModeEMMC,
    getDefaultOperatingModeSD,
};