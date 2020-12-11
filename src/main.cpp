#include <Arduino.h>
#include <SoftwareSerial.h>

const int sensorsCount = 2;
const uint8_t sensorPins[sensorsCount] = {5, 5};

SoftwareSerial gsm(8, 9);
const String sendSmsPhone = "+7xxxxxxxxx";
const long gsmTimeout = 10000;

bool moving;


String waitResponse()
{
	String response = "";
	auto timeout = millis() + gsmTimeout;

	while (!gsm.available() && millis() < timeout)
		delay(1);
	
	if (gsm.available())
		response = gsm.readString();
	else
		Serial.println("Timeout...");

	return response;
}

String sendATCommand(const String &cmd, bool waiting)
{
	Serial.println(cmd);
	gsm.println(cmd);

	if (waiting)
	{
		auto response = waitResponse();

		if (response.startsWith(cmd))
			response = response.substring(response.indexOf("\r", cmd.length()) + 2);

		Serial.println(response);
		return response;
	}

	return "";
}

void sendSms(const String &phone, const String &message)
{
	sendATCommand("AT+CMGS=\"" + phone + "\"", true);
	sendATCommand(message + "\r\n" + (String) ((char)26), true);
}

bool hasMoving()
{
	for (auto i = 0; i < sensorsCount; i++)
	{
		if (digitalRead(sensorPins[i]) == LOW)
			return false;
	}

	return true;
}

void initGsm()
{
	sendATCommand("AT+CMGF=1;&W", true);
	sendATCommand("AT+CSCS=\"GSM\"", true);
}

void setup()
{
	Serial.begin(9600);
	gsm.begin(9600);

	for (auto i = 0; i < sensorsCount; i++)
		pinMode(sensorPins[i], INPUT);

	moving = hasMoving();
	
	initGsm();

	sendSms(sendSmsPhone, "Start");
}

void detectMoving()
{
	auto value = hasMoving();
	auto changed = value != moving;
	moving = value;
	
	if (!changed)
		return;
	
	Serial.println(moving ? "Alarm! Moving detected!!!!" : "No moving");

	if (moving)
	{
		sendSms(sendSmsPhone, "Ograblenie!");
		delay(10000);
	}
}

void loop()
{
	detectMoving();

	delay(100);
}