sleep
=====

Add `sleep()` and `usleep()` to nodejs.

This is mainly useful for debugging.

**Sleep will block execution of all javascript!**

Usage
-----

`var sleep = require('sleep');`

* `sleep.sleep(n)`: sleep for n seconds
* `sleep.usleep(n)`: sleep for n microseconds (1 second is 1000000 microseconds)

