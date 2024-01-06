import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import { ALIASES } from "../vite.config.mts";

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [react()],
  root: "client",
  build: {
    outDir: "../dist",
  },
  resolve: {
    alias: ALIASES,
  },
});
