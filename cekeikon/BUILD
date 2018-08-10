# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
  name = "main",
  srcs = glob(["src/*.cpp"]),
  hdrs = glob(["src/*.h"]),
  deps = ["@opencv//:core"],
  visibility = ["//visibility:public"]
)