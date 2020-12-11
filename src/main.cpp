#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Pin.h>
#include <GsmAlert.h>
#include <MotionDetector.h>
#include <GsmModule.h>
#include <GsmAlert.h>
#include <Time.h>

Time time;
MotionDetector motionDetector({new Pin(5)});
SoftwareSerial gsmStream(8, 9);
GsmModule gsm(&gsmStream, &time);
GsmAlert alert(&motionDetector, &gsm, "+7xxxxxxxxx");


void setup()
{
	Serial.begin(9600);
	gsmStream.begin(9600);

	alert.begin();
}


void loop()
{
	alert.update();

	time.delay(100);
}