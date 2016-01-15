#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: ./restart.sh [part of program name]\n"
    exit 1
fi

psaux_line=`ps aux | grep program-runner | grep $1`
pid=`echo $psaux_line | awk '{print $2}'`

kill -s USR2 $pid
kill -s USR1 $pid
