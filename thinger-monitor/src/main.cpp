// The MIT License (MIT)
//
// Copyright (c) 2015 THINGER LTD
// Author: alvarolb@gmail.com (Alvaro Luis Bustamante)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <iostream>
#include <sstream>
#include <fstream>

#include "thinger/thinger.h"

using namespace std;

class Load {
public:
    float load1min;
    float load3min;
    float load5min;
};

class Memory {
public:
    int total;
    int free;
    int available;
    int cached;
    int swapTotal;
    int swapFree;
};

Load getLoad() {
    Load load{};
    int fileHandler;
    char fileBuffer[1024];

    fileHandler = open("/proc/loadavg", O_RDONLY);
    if (fileHandler < 0) {
        return load;
    }
    read(fileHandler, fileBuffer, sizeof(fileBuffer) - 1);
    stringstream inStream(fileBuffer);
    if (inStream.good()) {
        inStream >> load.load1min;
    }
    if (inStream.good()) {
        inStream >> load.load3min;
    }
    if (inStream.good()) {
        inStream >> load.load5min;
    }
    close(fileHandler);

    return load;
}

Memory getMemory() {
    Memory memory{};

    ifstream infile("/proc/meminfo");
    string line;
    while (getline(infile, line)) {
        stringstream inStream(line);
        if (!line.compare(0, 8, "MemTotal")) {
            inStream.ignore(256, ' ');
            inStream >> memory.total;
        } else if (!line.compare(0, 7, "MemFree")) {
            inStream.ignore(256, ' ');
            inStream >> memory.free;
        } else if (!line.compare(0, 12, "MemAvailable")) {
            inStream.ignore(256, ' ');
            inStream >> memory.available;
        } else if (!line.compare(0, 6, "Cached")) {
            inStream.ignore(256, ' ');
            inStream >> memory.cached;
        } else if (!line.compare(0, 9, "SwapTotal")) {
            inStream.ignore(256, ' ');
            inStream >> memory.swapTotal;
        } else if (!line.compare(0, 8, "SwapFree")) {
            inStream.ignore(256, ' ');
            inStream >> memory.swapFree;
        }
    }

    return memory;
}

// TODO Add temperature of the Raspberry PI

// Arguments are UserId, DeviceId, DeviceCredential
int main(int argc, char *argv[]) {
    printf("Starting Monitoring \n");

    // only for debugging
    for (int i = 0; i < argc; ++i) {
        printf("argv %i: %s\n", i, argv[i]);
    }

    if (argc < 4) {
        printf("Necessary arguments not found, please use [USER_ID] [DEVICE_ID] [DEVICE_CREDENTIAL]\n");
        exit(-1);
    }

    char *userId = argv[1];
    char *deviceId = argv[2];
    char *deviceCredential = argv[3];

    // Register on Thinger.io server (iot.thinger.io)
    thinger_device thing(userId, deviceId, deviceCredential);

    // Add API for system information
    thing["load"] >> [](pson &out) {
        Load l = getLoad();
        out["load1min"] = l.load1min;
        out["load3min"] = l.load3min;
        out["load5min"] = l.load5min;
    };

    thing["memory"] >> [](pson &out) {
        Memory m = getMemory();
        out["total"] = m.total;
        out["used"] = m.total - m.free - m.cached;
        out["free"] = m.free;
        out["available"] = m.available;
        out["cached"] = m.cached;
        out["swapTotal"] = m.swapTotal;
        out["swapUsed"] = m.swapTotal - m.swapFree;
        out["swapFree"] = m.swapFree;
    };

    thing.start();
    return 0;
}
