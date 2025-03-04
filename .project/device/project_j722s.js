const common = require("../common.js");

const component_file_list = [
    "source/drivers/.project/project.js",
    //"source/kernel/nortos/.project/project.js",
    "source/kernel/freertos/.project/project.js",
];

// List of components where makefile is not generated.
const component_file_list_with_makefile = [
];

const device_defines = {
    common: [
        "SOC_J722S",
    ],
};

const example_file_list = [
    "examples/empty/.project/project_freertos.js",
];

function getProjectSpecCpu(cpu) {
    let projectSpecCpu =
    {
        "mcu-r5fss0-0": "MCUSS_Cortex_R5_0_0",
        "wkup-r5fss0-0": "WKUP_Cortex_R5_0_0",
        "main-r5fss0-0": "MAIN_Cortex_R5_0_0",
        "c75ss0-0": "DSP_Core_1",
        "c75ss1-0": "DSP_Core_2",
        "a53ss0-0": "CortexA53_0",
        "a53ss0-1": "CortexA53_1",
        "a53ss1-0": "CortexA53_2",
        "a53ss1-1": "CortexA53_3",
        "hsm0-0":   "HSM_Core_0"
    }

    return projectSpecCpu[cpu];
}

function getComponentList() {
    return component_file_list;
}

function getComponentListWithMakefile() {
    return component_file_list_with_makefile;
}

function getExampleList() {
    return example_file_list;
}

function getSysCfgDevice(board) {
    return "J722S_TDA4VEN_TDA4AEN_AM67";
}

function getProjectSpecDevice(board) {
    return "J722S";
}

function getSysCfgCpu(cpu) {
    return cpu;
}

function getSysCfgPkg(board) {
    return "AMW";
}

function getSysCfgPart(board) {
    return "Default";
}

function getDevToolTirex(board) {
    return "J722SXH01EVM";
}

function getProperty() {
    let property = {};

    property.defines = device_defines;

    return property;
}

function getLinuxFwName(cpu) {
    switch(cpu) {
        case "mcu-r5fss0-0":
            return "mcu-r5f0_0";
        case "wkup-r5fss0-0":
            return "wkup-r5f0_0";
        case "main-r5fss0-0":
            return "main-r5f0_0";
        case "c75ss0-0":
            return "c75ss0-0";
        case "c75ss1-0":
            return "c75ss1-0";
    }
    return undefined;
}

function getProductNameProjectSpec() {
    return "MCU_PLUS_SDK_J722S";
}

function getFlashAddr() {
    return 0x60000000;
}

module.exports = {
    getComponentList,
    getComponentListWithMakefile,
    getExampleList,
    getSysCfgDevice,
    getSysCfgCpu,
    getSysCfgPkg,
    getSysCfgPart,
    getProjectSpecDevice,
    getProjectSpecCpu,
    getDevToolTirex,
    getProperty,
    getLinuxFwName,
    getProductNameProjectSpec,
    getFlashAddr,
};
