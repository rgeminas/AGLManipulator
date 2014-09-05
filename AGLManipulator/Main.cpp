// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "Servo.h"
#include "HttpWrapper.h"

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

const int servoPins[6] { 0, 1, 2, 3, 4, 5 };
double desiredPos[4] {0, 0, 0, 0};

int manipulatorAngles[6] {90, 90, 90, 90, 90, 90};

void setup()
{
	// Setup servo pins as output
	for (auto srv : servoPins)
		pinMode(srv, OUTPUT);       // Configure the pin for OUTPUT so you can turn on the LED.
}

void loop()
{

	/*
		1. Read command from somewhere (zmq socket???)
		2. Translate command into desiredPos
		3. 
	*/
	//Variables 

	agl::ReadHttpData(L"", L"");
    digitalWrite(servoPins[0], HIGH);   // turn the LED on by making the voltage HIGH
    Log(L"LED ON\n");
    delay(1000);               // wait for a second
}