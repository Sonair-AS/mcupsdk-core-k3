

function getInterfaceName(inst) {

    if(inst.useMcuDomainPeripherals)
        return "MCU_GPIO"

    return "GPIO";
}

function getInstanceString(moduleInstance) {
    let interfaceName = getInterfaceName(moduleInstance);
    let peripheralName = interfaceName;
    let solution = moduleInstance[peripheralName].$solution

    let splitStrings = (solution.peripheralPinName === null ) ? "": solution.peripheralPinName.split("_");
    let gpioBank = splitStrings[0];
    return gpioBank
}

function getPinIndex(moduleInstance) {
    let interfaceName = getInterfaceName(moduleInstance);
    let peripheralPinName;

    peripheralPinName = moduleInstance[interfaceName].$solution.peripheralPinName;

    if(! peripheralPinName)
        return "INVALID";

    let splitStrings = peripheralPinName.split("_");

    /* The last split is the GPIO number */
    return splitStrings[splitStrings.length-1];
}

exports = {
    getInterfaceName,
    getInstanceString,
    getPinIndex,
};
