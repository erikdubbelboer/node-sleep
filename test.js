/* globals describe, it */
var sleep = require('./');
var assert = require('assert');

function assertApproxEqual(val1, val2) {
  var epsilon = 5; // we require accuracy to the nearest N millisecond
  var diff = Math.abs(val1 - val2);
  assert.ok(diff <= epsilon);
}

describe('sleep', function () {
  it('works for normal input', function () {
    var sleepTime = 1;
    var start = new Date();
    sleep.sleep(sleepTime);
    var end = new Date();
    assertApproxEqual(end - start, sleepTime * 1000);
  });

  it('works for zero', function () {
    var sleepTime = 0;
    var start = new Date();
    sleep.sleep(sleepTime);
    var end = new Date();
    assertApproxEqual(end - start, sleepTime * 1000);
  });

  it('does not allow negative numbers', function () {
    assert.throws(function () {
      sleep.sleep(-1);
    });
  });
});

describe('usleep', function () {
  it('works for values smaller than a second', function () {
    var sleepTime = 30;
    var start = new Date();
    sleep.usleep(sleepTime);
    var end = new Date();
    assertApproxEqual(end - start, sleepTime / 1000);
  });

  it('works for values larger than a second', function () {
    this.timeout(4000); // necessary for mocha to not complain
    var sleepTime = 3000000;
    var start = new Date();
    sleep.usleep(sleepTime);
    var end = new Date();
    assertApproxEqual(end - start, sleepTime / 1000);
  });

  it('does not allow negative numbers', function () {
    assert.throws(function () {
      sleep.usleep(-100);
    });
  });
});
