
let common = system.getScript("/common");

/*
Missing IPs:
ADC
*/
const driverVer = {
    "ecap": {
        version: "v0",
    },
    "epwm": {
        version: "v0",
    },
    "gpio":{
        version:"v0_1",
    },
    "i2c": {
        version: "v0",
    },
    "ipc": {
        version: "v0",
    },
    "mcan": {
        version: "v0",
    },
    "mcasp": {
        version: "v1",
    },
    "sciclient": {
        version: "v0",
    },
    "bootloader": {
        version: "v0",
    },
    "mmcsd": {
        version: "v0", //version check!
    },
    "gtc": {
        version: "v0",
    },
    "ospi": {
        version: "v0",
    },
    "uart": {
        version: "v0",
    },
    "udma": {
        version: "v0",
    },
    "mcspi": {
        version: "v0",
    },
};

const topModules_wkup = [
    "/drivers/gpio/gpio",
    "/drivers/i2c/i2c",
    "/drivers/uart/uart",
    "/drivers/udma/udma",
];

const topModules_main = [
    "/drivers/ecap/ecap",
    "/drivers/epwm/epwm",
    "/drivers/gpio/gpio",
    "/drivers/i2c/i2c",
    "/drivers/mcspi/mcspi",
    "/drivers/uart/uart",
    "/drivers/udma/udma",
];

const topModules_c75 = [
    "/drivers/ecap/ecap",
    "/drivers/epwm/epwm",
    "/drivers/gpio/gpio",
    "/drivers/i2c/i2c",
    "/drivers/mcspi/mcspi",
    "/drivers/uart/uart",
    "/drivers/udma/udma",
];

function getCpuID() { // Work needed
    let corename_map = {
        "wkup-r5fss0-0" : "CSL_CORE_ID_WKUP_R5FSS0_0",
        "r5fss0-0" : "CSL_CORE_ID_R5FSS0_0",
        "r5fss0-1" : "CSL_CORE_ID_R5FSS0_1",
        "r5fss1-0" : "CSL_CORE_ID_R5FSS1_0",
        "r5fss1-1" : "CSL_CORE_ID_R5FSS1_1",
        "c75ss0-0" : "CSL_CORE_ID_C75SS0_0",
        "c75ss1-0" : "CSL_CORE_ID_C75SS1_0",
    };

    return corename_map[common.getSelfSysCfgCoreName()];
}

exports = {
    getTopModules: function() {

        let topModules = topModules_wkup;

        if(common.getSelfSysCfgCoreName().includes("wkup-r5fss0-0")) {
            topModules = topModules_wkup;
        }
        else if(common.getSelfSysCfgCoreName().includes("r5fss")) {
            topModules = topModules_main;
        }else if(common.getSelfSysCfgCoreName().includes("c75ss")){
            topModules = topModules_c75;
        }

        return topModules;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
    getCpuID,
};
