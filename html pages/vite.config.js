const { resolve } = require('path')

module.exports = {
  build: {
    rollupOptions: {
      input: {
        main: resolve(__dirname, 'index.html'),
        dome: resolve(__dirname, 'dome.html'),
        switch: resolve(__dirname, 'switch.html'),
        switchsetup: resolve(__dirname, 'switchsetup.html'),
        
      }
    }
  }
}