load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
  name = "vector2_proto",
  srcs = ["vector2.proto"],
  visibility = ["//visibility:public"],
)

# proto_library(
#   name = "vector2_proto",
#   srcs = ["vector2.proto"],
#   visibility = ["//visibility:public"],
#   deps = [":place_proto"],
# )

load("@build_stack_rules_proto//rules:proto_compile.bzl", "proto_compile")
load("@build_stack_rules_proto//rules/nodejs:proto_nodejs_library.bzl", "proto_nodejs_library")

proto_compile(
  name = "vector2_node_js_compile",
  options = {"@build_stack_rules_proto//plugin/builtin:commonjs": ["import_style=commonjs"]},
  outputs = ["vector2_pb.js"],
  plugins = ["@build_stack_rules_proto//plugin/builtin:commonjs"],
  proto = "vector2_proto",
)
proto_nodejs_library(
  name = "vector2_proto_js",
  srcs = ["vector2_pb.js"],
  visibility = ["//visibility:public"],
)

# load("@rules_proto_grpc//js:defs.bzl", "js_grpc_web_compile")
# js_grpc_web_compile(
#   name = "vector2_js_grpc",
#   protos = ["vector2_proto"],
#   # output_mode = "NO_PREFIX",
# )