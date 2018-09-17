#!/usr/bin/env bash
mkdir -p build
cd build
cp ../src/sensortagcollector.py sensortagcollector.py
cmake -DCMAKE_BUILD_TYPE=Release -DDAEMON=OFF ../
make thinger
