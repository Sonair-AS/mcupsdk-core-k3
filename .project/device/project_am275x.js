const common = require("../common.js");

const component_file_list = [
    "source/drivers/.project/project.js",
    "source/kernel/nortos/.project/project.js",
    "source/kernel/freertos/.project/project.js",
];

const device_defines = {
    common: [
        "SOC_AM275X",
    ],
};

const example_file_list = [
];

function getProjectSpecCpu(cpu) {
    let projectSpecCpu =
    {
    }

    return projectSpecCpu[cpu];
}

function getComponentList() {
    return component_file_list;
}

function getExampleList() {
    return example_file_list;
}

function getSysCfgDevice(board) {
    return "AM275x";
}

function getProjectSpecDevice(board) {
    return "AM275x";
}

function getSysCfgCpu(cpu) {
    return cpu;
}

function getSysCfgPkg(board) {
    return "ANJ";
}

function getSysCfgPart(board) {
    return "AM2754";
}

function getDevToolTirex(board) {
    return "AM275x_EVM";
}

function getProperty() {
    let property = {};

    property.defines = device_defines;

    return property;
}

function getProductNameProjectSpec() {
    return "MCU_PLUS_SDK_AM275X";
}

function getTirexId() {
    return "MCU-PLUS-SDK-AM275X";
}

function getFlashAddr() {
    return 0x60000000;
}

module.exports = {
    getComponentList,
    getExampleList,
    getSysCfgDevice,
    getSysCfgCpu,
    getSysCfgPkg,
    getSysCfgPart,
    getProjectSpecDevice,
    getProjectSpecCpu,
    getDevToolTirex,
    getProperty,
    getProductNameProjectSpec,
    getTirexId,
    getFlashAddr,
};
