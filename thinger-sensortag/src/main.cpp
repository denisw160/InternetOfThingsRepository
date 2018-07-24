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

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>

#include "thinger/thinger.h"

using namespace std;

#define USER_ID 			"xxx"
#define DEVICE_ID 			"xxx"
#define DEVICE_CREDENTIAL 	"xxx"

#define SENSORTAG_CMD 		"python ./../../sensortag/sensortagcollector.py -d "

class Load
{
  public:
    float load1min;
    float load3min;
    float load5min;
};

class Memory
{
  public:
    int total;
    int free;
    int available;
    int cached;
    int swapTotal;
    int swapFree;
};

class Sensor
{
  public:
    float x;
    float y;
    float z;
	// TODO add more data
};

map<string, Sensor> sensors;

/// old

class Accelerometer
{
  public:
    float x;
    float y;
    float z;
};

Accelerometer sensorRedAccelerometer;
Accelerometer sensorYellowAccelerometer;

/// old end

Load getLoad()
{
    Load load;
    int fileHandler;
    char fileBuffer[1024];

    fileHandler = open("/proc/loadavg", O_RDONLY);
    if (fileHandler < 0)
    {
        return load;
    }
    read(fileHandler, fileBuffer, sizeof(fileBuffer) - 1);
    stringstream ssin(fileBuffer);
    if (ssin.good())
    {
        ssin >> load.load1min;
    }
    if (ssin.good())
    {
        ssin >> load.load3min;
    }
    if (ssin.good())
    {
        ssin >> load.load5min;
    }
    close(fileHandler);

    //cout << fileBuffer;
    return load;
}

Memory getMemory()
{
    Memory memory;
    int fileHandler;
    char fileBuffer[1024];

    ifstream infile("/proc/meminfo");
    string line;
    while (getline(infile, line))
    {
        stringstream ssin(line);
        if (!line.compare(0, 8, "MemTotal"))
        {
            ssin.ignore(256, ' ');
            ssin >> memory.total;
        }
        else if (!line.compare(0, 7, "MemFree"))
        {
            ssin.ignore(256, ' ');
            ssin >> memory.free;
        }
        else if (!line.compare(0, 12, "MemAvailable"))
        {
            ssin.ignore(256, ' ');
            ssin >> memory.available;
        }
        else if (!line.compare(0, 6, "Cached"))
        {
            ssin.ignore(256, ' ');
            ssin >> memory.cached;
        }
        else if (!line.compare(0, 9, "SwapTotal"))
        {
            ssin.ignore(256, ' ');
            ssin >> memory.swapTotal;
        }
        else if (!line.compare(0, 8, "SwapFree"))
        {
            ssin.ignore(256, ' ');
            ssin >> memory.swapFree;
        }
    }

    return memory;
}

void streamSensorTag(thinger_device thing)
{
    FILE *fp;
    char json[1035];

    /* Open the command for reading. */
    fp = popen(SENSORTAG_CMD, "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    Json::Value root;
    Json::Reader reader;

    /* Read the output a line at a time - output it. */
    while (fgets(json, sizeof(json) - 1, fp) != NULL)
    {
        //printf("%s", json);

        bool parsingSuccessful = reader.parse(json, root); //parse process
        if (!parsingSuccessful)
        {
            cout << "Failed to parse" << reader.getFormattedErrorMessages();
            exit(2);
        }

        if (root.get("devicename", "none") == "sensorRed" && root.isMember("accelerometer"))
        {
            Json::Value acc = root["accelerometer"];
            sensorRedAccelerometer.x = acc[0].asFloat();
            sensorRedAccelerometer.y = acc[1].asFloat();
            sensorRedAccelerometer.z = acc[2].asFloat();
        }
        else if (root.get("devicename", "none") == "sensorYellow" && root.isMember("accelerometer"))
        {
            Json::Value acc = root["accelerometer"];
            sensorYellowAccelerometer.x = acc[0].asFloat();
            sensorYellowAccelerometer.y = acc[1].asFloat();
            sensorYellowAccelerometer.z = acc[2].asFloat();
        }

        // TODO Weitere Sensor-Daten (Licht, Temperatur)
    }

    /* close */
    pclose(fp);
    printf("SensorTag terminated\n");
}

// Arguments are C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow
int main(int argc, char* argv[])
{
	printf("argc: %i\n", argc);
	
	for(int i = 0; i < argc; ++i) {
  		printf("argv %i: %s\n", i, argv[i]);
	}
	
	if (argc < 2) {
		printf("No arguments found, please use C4:BE:84:70:F6:8B=sensorRed A0:E6:F8:AE:37:80=sensorYellow or something like that\n");
		exit(-1);
	}
	
    thinger_device thing(USER_ID, DEVICE_ID, DEVICE_CREDENTIAL);

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

	// register sensors
	for(int i = 1; i < argc; ++i) {
  		printf("Adding sensor %i: %s\n", i, argv[i]);
		
		char* pch;
		static char* sensor;
  		pch = strtok (argv[i], "=");
		pch = strtok (NULL, "=");
		
		sensor = pch;
		printf("%s\n", sensor);
		Sensor s;
		sensors[sensor] = s;
		
		thing[sensor] >> [](pson &out) {
        	out["x"] = sensors[sensor].x;
        	out["y"] = 2;//sensors[sensor].y;
        	out["z"] = 3;//sensors[sensor].z;
    	};
	}
	
	
    thing["sensorRedAccelerometer"] >> [](pson &out) {
        out["x"] = sensorRedAccelerometer.x;
        out["y"] = sensorRedAccelerometer.y;
        out["z"] = sensorRedAccelerometer.z;
    };

    thing["sensorYellowAccelerometer"] >> [](pson &out) {
        out["x"] = sensorYellowAccelerometer.x;
        out["y"] = sensorYellowAccelerometer.y;
        out["z"] = sensorYellowAccelerometer.z;
    };

    thread t(streamSensorTag, thing);
    thing.start();
    return 0;
}
