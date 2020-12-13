#include <GsmModule.h>
#include <SmsParser.h>

GsmModule::GsmModule(Stream &stream, ITime *time, unsigned long timeout) : gsm(stream)
{
	this->time = time;
	this->timeout = timeout;
}

void GsmModule::begin()
{
	gsm.sendAT(GF("+CMGF=1"));
	gsm.waitResponse();
	gsm.sendAT(GF("+CSDH=1"));
	gsm.waitResponse();
}

bool GsmModule::sendSms(const String &phone, const String &message)
{
	return gsm.sendSMS(phone, message);
}

std::vector<Sms> GsmModule::readSms()
{
	std::vector<Sms> result;
	SmsParser parser;

	gsm.sendAT(GF("+CMGL=\"REC UNREAD\""));

	while (true)
	{
		if (!gsm.waitResponse(5000L, GF(GSM_NL "+CMGL:"), GFP(GSM_OK), GFP(GSM_ERROR)))
		{
			Serial.println("noRead");
			break;
		}

		String data = gsm.stream.readStringUntil('\n');
		data.trim();
		if (data.length() == 0)
			break;

		Serial.println("Data: " + data);
		String message = gsm.stream.readStringUntil('\n');
		message.trim();
		Serial.println("Message: " + message);
		
		Sms sms;
		if (parser.parse(data, message, sms))
			result.push_back(sms);
	}

	return result;
}

bool GsmModule::deleteSms(uint8_t id)
{
	gsm.sendAT(GF("+CMGD="), id, GF(","), 0);
	return gsm.waitResponse(5000L) == 1;
}
