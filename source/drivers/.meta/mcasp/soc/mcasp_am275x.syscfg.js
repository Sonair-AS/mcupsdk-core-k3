let common = system.getScript("/common");
let pinmux = system.getScript("/drivers/pinmux/pinmux");

let mcasp_input_clk_freq = 48000000;

const mcasp_config = [
    {
        name                        : "MCASP0",
        regBaseAddr                 : "CSL_MCASP0_CFG_BASE",
        dataRegBaseAddr             : "CSL_MCASP0_DMA_BASE",
        numSerializers              : 16,
        inputClkFreq                : mcasp_input_clk_freq,
        r5RxIntr                    : 120,
        r5TxIntr                    : 121,
        c7xRxIntr                   : 267,
        c7xTxIntr                   : 268,
        c7xRxEvent                  : 235,
        c7xTxEvent                  : 236,
        clockIds                    : ["TISCI_DEV_MCASP0"],
        clockFrequencies            : [
            {
                moduleId: "TISCI_DEV_MCASP0",
                clkId   : "TISCI_DEV_MCASP0_AUX_CLK",
                clkRate : mcasp_input_clk_freq,
            }
        ],
        udmaPdmaChannels            : [
            {
                txCh : "UDMA_PDMA_CH_MAIN0_MCASP0_TX",
                rxCh : "UDMA_PDMA_CH_MAIN0_MCASP0_RX",
            }
        ],
    },
    {
        name                        : "MCASP1",
        regBaseAddr                 : "CSL_MCASP1_CFG_BASE",
        dataRegBaseAddr             : "CSL_MCASP1_DMA_BASE",
        numSerializers              : 16,
        inputClkFreq                : mcasp_input_clk_freq,
        r5RxIntr                    : 122,
        r5TxIntr                    : 123,
        c7xRxIntr                   : 269,
        c7xTxIntr                   : 270,
        c7xRxEvent                  : 237,
        c7xTxEvent                  : 238,
        clockIds                    : ["TISCI_DEV_MCASP1"],
        clockFrequencies            : [
            {
                moduleId: "TISCI_DEV_MCASP1",
                clkId   : "TISCI_DEV_MCASP1_AUX_CLK",
                clkRate : mcasp_input_clk_freq,
            }
        ],
        udmaPdmaChannels            : [
            {
                txCh : "UDMA_PDMA_CH_MAIN0_MCASP1_TX",
                rxCh : "UDMA_PDMA_CH_MAIN0_MCASP1_RX",
            }
        ],
    },
    {
        name                        : "MCASP2",
        regBaseAddr                 : "CSL_MCASP2_CFG_BASE",
        dataRegBaseAddr             : "CSL_MCASP2_DMA_BASE",
        numSerializers              : 16,
        inputClkFreq                : mcasp_input_clk_freq,
        r5RxIntr                    : 124,
        r5TxIntr                    : 125,
        c7xRxIntr                   : 271,
        c7xTxIntr                   : 272,
        c7xRxEvent                  : 239,
        c7xTxEvent                  : 240,
        clockIds                    : ["TISCI_DEV_MCASP2"],
        clockFrequencies            : [
            {
                moduleId: "TISCI_DEV_MCASP2",
                clkId   : "TISCI_DEV_MCASP2_AUX_CLK",
                clkRate : mcasp_input_clk_freq,
            }
        ],
        udmaPdmaChannels            : [
            {
                txCh : "UDMA_PDMA_CH_MAIN0_MCASP2_TX",
                rxCh : "UDMA_PDMA_CH_MAIN0_MCASP2_RX",
            }
        ],
    },
    {
        name                        : "MCASP3",
        regBaseAddr                 : "CSL_MCASP3_CFG_BASE",
        dataRegBaseAddr             : "CSL_MCASP3_DMA_BASE",
        numSerializers              : 16,
        inputClkFreq                : mcasp_input_clk_freq,
        r5RxIntr                    : 126,
        r5TxIntr                    : 127,
        c7xRxIntr                   : 273,
        c7xTxIntr                   : 274,
        c7xRxEvent                  : 239,
        c7xTxEvent                  : 240,
        clockIds                    : ["TISCI_DEV_MCASP2"],
        clockFrequencies            : [
            {
                moduleId: "TISCI_DEV_MCASP3",
                clkId   : "TISCI_DEV_MCASP3_AUX_CLK",
                clkRate : mcasp_input_clk_freq,
            }
        ],
        udmaPdmaChannels            : [
            {
                txCh : "UDMA_PDMA_CH_MAIN0_MCASP3_TX",
                rxCh : "UDMA_PDMA_CH_MAIN0_MCASP3_RX",
            }
        ],
    },
    {
        name                        : "MCASP4",
        regBaseAddr                 : "CSL_MCASP4_CFG_BASE",
        dataRegBaseAddr             : "CSL_MCASP4_DMA_BASE",
        numSerializers              : 16,
        inputClkFreq                : mcasp_input_clk_freq,
        r5RxIntr                    : 130,
        r5TxIntr                    : 131,
        c7xRxIntr                   : 275,
        c7xTxIntr                   : 276,
        c7xRxEvent                  : 239,
        c7xTxEvent                  : 240,
        clockIds                    : ["TISCI_DEV_MCASP2"],
        clockFrequencies            : [
            {
                moduleId: "TISCI_DEV_MCASP4",
                clkId   : "TISCI_DEV_MCASP4_AUX_CLK",
                clkRate : mcasp_input_clk_freq,
            }
        ],
        udmaPdmaChannels            : [
            {
                txCh : "UDMA_PDMA_CH_MAIN0_MCASP4_TX",
                rxCh : "UDMA_PDMA_CH_MAIN0_MCASP4_RX",
            }
        ],
    }
];

let mcasp_ext_rxhclk_src = [
    { name: 0, displayName: "EXT_REFCLK1"},
    { name: 1, displayName: "HFOSC0_CLKOUT"},
    { name: 2, displayName: "AUDIO_EXT_REFCLK0"},
    { name: 3, displayName: "AUDIO_EXT_REFCLK1"},
    { name: 16, displayName: "Invalid Clock"},
];

let mcasp_ext_txhclk_src = [
    { name: 0, displayName: "EXT_REFCLK1"},
    { name: 1, displayName: "HFOSC0_CLKOUT"},
    { name: 2, displayName: "AUDIO_EXT_REFCLK0"},
    { name: 3, displayName: "AUDIO_EXT_REFCLK1"},
    { name: 16, displayName: "Invalid Clock"},
];

function getConfigArr() {
    return mcasp_config;
}

let mcas_ext_hclk_src_list = [
    "EXT_REFCLK1", "CLKOUT0", "AUDIO_EXT_REFCLK0", "AUDIO_EXT_REFCLK1"
];

function getExtClkPins() {
    return mcas_ext_hclk_src_list;
}

function getExtRxHclkSrc() {
    return mcasp_ext_rxhclk_src;
}

function getExtTxHclkSrc() {
    return mcasp_ext_txhclk_src;
}

function getPinmuxReq(txHclkSourceMux, rxHclkSourceMux)
{
    let systemResources = [];
    let pinResource = {}

    if(txHclkSourceMux == 0 || rxHclkSourceMux == 0)
    {
        pinResource = pinmux.getPinRequirements("SYSTEM", "EXT_REFCLK1", "External ref clk 1");
        pinmux.setConfigurableDefault( pinResource, "rx", true );
        systemResources.push(pinResource);
    }
    if(txHclkSourceMux == 1 || rxHclkSourceMux == 1)
    {
        pinResource = pinmux.getPinRequirements("SYSTEM", "CLKOUT0", "High Frequency Oscillator clk out 0");
        pinmux.setConfigurableDefault( pinResource, "rx", true );
        systemResources.push(pinResource);
    }
    if(txHclkSourceMux == 2 || rxHclkSourceMux == 2)
    {
        pinResource = pinmux.getPinRequirements("SYSTEM", "AUDIO_EXT_REFCLK0", "Audio external ref clk 0");
        pinmux.setConfigurableDefault( pinResource, "rx", true );
        systemResources.push(pinResource);
    }
    if(txHclkSourceMux == 3 || rxHclkSourceMux == 3)
    {
        pinResource = pinmux.getPinRequirements("SYSTEM", "AUDIO_EXT_REFCLK1", "Audio external ref clk 1");
        pinmux.setConfigurableDefault( pinResource, "rx", true );
        systemResources.push(pinResource);
    }

    return systemResources;
}

exports = {
    getConfigArr,
    mcasp_input_clk_freq,
    getExtRxHclkSrc,
    getExtTxHclkSrc,
    getExtClkPins,
    getPinmuxReq,
};
