#pragma once

#include <IGsmModule.h>

class GsmModuleFake : public IGsmModule
{
public:
	inline GsmModuleFake() : started(false) {}
	inline void begin() { started = true; }
	inline void sendSms(const String &phone, const String &message) { this->phone = phone; this->message = message; }
public:
	bool started;
	String phone;
	String message;
};
