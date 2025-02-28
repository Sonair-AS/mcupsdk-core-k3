let path = require('path');

let device = "j722s";

const files_mcu_r5f = {
    common: [
        "csl_sec_proxy.c",
        "csl_bcdma.c",
        "csl_intaggr.c",
        "csl_lcdma_ringacc.c",
        "csl_pktdma.c",
        "csl_dru.c",
        "gpio.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "pinmux.c",
        "sciclient.c",
        "sciclient_pm.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_procboot.c",
        "sciclient_firewall.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_soc_priv.c",
        "soc.c",
        "spinlock.c",
        "uart_v0.c",
        "uart_dma.c",
        "uart_dma_udma.c",
        "utils.c",

    ],
};

const files_wkup_r5f = {
    common: [
        "csl_sec_proxy.c",
        "gpio.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "pinmux.c",
        "qos.c",
        "soc.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "spinlock.c",
        "uart_v0.c",
        "uart_dma.c",
        "uart_dma_udma.c",
    ]
};

const files_main_r5f = {
    common: [
        "csl_sec_proxy.c",
        "gpio.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "pinmux.c",
        "soc.c",
        "sciclient.c",
        "sciclient_pm.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_procboot.c",
        "sciclient_firewall.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_soc_priv.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_irq_rm.c",
        "sciclient_pm.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_procboot.c",
        "sciclient_soc_priv.c",
        "spinlock.c",
        "uart_v0.c",
        "uart_dma.c",
        "uart_dma_udma.c",
        "spinlock.c",
    ]
};

const files_c75ss0 = {
    common: [
        "csl_bcdma.c",
        "csl_sec_proxy.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "pinmux.c",
        "sciclient.c",
        "sciclient_pm.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_procboot.c",
        "sciclient_firewall.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_soc_priv.c",
        "spinlock.c",
        "soc.c",
        "uart_v0.c",
        "uart_dma.c",
        "uart_dma_udma.c",
    ],
};

const files_c75ss1 = {
    common: [
        "csl_bcdma.c",
        "csl_sec_proxy.c",
        "i2c_v0.c",
        "i2c_v0_lld.c",
        "i2c_soc.c",
        "pinmux.c",
        "sciclient.c",
        "sciclient_pm.c",
        "sciclient_rm.c",
        "sciclient_rm_irq.c",
        "sciclient_procboot.c",
        "sciclient_firewall.c",
        "sciclient_irq_rm.c",
        "sciclient_fmwSecureProxyMap.c",
        "sciclient_soc_priv.c",
        "spinlock.c",
        "soc.c",
        "uart_v0.c",
        "uart_dma.c",
        "uart_dma_udma.c",
    ],
};

const filedirs_c75ss0 = {
    common: [
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/j722s",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/j722s",
        "ipc_rpmsg/",
        "pinmux/j722s",
        "sciclient",
        "sciclient/soc/j722s",
        "spinlock/v0",
        "soc/j722s",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "hw_include/dru/v2",
        "udma",
        "udma/hw_include",
        "udma/soc",
        "udma/soc/j722s",
        "utils"
    ],
}

const filedirs_c75ss1 = {
    common: [
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/j722s",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/j722s",
        "ipc_rpmsg/",
        "pinmux/j722s",
        "sciclient",
        "sciclient/soc/j722s",
        "spinlock/v0",
        "soc/j722s",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "hw_include/dru/v2",
        "udma",
        "udma/hw_include",
        "udma/soc",
        "udma/soc/j722s",
        "utils"
    ],
}

const filedirs_mcu_r5f = {
    common: [
        "gpio/v0",
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/j722s",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/j722s",
        "ipc_rpmsg/",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "mcan/v0",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "mmcsd",
        "mmcsd/v0",
        "pinmux/j722s",
        "sciclient",
        "sciclient/soc/j722s",
        "soc/j722s",
        "spinlock/v0",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "hw_include/dru/v2",
        "udma",
        "udma/hw_include",
        "udma/soc",
        "udma/soc/j722s",
        "utils"
    ],
};

const filedirs_wkup_r5f = {
    common: [
        "bootloader",
        `bootloader/soc/j722s`,
        "ddr/v1",
        "ddr/v1/cdn_drv/",
        "ddr/v1/cdn_drv/include",
        "ddr/v1/cdn_drv/include/j722s",
        "ddr/v1/cdn_drv/include/common",
        "ddr/v1/cdn_drv/src",
        "ddr/v1/soc/j722s",
        "ddr",
        "gpio/v0",
        "gtc/v0",
        'gtc/v0/soc/j722s',
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/j722s",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/j722s",
        "ipc_rpmsg/",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "mcan/v0",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "mmcsd",
        "mmcsd/v0",
        "qos",
        "qos/v0",
        "pinmux/j722s",
        "sciclient",
        "sciclient/soc/j722s",
        "soc/j722s",
        "spinlock/v0",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "hw_include/dru/v2",
        "udma",
        "udma/hw_include",
        "udma/soc",
        "udma/soc/j722s",
        "utils"
    ],
};

const filedirs_main_r5f = {
    common: [
        "dss",
        "dss/v0",
        "dss/v0/common",
        "dss/v0/dctrl",
        "dss/v0/disp",
        "dss/v0/hw_include",
        "dss/v0/hw_include/V3",
        "dss/v0/include",
        "dss/v0/soc",
        "dss/v0/soc/j722s",
        "fvid2/v0",
        "gpio/v0",
        "csirx",
       	"csirx/v1",
        "csirx/v1/hw_include",
        "csirx/v1/hw_include/V1",
        "csirx/v1/include",
        "csirx/v1/soc",
        "csirx/v1/soc/V0",
        "csirx/v1/src",
        "csitx",
       	"csitx/v0",
        "csitx/v0/hw_include",
        "csitx/v0/include",
        "csitx/v0/soc",
        "csitx/v0/soc/V0",
        "csitx/v0/src",
        "i2c/v0",
        "i2c/v0/lld",
        "i2c/v0/soc/j722s",
        "ipc_notify/v0",
        "ipc_notify/v0/soc/j722s",
        "ipc_rpmsg/",
        "mcspi/v0",
        "mcspi/v0/dma",
        "mcspi/v0/dma/udma",
        "ospi",
        "ospi/v0",
        "ospi/v0/dma",
        "ospi/v0/dma/udma",
        "mcan/v0",
        "mmcsd",
        "mmcsd/v0",
        "pinmux/j722s",
        "sciclient",
        "sciclient/soc/j722s",
        "soc/j722s",
        "spinlock/v0",
        "uart/v0",
        "uart/v0/dma",
        "uart/v0/dma/udma",
        "hw_include/dru/v2",
        "udma",
        "udma/hw_include",
        "udma/soc",
        "udma/soc/j722s",
        "utils"
    ],
};

const defines_wkup_r5 = {
    common: [
        "WKUP_R5",
        "ENABLE_SCICLIENT_DIRECT",
    ],
};

const defines_mcu_r5 = {
    common: [
        "MCU_R5",
    ],
};

const defines_main_r5 = {
    common: [
        "MAIN_R5",
        "FVID2_CFG_TRACE_ENABLE",
        "FVID2_CFG_ASSERT_ENABLE",
    ],
};

const defines_c75ss0 = {
    common: [
    ],
};

const defines_c75ss1 = {
    common: [
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "mcu-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "wkup-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "main-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "c75ss0-0", cgt: "ti-c7000"},
    { device: device, cpu: "c75ss1-0", cgt: "ti-c7000"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "drivers";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    if(buildOption.cpu.match(/wkup-r5f*/)) {
        build_property.files = files_wkup_r5f;
        build_property.defines = defines_wkup_r5;
        build_property.filedirs = filedirs_wkup_r5f;
    }else if(buildOption.cpu.match(/mcu-r5f*/)) {
        build_property.files = files_mcu_r5f;
        build_property.defines = defines_mcu_r5;
        build_property.filedirs = filedirs_mcu_r5f;
    }else if(buildOption.cpu.match(/main-r5f*/)) {
        build_property.files = files_main_r5f;
        build_property.defines = defines_main_r5;
        build_property.filedirs = filedirs_main_r5f;
    }else if(buildOption.cpu.match(/c75ss0-0*/)) {
        build_property.files = files_c75ss0;
        build_property.defines = defines_c75ss0;
        build_property.filedirs = filedirs_c75ss0;
    }else if(buildOption.cpu.match(/c75ss1-0*/)) {
        build_property.files = files_c75ss1;
        build_property.defines = defines_c75ss1;
        build_property.filedirs = filedirs_c75ss1;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
