var sleep = require('./build/Release/node_sleep.node');

sleep.msleep = function(miliseconds) {
  if (miliseconds < 1 || miliseconds % 1 != 0) {
    throw new Exception('Expected number of miliseconds');
  }
  sleep.usleep(miliseconds * 1000);
}

module.exports = sleep;

