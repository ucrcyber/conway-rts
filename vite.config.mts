/// <reference types="vitest" />
import { configDefaults, defineConfig } from "vitest/config";
import { resolve } from "path";

export const ALIASES = [
  {
    find: "@/lib-wasm",
    replacement: resolve(__dirname, "bazel-bin/client_wasm/conway_lib_wasm/conway_lib_wasm_embind"),
  },
  {
    find: "@/lib",
    replacement: resolve(__dirname, "client_wasm/conway"),
  },
  {
    find: "@/proto",
    replacement: resolve(__dirname, "build/bundle_proto"),
  }
];

// https://vitejs.dev/config/
export default defineConfig({
  resolve: {
    alias: ALIASES,
  },
  test: {
    root: '.',
    exclude: [...configDefaults.exclude, 'external', 'bazel-*/**/*'],
  },
});
