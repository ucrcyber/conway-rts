workspace(
    name = "conway_rts",
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

####
# gcc toolchain
####
# http_archive(
#     name = "aspect_gcc_toolchain",
#     sha256 = "3341394b1376fb96a87ac3ca01c582f7f18e7dc5e16e8cf40880a31dd7ac0e1e",
#     strip_prefix = "gcc-toolchain-0.4.2",
#     urls = [
#         "https://github.com/aspect-build/gcc-toolchain/archive/refs/tags/0.4.2.tar.gz",
#     ],
# )

# load("@aspect_gcc_toolchain//toolchain:repositories.bzl", "gcc_toolchain_dependencies")

# gcc_toolchain_dependencies()

# load("@aspect_gcc_toolchain//toolchain:defs.bzl", "gcc_register_toolchain", "ARCHS")

# gcc_register_toolchain(
#     name = "gcc_toolchain_x86_64",
#     target_arch = ARCHS.x86_64,
# )

####
# aspect rules JS (for emscripten)
####
# load("@aspect_rules_js//js:repositories.bzl", "rules_js_dependencies")
# rules_js_dependencies()

# load("@rules_nodejs//nodejs:repositories.bzl", "DEFAULT_NODE_VERSION", "nodejs_register_toolchains")
# nodejs_register_toolchains(
#     name = "nodejs",
#     node_version = DEFAULT_NODE_VERSION,
# )

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
