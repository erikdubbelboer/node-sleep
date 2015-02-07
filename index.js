
try {
  module.exports = require('./build/Release/node_sleep.node');
} catch (e) {
  console.log('sleep: using busy loop fallback');

  module.exports = {
    sleep: function(s) {
      var e = new Date().getTime() + (s * 1000);

      while (new Date().getTime() <= e) {
        ;
      }
    },

    usleep: function(s) {
      var e = new Date().getTime() + (s / 1000);

      while (new Date().getTime() <= e) {
        ;
      }
    }
  };
}

