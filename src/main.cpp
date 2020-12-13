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
GsmModule gsm(gsmStream, &time);
GsmAlert alert(&motionDetector, &gsm, "+7xxxxxxxxxx");
unsigned long last;

void setup()
{
	Serial.begin(9600);
	gsmStream.begin(9600);
	last = millis();
	// alert.begin();
	gsm.begin();
}

void loop()
{
	// while (Serial.available()) 
	// 	gsmStream.write(Serial.read());
	// while(gsmStream.available()) 
	// 	Serial.write(gsmStream.read());
	// delay(100);
	
	// alert.update();


	while (Serial.available()) 
		gsmStream.write(Serial.read());
	while(gsmStream.available()) 
		Serial.write(gsmStream.read());

	if (millis() - last > 5000)
	{
		last = millis();

		auto messages = gsm.readSms();
		Serial.println(messages.size());
		for (auto sms : messages)
		{
			Serial.print("message: ");
			Serial.println(sms.message);

			sms.message.toLowerCase();

			Serial.print("message2: ");
			Serial.println(sms.message);

			Serial.print("message3: ");
			Serial.println(sms.message.length());

			if (sms.message == "info")
			{
				Serial.println("Info is empty awhile");
				gsm.sendSms(sms.phone, "Info is empty awhile");
				// gsm.deleteSms(sms.id);
			}
		}

		Serial.println("loop");
	}
	time.delay(100);
}