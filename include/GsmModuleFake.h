#pragma once

#include <IGsmModule.h>

class GsmModuleFake : public IGsmModule
{
public:
	inline GsmModuleFake() : started(false) {}
	inline void begin() { started = true; }
	inline bool sendSms(const String &phone, const String &message) { this->phone = phone; this->message = message; return true; }
	inline bool deleteSms(uint8_t id)  { return true; }
	inline std::vector<Sms> readSms() {return std::vector<Sms>(); }
public:
	bool started;
	String phone;
	String message;
};
