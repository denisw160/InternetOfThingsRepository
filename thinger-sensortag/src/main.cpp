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
#include <string>
#include <thread>
#include <map>

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>

#include "thinger/thinger.h"

using namespace std;

#define SENSORTAG_CMD       "python sensortagcollector.py"

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

// Sample
//  {"deviceuid":"a0:e6:f8:ae:37:80","devicename":"sensorYellow","accelerometer":[0.094482421875,0.034912109375,0.8818359375]}
//  {"deviceuid":"a0:e6:f8:ae:37:80","devicename":"sensorYellow","lightmeter":67.56}
//  {"deviceuid":"a0:e6:f8:ae:37:80","devicename":"sensorYellow","humidity":[27.2225952148,42.2302246094]}
//  {"deviceuid":"a0:e6:f8:ae:37:80","devicename":"sensorYellow","barometer":[27.24,1012.23]}

class Sensor {
public:
    float accelerometerX;
    float accelerometerY;
    float accelerometerZ;
    float lightmeter;
    float temperature;
    float humidity;
    float barometer;
};

map<string, Sensor> sensors;

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

// TODO Restart on error
void readSensorTagData(std::string parameter) {
    FILE *fp;
    char inputJson[1035];

    /* Open the command for reading. */
    std::string cmdString = SENSORTAG_CMD;
    cmdString.append(parameter);
    const char *cmd = cmdString.c_str();

    // Only for debugging
    printf("DEBUG: CMD %s\n", cmd);

    // TODO try-finally
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    // JSON helper
    Json::Value root;
    Json::Reader reader;
    Json::StreamWriterBuilder builder;
    builder["indentation"] = ""; // whitespace-less output


    /* Read the output a line at a time - output it. */
    while (fgets(inputJson, sizeof(inputJson) - 1, fp) != NULL) {
        // Only for debugging
        printf("DEBUG: INPUT %s", inputJson);

        // Skip line if not parse is unsuccessfully
        bool parsingSuccessful = reader.parse(inputJson, root); //parse process
        if (!parsingSuccessful) {
            printf("ERROR: LINE %s", inputJson);
            cout << "Failed to parse" << reader.getFormattedErrorMessages();
            continue;
        }

        // Get name of the sensor
        Json::Value sensorNameValue = root.get("devicename", "none"); // return none if no devicename
        std::string sensorNameString = Json::writeString(builder, sensorNameValue);
        const char *sensorName = sensorNameString.c_str();
        // Only for debugging
        printf("DEBUG: SENSOR %s\n", sensorName);

        bool containsSensor = sensors.count(sensorName) == 1;
        if (containsSensor) {
            Sensor sensor = sensors[sensorName];
            if (root.isMember("accelerometer")) {
                Json::Value acc = root["accelerometer"];
                sensor.accelerometerX = acc[0].asFloat();
                sensor.accelerometerY = acc[1].asFloat();
                sensor.accelerometerZ = acc[2].asFloat();
            } else if (root.isMember("humidity")) {
                Json::Value acc = root["humidity"];
                sensor.temperature = acc[0].asFloat();
                sensor.humidity = acc[1].asFloat();
            } else if (root.isMember("barometer")) {
                Json::Value acc = root["barometer"];
                sensor.temperature = acc[0].asFloat();
                sensor.barometer = acc[1].asFloat();
            } else if (root.isMember("lightmeter")) {
                Json::Value acc = root["lightmeter"];
                sensor.lightmeter = acc.asFloat();
            } else {
                printf("WARN: Unknown value %s", inputJson);
            }

        }
    }

    /* close */
    pclose(fp);
    printf("SensorTag terminated\n");
}

// Arguments are UserId, DeviceId, DeviceCredential, C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow
int main(int argc, char *argv[]) {
    printf("Starting Gateway for SensorTags\n");
    printf(" Reading from %i sensors\n", argc - 4);

    // only for debugging
    for (int i = 0; i < argc; ++i) {
        printf("argv %i: %s\n", i, argv[i]);
    }

    if (argc < 5) {
        printf("Necessary arguments not found, please use [USER_ID] [DEVICE_ID] [DEVICE_CREDENTIAL] C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow or something like that\n");
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

    // Adding API for sensors from command line
    std::string parameter = " -d";
    for (int i = 4; i < argc; ++i) {
        printf(" Adding sensor %i: %s\n", i, argv[i]);
        parameter.append(" ");
        parameter.append(argv[i]);

        static char *sensorName;
        strtok(argv[i], "=");
        sensorName = strtok(nullptr, "=");

        Sensor sensor{};
        sensors[sensorName] = sensor;

        thing[sensorName] >> [](pson &out) {
            out["accelerometerX"] = sensors[sensorName].accelerometerX;
            out["accelerometerY"] = sensors[sensorName].accelerometerY;
            out["accelerometerZ"] = sensors[sensorName].accelerometerZ;
            out["lightmeter"] = sensors[sensorName].lightmeter;
            out["temperature"] = sensors[sensorName].temperature;
            out["humidity"] = sensors[sensorName].humidity;
            out["barometer"] = sensors[sensorName].barometer;
        };
    }

    thread t(readSensorTagData, parameter);
    thing.start();
    return 0;
}
