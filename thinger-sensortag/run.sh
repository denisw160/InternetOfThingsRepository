#!/usr/bin/env bash
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DDAEMON=OFF ../
make thinger
./thinger C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow
#./thinger A0:E6:F8:AE:37:80=sensorYellow
#./thinger