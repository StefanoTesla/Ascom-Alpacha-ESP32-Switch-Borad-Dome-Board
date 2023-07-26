const { resolve } = require('path')
import { defineConfig } from 'vite'
import { ViteMinifyPlugin } from 'vite-plugin-minify' 

module.exports = {
  build: {
    rollupOptions: {
      input: {
        main: resolve(__dirname, 'index.html'),
        dome: resolve(__dirname, 'dome.html'),
        setup: resolve(__dirname, 'setup.html'),
        switch: resolve(__dirname, 'switch.html'),
        switchsetup: resolve(__dirname, 'switchsetup.html'),
      }
    }
  },
}