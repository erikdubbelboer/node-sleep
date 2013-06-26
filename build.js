
if (process.platform !== 'win32') {
  require('child_process').exec('node-gyp clean || true; node-gyp configure build', function(err, stdout, stderr) {
    console.log(stdout);
    console.log(stderr);
  });
}

