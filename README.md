[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Ferikdubbelboer%2Fnode-sleep.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2Ferikdubbelboer%2Fnode-sleep?ref=badge_shield)

sleep
=====

Add [`sleep()`][1], `msleep()` and [`usleep()`][2] to Node.js, via a C++ binding.

This is mainly useful for debugging.

**These calls will block execution of all JavaScript by halting Node.js' event loop!**

Usage
-----

    var sleep = require('sleep');

* `sleep.sleep(n)`: sleep for `n` seconds
* `sleep.msleep(n)`: sleep for `n` miliseconds
* `sleep.usleep(n)`: sleep for `n` microseconds (1 second is 1000000 microseconds)


[1]: http://linux.die.net/man/3/sleep
[2]: http://linux.die.net/man/3/usleep


## License
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Ferikdubbelboer%2Fnode-sleep.svg?type=large)](https://app.fossa.io/projects/git%2Bgithub.com%2Ferikdubbelboer%2Fnode-sleep?ref=badge_large)