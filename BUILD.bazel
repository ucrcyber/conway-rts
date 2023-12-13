load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
  name = "vector2",
  srcs = ["src/Vector2.cpp"],
  hdrs = ["include/Vector2.hpp", "include/ISerializable.hpp"],
  copts = ["-I include"],
)

filegroup(
  name = "conway",
  srcs = [
    "//client:conway_lib_wasm",
    "//proto:vector2_proto_js",
  ],
)