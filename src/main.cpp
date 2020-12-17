#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Pin.h>
#include <MotionDetector.h>
#include <GsmModule.h>
#include <GsmAlert.h>
#include <Time.h>

Time time;
MotionDetector motionDetector({new Pin(7)});
SoftwareSerial gsmStream(6, 5);
GsmModule gsm(gsmStream);
GsmAlert alert(motionDetector, gsm, time, "+7xxxxxxxxxx");

void setup()
{
	Serial.begin(9600);
	gsmStream.begin(9600);
	gsmStream.setTimeout(5000);
	alert.begin();
}

void loop()
{
	alert.update();
	time.delay(100);
}