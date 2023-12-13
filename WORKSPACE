workspace(
  name = "conway_rts",
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

####
# google test
####
http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/5ab508a01f9eb089207ee87fd547d290da39d015.zip"],
  strip_prefix = "googletest-5ab508a01f9eb089207ee87fd547d290da39d015",
)

####
# aspect rules JS (for emscripten)
####
http_archive(
  name = "aspect_rules_js",
  sha256 = "77c4ea46c27f96e4aadcc580cd608369208422cf774988594ae8a01df6642c82",
  strip_prefix = "rules_js-1.32.2",
  url = "https://github.com/aspect-build/rules_js/releases/download/v1.32.2/rules_js-v1.32.2.tar.gz",
)

load("@aspect_rules_js//js:repositories.bzl", "rules_js_dependencies")
rules_js_dependencies()

load("@rules_nodejs//nodejs:repositories.bzl", "DEFAULT_NODE_VERSION", "nodejs_register_toolchains")
nodejs_register_toolchains(
  name = "nodejs",
  node_version = DEFAULT_NODE_VERSION,
)

########################
# Emscripten toolchain #
########################
http_archive(
    name = "emsdk",
    sha256 = "5dd94e557b720800a60387ec078bf3b3a527cbd916ad74a696fe399f1544474f",
    strip_prefix = "emsdk-3.1.46/bazel",
    url = "https://github.com/emscripten-core/emsdk/archive/refs/tags/3.1.46.tar.gz",
)

load("@emsdk//:deps.bzl", emsdk_deps = "deps")
emsdk_deps()

load("@emsdk//:emscripten_deps.bzl", emsdk_emscripten_deps = "emscripten_deps")
emsdk_emscripten_deps(emscripten_version = "3.1.46")

load("@emsdk//:toolchains.bzl", "register_emscripten_toolchains")
register_emscripten_toolchains()

############
# Protobuf #
############
# Release: v2.0.1
# TargetCommitish: master
# Date: 2022-10-20 02:38:27 +0000 UTC
# URL: https://github.com/stackb/rules_proto/releases/tag/v2.0.1
# Size: 2071295 (2.1 MB)
http_archive(
    name = "build_stack_rules_proto",
    sha256 = "ac7e2966a78660e83e1ba84a06db6eda9a7659a841b6a7fd93028cd8757afbfb",
    strip_prefix = "rules_proto-2.0.1",
    urls = ["https://github.com/stackb/rules_proto/archive/v2.0.1.tar.gz"],
)

register_toolchains("@build_stack_rules_proto//toolchain:standard")

load("@build_stack_rules_proto//deps:core_deps.bzl", "core_deps")
core_deps()

load("@build_stack_rules_proto//deps:protobuf_core_deps.bzl", "protobuf_core_deps")
protobuf_core_deps()