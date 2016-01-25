#!/bin/bash

packagedir=package/program-runner_1.1-1
destdir=$packagedir/usr/bin

# Build
make

# Copy everything into the package
mkdir -p $destdir
cp bin/* $destdir
cp scripts/* $destdir

# Build deb packager
dpkg --build $packagedir

# Move package to dist dir 
mkdir -p dist
mv package/*.deb dist/
