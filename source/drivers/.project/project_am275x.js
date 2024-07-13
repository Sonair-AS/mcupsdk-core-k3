let path = require('path');

let device = "am275x";

const files_r5f = {
    common: [
        "pinmux.c",
        "soc.c",
    ],
};

const files_wkup_r5f = {
    common: [
        "pinmux.c",
        "soc.c",
    ]
};

const files_c75 = {
    common: [
        "pinmux.c",
        "soc.c",
    ],
};

const filedirs = {
    common: [
        "pinmux/am275x",
        "soc/am275x",
    ],
};

const defines_wkup_r5 = {
    common: [
        "ENABLE_SCICLIENT_DIRECT",
    ],
};

const defines_r5 = {
    common: [
        "MCU_R5",
    ],
};



const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "wkup-r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "c75x", cgt: "ti-c7000"},
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

    build_property.filedirs = filedirs;

    if(buildOption.cpu.match(/wkup-r5f*/)) {
        build_property.files = files_wkup_r5f;
        build_property.defines = defines_wkup_r5;
    }else if(buildOption.cpu.match(/r5f*/)) {
        build_property.files = files_r5f;
        build_property.defines = defines_r5;
    }else if(buildOption.cpu.match(/c75*/)) {
        build_property.files = files_c75;
    }
    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
