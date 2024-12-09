
const common = require(`../common.js`);

const cgt_common = {
    path: "CGT_TI_C7000_PATH",
    cc: "cl7x",
    ar: "ar7x",
    lnk: "cl7x",
    strip: "strip7x",
    objcopy: "",

    includes: {
        common: [
            "${CG_TOOL_ROOT}/include",
            "${MCU_PLUS_SDK_PATH}/source"
        ],
    },
    cflags: {
        common: [
            "-mv7504",
            "--abi=eabi",
            "-q",
            "-mo",
            "-pden",
            "-pds=238",
            "-pds=880",
            "-pds1110",
            "--endian=little",
            "--disable_inlining",
            "-ea.se71",
            "--emit_warnings_as_errors",
            "--diag_suppress=770", // to suppress pointer to small int conversion error
            "--diag_suppress=69", // to suppress -1 to uint32t error
            "--diag_suppress=70", // to suppress char pointer to uint32t error
        ],
        debug: [
            "-Dxdc_target_name__=C71",
            "-D_DEBUG_=1",
            //"-Dxdc_target_types__=ti/targets/elf/std.h",
            "--opt_level=0",
            "--symdebug:dwarf",
            "-DBUILD_C7X_1",
            "-DBUILD_C7X",
        ],
        release: [
            "-Dxdc_target_name__=C71",
            //"-Dxdc_target_types__=ti/targets/elf/std.h",
            "--opt_level=3",
            "--symdebug:none",
            "-DBUILD_C7X_1",
            "-DBUILD_C7X",
        ],
    },
    arflags: {
        common: [
            "rq",
        ],
    },
    lflags: {
        common: [
            "--silicon_version=7504",
            "-z",
            "--emit_warnings_as_errors",
            "--diag_suppress=10063",
            "--ram_model",
            "--warn_sections",
            "-q",
            "-x",
            ""
        ],
    },
    libdirs: {
        common: [
            "${CG_TOOL_ROOT}/lib",
        ],
    },
    libs: {
        common: [
            "libc.a",
        ],
    },
};

const cgt_common_am275x = {
    path: "CGT_TI_C7000_PATH",
    cc: "cl7x",
    ar: "ar7x",
    lnk: "cl7x",
    strip: "strip7x",
    objcopy: "",

    includes: {
        common: [
            "${CG_TOOL_ROOT}/include",
            "${MCU_PLUS_SDK_PATH}/source"
        ],
    },
    cflags: {
        common: [
            "-mv7524",
            "--abi=eabi",
            "-q",
            "-mo",
            "-pden",
            "-pds=238",
            "-pds=880",
            "-pds1110",
            "--endian=little",
            "--disable_inlining",
            "-ea.se71",
            "--emit_warnings_as_errors",
            "--diag_suppress=770", // to suppress pointer to small int conversion error
            "--diag_suppress=69", // to suppress -1 to uint32t error
            "--diag_suppress=70", // to suppress char pointer to uint32t error
        ],
        debug: [
            "-Dxdc_target_name__=C71",
            "-D_DEBUG_=1",
            //"-Dxdc_target_types__=ti/targets/elf/std.h",
            "--opt_level=0",
            "--symdebug:dwarf",
            "-DBUILD_C7X_1",
            "-DBUILD_C7X",
        ],
        release: [
            "-Dxdc_target_name__=C71",
            //"-Dxdc_target_types__=ti/targets/elf/std.h",
            "--opt_level=3",
            "--symdebug:none",
            "-DBUILD_C7X_1",
            "-DBUILD_C7X",
        ],
    },
    arflags: {
        common: [
            "rq",
        ],
    },
    lflags: {
        common: [
            "--silicon_version=7524",
            "-z",
            "--emit_warnings_as_errors",
            "--diag_suppress=10063",
            "--ram_model",
            "--warn_sections",
            "-q",
            "-x",
            ""
        ],
    },
    libdirs: {
        common: [
            "${CG_TOOL_ROOT}/lib",
        ],
    },
    libs: {
        common: [
            "libc.a",
        ],
    },
};

function getCgtOptions(cpu)
{
    let cgtOptions = {};
    if(buildOption.device=="am275x")
    {
        cgtOptions = cgt_common_am275x;
    }
    else
    {
        cgtOptions = cgt_common;
    }

    return cgtOptions;
}

module.exports = {

    getCgtOptions,
};
