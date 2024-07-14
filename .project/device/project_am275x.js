const common = require("../common.js");

const component_file_list = [
    "source/board/.project/project.js",
    "source/drivers/.project/project.js",
    "source/drivers/udma/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/.project/project.js",
    "source/drivers/device_manager/sciclient_direct/sbl/.project/project.js",
    "source/drivers/device_manager/sciserver/.project/project.js",
    "source/drivers/device_manager/self_reset/.project/project.js",
    "source/dhrystone_benchmark/.project/project.js",
    "source/kernel/nortos/.project/project.js",
    "source/kernel/freertos/.project/project.js",
    "test/unity/.project/project.js",
];


// List of components where makefile is not generated.
const component_file_list_with_makefile = [
    "source/drivers/device_manager/rm_pm_hal/.project/project.js",
    "source/drivers/device_manager/rm_pm_hal/sbl/.project/project.js",
];

const device_defines = {
    common: [
        "SOC_AM275X",
    ],
};

const example_file_list = [
    "examples/empty/.project/project_nortos.js",
    "examples/empty/.project/project_freertos.js",
    "examples/hello_world/.project/project.js",
    "examples/kernel/dpl/dpl_demo/.project/project.js",
    "examples/kernel/freertos/dhrystone_benchmark/.project/project.js",
    //"examples/kernel/freertos/memcpy_benchmark/.project/project.js",
    "examples/kernel/freertos/posix_demo/.project/project.js",
    "examples/kernel/freertos/task_switch/.project/project.js",

    // Tests
    "test/kernel/dpl/.project/project.js",
    "test/kernel/freertos/.project/project.js",
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

function getComponentListWithMakefile() {
    return component_file_list_with_makefile;
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

function getLinuxFwName(cpu) {
    return undefined;
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
    getTirexId,
    getFlashAddr,
};
