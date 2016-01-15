Introduction
---------------------------------------------------------
program-runner is a small application that simplifies running programs in a terminal that require starting/stopping often. This is useful during development when a project consists of multiple processes. Instead of having a script that starts the programs in the background, thus removing the ability to view stdout/stderr or having to go through multiple terminal windows to start/stop the processes you can use program-runner.


Example usage
---------------------------------------------------------

    program-runner /home/myuser/myserverprogram

This process will wait for a signal to start the specified program. You can make it start the specified program by executing:

    program-runner-start myserverprogram

This will produce the following output:

    [program-runner] starting program
    
You can also stop the program:

    program-runner-stop myserverprogram

Or restart it:

    program-runner-restart myserverprogram

The argument specified to program-runner-start/stop/restart only has to be part of the path to the actual program you specified to program-runner. It looks at the process list to identify which instance of program-runner to send the signal to.

You can create your own script that starts/stops multiple instances of program-runner.


Building / Installing
---------------------------------------------------------

    make
    sudo make install

This will build program-runner and install it to /usr/bin.


Uninstalling
---------------------------------------------------------

    sudo make uninstall

