cc_library(
    name = "core",
    srcs = glob([
        "modules/core/src/**/*.cpp",
        "modules/core/src/**/*.hpp",
        "modules/core/include/**/*.hpp",
        "modules/core/include/**/*.h",
    ]) + [
        "custom_hal.hpp",
        "cvconfig.h",
        "opencl_kernels_core.hpp",
        "opencv2/opencv_modules.hpp",
        "version_string.inc",
    ],
    hdrs = ["modules/core/include/opencv2/core/opencl/ocl_defs.hpp"],
    copts = [
        "-D__OPENCV_BUILD",
        "-Iexternal/zlib",
    ],
    includes = [
        ".",
        "modules/core/include",
    ],
    linkopts = [
        "-ldl",
    ] + select({
        ":arm": ["-llog"],
        "//conditions:default": ["-lpthread"],
    }),
    visibility = ["//visibility:public"],
    deps = [
        "@zlib",
    ],
)

genrule(
    name = "core_kernels",
    outs = ["opencl_kernels_core.hpp"],
    cmd = """
      echo '#include "opencv2/core/ocl.hpp"' > $@
      echo '#include "opencv2/core/ocl_genbase.hpp"' > $@
      echo '#include "opencv2/core/opencl/ocl_defs.hpp"' > $@
    """,
)

genrule(
    name = "cvconfig",
    srcs = select({
        ":arm": ["cvconfig_android.h"],
        "//conditions:default": ["cvconfig_linux.h"],
    }),
    outs = ["cvconfig.h"],
    cmd = "cp $< $@",
)

genrule(
    name = "cvconfig_linux",
    outs = ["cvconfig_linux.h"],
    cmd = """
      echo '#define HAVE_PNG' >> $@
    """,
)

genrule(
    name = "cvconfig_android",
    outs = ["cvconfig_android.h"],
    cmd = """
      echo '#define HAVE_PNG' >> $@
      echo '#define ANDROID' >> $@
    """,
)

genrule(
    name = "custom_hal",
    outs = ["custom_hal.hpp"],
    cmd = "touch $@",
)

genrule(
    name = "version_string",
    outs = ["version_string.inc"],
    cmd = "echo '\"OpenCV 3.1.0\"' > $@",
)

genrule(
    name = "opencv_modules",
    outs = ["opencv2/opencv_modules.hpp"],
    cmd = """
        echo '#define HAVE_core' >> $@
        echo '#define HAVE_imgcodecs' >> $@
        echo '#define HAVE_imgproc' >> $@
        echo '#define HAVE_OPENCV_ML' >> $@
        echo '#define HAVE_OPENCV_VIDEOIO' >> $@
    """,
)

cc_library(
    name = "imgproc",
    srcs = glob([
        "modules/imgproc/src/**/*.cpp",
        "modules/imgproc/src/**/*.hpp",
        "modules/imgproc/src/**/*.h",
        "modules/imgproc/include/**/*.hpp",
        "modules/imgproc/include/**/*.h",
    ]) + ["opencl_kernels_imgproc.hpp"],
    copts = ["-D__OPENCV_BUILD"],
    includes = [
        ".",
        "modules/core/include",
        "modules/imgproc/include",
    ],
    visibility = ["//visibility:public"],
    deps = [":core"],
)

genrule(
    name = "imgproc_kernels",
    outs = ["opencl_kernels_imgproc.hpp"],
    cmd = """
      echo '#include "opencv2/core/ocl.hpp"' > $@
      echo '#include "opencv2/core/ocl_genbase.hpp"' > $@
      echo '#include "opencv2/core/opencl/ocl_defs.hpp"' > $@
    """,
)

cc_library(
    name = "ml",
    srcs = glob([
        "modules/ml/src/**/*.cpp",
        "modules/ml/src/**/*.hpp",
        "modules/ml/include/**/*.hpp",
    ]),
    copts = ["-D__OPENCV_BUILD"],
    includes = ["modules/ml/include"],
    visibility = ["//visibility:public"],
    deps = [":core"],
)

cc_library(
    name = "highgui",
    srcs = glob(
        [
            "modules/highgui/src/**/*.cpp",
            "modules/highgui/src/**/*.hpp",
            "modules/highgui/include/**/*.hpp",
            "modules/highgui/include/**/*.h",
        ],
        exclude = [
            "modules/highgui/src/window_winrt_bridge.cpp",
            "modules/highgui/src/window_carbon.cpp",
            "modules/highgui/src/window_winrt.cpp",
            "modules/highgui/src/window_w32.cpp",
            "modules/highgui/src/window_QT.cpp",
            "modules/highgui/src/window_gtk.cpp",
        ],
    ),
    hdrs = ["modules/highgui/include/opencv2/highgui.hpp"],
    copts = ["-D__OPENCV_BUILD"],
    includes = ["modules/highgui/include"],
    visibility = ["//visibility:public"],
    deps = [
        ":core",
        ":imgcodecs",
        ":videoio",
    ],
)

cc_library(
    name = "imgcodecs",
    srcs = glob([
        "modules/imgcodecs/src/**/*.cpp",
        "modules/imgcodecs/src/**/*.hpp",
        "modules/imgcodecs/include/**/*.hpp",
        "modules/imgcodecs/include/**/*.h",
    ]),
    copts = [
        "-D__OPENCV_BUILD",
        "-Iexternal/libpng_http",
        "-Iexternal/zlib",
    ],
    includes = [
        "modules/imgcodecs/include",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":core",
        ":imgproc",
        "//external:libpng",
        "//external:zlib",
    ],
)

cc_library(
    name = "videoio",
    srcs = glob(
        [
            "modules/videoio/src/**/*.cpp",
            "modules/videoio/src/**/*.hpp",
            "modules/videoio/include/**/*.hpp",
            "modules/videoio/include/**/*.h",
        ],
        exclude = [
            "modules/videoio/src/cap_giganetix.cpp",
            "modules/videoio/src/cap_gstreamer.cpp",
            "modules/videoio/src/cap_qt.cpp",
            "modules/videoio/src/cap_unicap.cpp",
            "modules/videoio/src/cap_vfw.cpp",
            "modules/videoio/src/cap_winrt/**/*",
            "modules/videoio/src/cap_winrt_bridge.cpp",
            "modules/videoio/src/cap_winrt_capture.cpp",
            "modules/videoio/src/cap_winrt_video.cpp",
            "modules/videoio/src/cap_ximea.cpp",
            "modules/videoio/src/cap_xine.cpp",
        ],
    ),
    copts = ["-D__OPENCV_BUILD"],
    includes = ["modules/videoio/include"],
    visibility = ["//visibility:public"],
    deps = [
        ":core",
        ":imgcodecs",
    ],
)

config_setting(
    name = "arm",
    values = {
        "cpu": "armeabi-v7a",
    },
)