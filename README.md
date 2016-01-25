# program-runner
[![Build Status](https://travis-ci.org/Photonios/program-runner.svg?branch=master)](https://travis-ci.org/Photonios/program-runner)

`program-runner` is a small application that simplifies running programs in a terminal that require starting/stopping often. This is useful during development when a project consists of multiple processes. Instead of having a script that starts the programs in the background, thus removing the ability to view `stdout` `stderr` or having to go through multiple terminal windows to start/stop the processes, you can use `program-runner`.


## Example usage

    $ program-runner /home/myuser/myserverprogram

This process will wait for a signal to start the specified program. You can make it start the specified program by executing:

    $ program-runner-start myserverprogram
    [program-runner] send signal (SIGUSR1) to [pid] (/home/myuser/myserverprogram)

This will produce the following output in the terminal where `program-runner` is running:

    [program-runner] starting program
    
You can also stop the program:

    $ program-runner-stop myserverprogram
    [program-runner] send signal (SIGUSR2) to [pid] (/home/myuser/myserverprogram)

Or restart it:

    $ program-runner-restart myserverprogram
    [program-runner] send signal (SIGUSR2) to [pid] (/home/myuser/myserverprogram)
    [program-runner] send signal (SIGUSR1) to [pid] (/home/myuser/myserverprogram)

The argument specified to `program-runner-start/stop/restart` only has to be part of the path to the actual program you specified to program-runner. It looks at the process list to identify which instance of `program-runner` to send the signal to. You can create your own script that starts/stops multiple instances of `program-runner`.

Optionally you can also specify extra arguments that `program-runner` should pass:

    $ program-runner /home/myuser/myserverprogram arg1 arg2

## Building / Installing
### From source

    make
    sudo make install

This will build `program-runner` and install it to `/usr/bin`.

### From *.deb package

    wget https://github.com/Photonios/program-runner/releases/download/release-1.1/program-runner_1.1-1.deb
    sudo dpkg -i program-runner_1.1-1.deb


## Uninstalling

    sudo make uninstall

