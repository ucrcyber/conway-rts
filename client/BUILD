load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

DEFAULT_EMSCRIPTEN_LINKOPTS = [
  # LTO broken when using hermetic emsdk
  # "-flto",                          # Specify lto (has to be set on for compiler as well)
  "--bind",                           # Compiles the source code using the Embind bindings to connect C/C++ and JavaScript
  "--closure 1",                      # Run the closure compiler
  "-s MALLOC=emmalloc",               # Switch to using the much smaller implementation
  "-s ALLOW_MEMORY_GROWTH=0",         # Our example doesn't need memory growth
  "-s USE_PTHREADS=0",                # Disable pthreads
  "-s ASSERTIONS=0",                  # Turn off assertions
  # "-s EXPORT_ES6=1",                  # Export as es6 module, used for rollup
  "-s MODULARIZE=1",                  # Allows us to manually invoke the initializatio of wasm
  "-s EXPORT_NAME=createModule",      # Not used, but good to specify
  # "-s USE_ES6_IMPORT_META=1",         # needed for somethingggg --- Disable loading from import meta since we use rollup
  "-s SINGLE_FILE=1",                 # Pack all webassembly into base64
  "-s DISABLE_EXCEPTION_CATCHING=1",  # Disable all exception catching
  "-s NODEJS_CATCH_EXIT=0",           # We don't have a 'main' so disable exit() catching
]

WASM_LINKOPTS = [
  "-s WASM=0",          # Specify wasm output
]

cc_binary(
  name = "lib-wasm.js",
  srcs = ["bindings.cpp"],
  linkopts = DEFAULT_EMSCRIPTEN_LINKOPTS + WASM_LINKOPTS,
  deps = [
    "//:vector2",
    # "//hello-world/cpp:localtime",
  ],
)

wasm_cc_binary(
  name = "lib-wasm",
  cc_target = ":lib-wasm.js",
)