#pragma once

#include <Arduino.h>

class Sms
{
public:
	inline Sms() : id(0) {}
	uint8_t id;
	String phone;
	String message;
};
