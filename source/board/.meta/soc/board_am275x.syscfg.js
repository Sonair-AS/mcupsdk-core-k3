
let common = system.getScript("/common");

const driverVer = {
};

const topModules_r5 = [
    "/board/led/led",
    "/board/eeprom/eeprom",
];
const topModules_wkup_r5 = [
];

const topModules_c75x = [
];

exports = {
    getTopModules: function() {
    if (common.getSelfSysCfgCoreName().match(/wkup-r5f*/))
        {
            return topModules_wkup_r5;
        }
        else if (common.getSelfSysCfgCoreName().match(/c75*/))
        {
            return topModules_c75x;
        }

        return topModules_r5;
    },
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
    getDriverInstanceValid: function(driverName) {
        let valid = false;
        if(driverName in driverVer)
        {
            valid = true;
        }
        return valid;
    }

};
