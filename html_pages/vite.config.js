const { resolve } = require('path')
import viteCompression from 'vite-plugin-compression';

module.exports = {
  plugins: [viteCompression({algorithm: 'gzip', deleteOriginFile: true })],
  build: {
    rollupOptions: {
      input: {
        main: resolve(__dirname, 'index.html'),
        setup: resolve(__dirname, 'setup.html'),
      }
    },
  },
}