#!/bin/bash

make
mkdir -p package/program-runner_1.0-1/usr
mkdir -p package/program-runner_1.0-1/usr/bin
cp program-runner* package/program-runner_1.0-1/usr/bin
dpkg --build package/program-runner_1.0-1
mv package/*.deb .
