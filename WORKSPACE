workspace(
  name = "conway_rts",
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
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

# Emscripten toolchain
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
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