#!/bin/bash

function get_pid {
    psaux_line=`ps aux | grep program-runner | grep $1 | grep -v bash`
    name=`echo $psaux_line | awk '{print $12'}`
    pid=`echo $psaux_line | awk '{print $2}'` 
}
