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

You can also install this as global dependency:

    npm install -g
    sleep 1
    usleep 1000

On unices or when you have already installed `sleep` and `usleep`, this
installation will not override those. You can instead then use the CLI by
running `sleepuv 1` and `usleepuv 1000`.


[1]: http://linux.die.net/man/3/sleep
[2]: http://linux.die.net/man/3/usleep
