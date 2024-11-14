let path = require('path');

let device = "am275x";


const files_r5f={
    common: [
        "eeprom.c",
        "eeprom_at24c512c.c",
        "flash.c",
        "flash_nand_ospi.c",
        "flash_nor_ospi.c",
        "ioexp_tca6416.c",
        "ioexp_tca6424.c",
        "led.c",
        "led_gpio.c",
        "led_tpic2810.c",
        "led_ioexp_am275x_evm.c",
        "nor_spi_sfdp.c",
    ],
};

const files_c75x = {
    common: [
        "flash.c",
        "flash_nand_ospi.c",
        "flash_nor_ospi.c",
        "ioexp_tca6424.c",
        "ioexp_tca6416.c",
        "led.c",
        "led_ioexp_am275x_evm.c",
        "nor_spi_sfdp.c",
    ],
};

const filedirs = {
    common: [
        "eeprom",
        "flash",
        "flash/ospi",
        "flash/sfdp",
        "ioexp",
        "led",
    ],
};

const buildOptionCombos = [
    { device: device, cpu: "r5f", cgt: "ti-arm-clang"},
    { device: device, cpu: "c75x", cgt: "ti-c7000"},
];

function getComponentProperty() {
    let property = {};

    property.dirPath = path.resolve(__dirname, "..");
    property.type = "library";
    property.name = "board";
    property.isInternal = false;
    property.buildOptionCombos = buildOptionCombos;

    return property;
}

function getComponentBuildProperty(buildOption) {
    let build_property = {};

    build_property.filedirs = filedirs;
    if(buildOption.cpu.match(/r5f*/))
    {
        build_property.files = files_r5f;
    }
    else if(buildOption.cpu.match(/c75x*/))
    {
        build_property.files = files_c75x;
    }

    return build_property;
}

module.exports = {
    getComponentProperty,
    getComponentBuildProperty,
};
