workspace(
    name = "conway_rts",
)

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
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

###############
# uwebsockets #
###############
http_archive(
    name = "uwebsockets",
    build_file = "BUILD.uwebsockets.bazel",
    sha256 = "6794e7895eb8cc182024a0ae482a581eaa82f55f7cca53ae88b30738449f3cb9",
    strip_prefix = "uWebSockets-20.51.0",
    url = "https://github.com/uNetworking/uWebSockets/archive/refs/tags/v20.51.0.tar.gz",
)

git_repository(
    name = "usockets",
    build_file = "BUILD.usockets.bazel",
    commit = "8cd4cb66eb061b2594ca114b9ea1ead64613ad4b",  # v0.8.6
    remote = "git@github.com:uNetworking/uSockets.git",
)

git_repository(
    name = "boringssl",
    build_file = "BUILD.boringssl.bazel",
    commit = "1ccef4908ce04adc6d246262846f3cd8a111fa44",  # specific version used with usockets v0.8.6
    remote = "git@github.com:google/boringssl.git",
)

git_repository(
    name = "lsquic",
    build_file = "BUILD.lsquic.bazel",
    commit = "3bbf683f25ab84826951350c57ae226c88c54422",  # v3.2.0
    recursive_init_submodules = True,
    remote = "git@github.com:litespeedtech/lsquic.git",
)

http_archive(
    name = "libuv",
    build_file = "BUILD.libuv.bazel",
    sha256 = "d50af7e6d72526db137e66fad812421c8a1cae09d146b0ec2bb9a22c5f23ba93",
    strip_prefix = "libuv-1.47.0",
    url = "https://github.com/libuv/libuv/archive/refs/tags/v1.47.0.tar.gz",
)

http_archive(
    name = "zlib",
    build_file = "BUILD.zlib.bazel",
    sha256 = "ff0ba4c292013dbc27530b3a81e1f9a813cd39de01ca5e0f8bf355702efa593e",
    strip_prefix = "zlib-1.3",
    url = "https://github.com/madler/zlib/releases/download/v1.3/zlib-1.3.tar.gz",
)
