#pragma once

#include <IGsmModule.h>

class GsmModuleFake : public IGsmModule
{
public:
	inline GsmModuleFake() : started(false), smsReaded(false), deletedSms(0) {}
	inline void begin() { started = true; }
	inline bool sendSms(const String &phone, const String &message) { this->phone = phone; this->message = message; return true; }
	inline bool deleteSms(uint8_t id)  { deletedSms = id; return true; }
	inline std::vector<Sms> readSms() { smsReaded = true; return smsList; }
	inline String sendUssd(const String &ussd) { return ussd ; }
	inline void update() { };
public:
	std::vector<Sms> smsList;
	bool started;
	bool smsReaded;
	uint8_t deletedSms;
	String phone;
	String message;
};
