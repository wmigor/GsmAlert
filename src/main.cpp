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
GsmModule gsm(gsmStream, &time);
GsmAlert alert(&motionDetector, &gsm, "+7xxxxxxxxxx");
unsigned long last;

void setup()
{
	Serial.begin(9600);
	gsmStream.begin(9600);
	gsmStream.setTimeout(5000);
	last = millis();
	alert.begin();
}

void loop()
{
	alert.update();

	while (Serial.available()) 
		gsmStream.write(Serial.read());
	while(gsmStream.available()) 
		Serial.write(gsmStream.read());

	if (millis() - last > 5000)
	{
		last = millis();

		auto messages = gsm.readSms();
		for (auto sms : messages)
		{
			if (sms.message.equalsIgnoreCase("info"))
			{
				String ansver = "Status: ";
				ansver += alert.isEnabled() ? "ON" : "OFF";
				ansver += "\nCommands: info, on, off";
				gsm.sendSms(sms.phone, ansver);
			}
			else if (sms.message.equalsIgnoreCase("on"))
				alert.setEnabled(true);
			else if (sms.message.equalsIgnoreCase("off"))
				alert.setEnabled(false);
			gsm.deleteSms(sms.id);
		}
	}
	time.delay(100);
}