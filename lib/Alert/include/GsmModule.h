#pragma once

#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include <IGsmModule.h>

class GsmModule : public IGsmModule
{
public:
    GsmModule(Stream &stream, unsigned long timeout = 10000);
	void begin();
	bool sendSms(const String &phone, const String &message);
	bool deleteSms(uint8_t id);
	std::vector<Sms> readSms();
	void update();
	inline String sendUssd(const String &ussd) { return gsm.sendUSSD(ussd); }
private:
	unsigned long timeout;

	TinyGsm gsm;
};