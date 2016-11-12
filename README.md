sleep
=====

Add [`sleep()`][1] and [`usleep()`][2] to Node.js, via a C++ binding.

This is mainly useful for debugging.

**These calls will block execution of all JavaScript by halting Node.js' event loop!**

Usage
-----

    var sleep = require('sleep');

* `sleep.sleep(n)`: sleep for `n` seconds
* `sleep.usleep(n)`: sleep for `n` microseconds (1 second is 1000000 microseconds)


[1]: http://linux.die.net/man/3/sleep
[2]: http://linux.die.net/man/3/usleep
