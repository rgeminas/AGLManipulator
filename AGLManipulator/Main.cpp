// Main.cpp : Defines the entry point for the console application.
//
#include <string>
#include <sstream>

#include "stdafx.h"
#include "arduino.h"
#include "Servo.h"
#include "HttpWrapper.h"

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

Servo servos[6];
const int servoPins[6] { 0, 1, 2, 3, 4, 5 };
double desiredPos[4] {0, 0, 0, 0};

int manipulatorAngles[6] {90, 90, 90, 90, 90, 90};

Servo srv;

void recvCommand(void)
{
	std::string cmd = agl::ReadHttpData(L"10.1.1.14", L"/positions", 3000);
    Log(std::wstring(cmd.begin(), cmd.end()).c_str());
    Log(L"\n");

	std::stringstream ss(cmd);
	std::string segment;
	std::vector<std::string> seglist;
	while (std::getline(ss, segment, '|'))
	{
		seglist.push_back(segment);
	}
	for (int i = 0; i < seglist.size() && i < sizeof(manipulatorAngles)/sizeof(manipulatorAngles[0]); ++i)
	{
		try
		{
			manipulatorAngles[i] = std::stoi(seglist[i]);
		}
		catch (std::exception& e)
		{
		}
	}
}

void setup()
{
	// Setup servo pins as output
	//for (auto srv : servoPins)
	//	pinMode(srv, OUTPUT);       // Configure the pin for OUTPUT so you can turn on the LED.

	//for (int i = 0; i < sizeof(servos)/sizeof(servos[0]); ++i)
	//{
	//	servos[i].attach(servoPins[i]);
	//}
	pinMode(0, OUTPUT);
	srv.attach(0);
}

void loop()
{
	recvCommand();

	//for (int i = 0; i < sizeof(servos) / sizeof(servos[0]); ++i)
	//{
	//	servos[i].write(manipulatorAngles[i]);
	//}
	srv.write(manipulatorAngles[0]);
	// Wait 1 sec
    delay(1000); 
}