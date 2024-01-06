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
git_repository(
    name = "emsdk",
    commit = "9347bc393b94a17b93450bbc98bc3f66cef2aeb0",  # 3.1.51 + 2 commits (to patch windows bazel wasm_cc_binary)
    remote = "git@github.com:emscripten-core/emsdk.git",
    strip_prefix = "bazel",
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
    build_file = "@//externals:BUILD.uwebsockets.bazel",
    sha256 = "6794e7895eb8cc182024a0ae482a581eaa82f55f7cca53ae88b30738449f3cb9",
    strip_prefix = "uWebSockets-20.51.0",
    url = "https://github.com/uNetworking/uWebSockets/archive/refs/tags/v20.51.0.tar.gz",
)

http_archive(
    name = "usockets",
    build_file = "@//externals:BUILD.usockets.bazel",
    integrity = "sha256-FuuhM90z6t4vX43YdhLAS13XEQZuBHHGDWQaL2qYjxY=",
    strip_prefix = "uSockets-0.8.6",
    url = "https://github.com/uNetworking/uSockets/archive/refs/tags/v0.8.6.tar.gz",
)

git_repository(
    name = "boringssl",
    build_file = "@//externals:BUILD.boringssl.bazel",
    commit = "1ccef4908ce04adc6d246262846f3cd8a111fa44",  # specific version used with usockets v0.8.6
    remote = "git@github.com:google/boringssl.git",
)

git_repository(
    name = "lsquic",
    build_file = "@//externals:BUILD.lsquic.bazel",
    commit = "3bbf683f25ab84826951350c57ae226c88c54422",  # v3.2.0
    recursive_init_submodules = True,
    remote = "git@github.com:litespeedtech/lsquic.git",
)

http_archive(
    name = "libuv",
    build_file = "@//externals:BUILD.libuv.bazel",
    sha256 = "d50af7e6d72526db137e66fad812421c8a1cae09d146b0ec2bb9a22c5f23ba93",
    strip_prefix = "libuv-1.47.0",
    url = "https://github.com/libuv/libuv/archive/refs/tags/v1.47.0.tar.gz",
)
