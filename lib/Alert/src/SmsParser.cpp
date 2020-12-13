#include <SmsParser.h>

bool SmsParser::parse(const String &data, const String &message, Sms &sms)
{
	auto index = data.indexOf(",");
	if (index < 0)
		return false;
	sms.id = (uint8_t) data.substring(0, index).toInt();
	index = data.indexOf("\",\"", index + 1);
	if (index < 0)
		return false;
	auto endIndex = data.indexOf("\",\"", index + 4);
	if (endIndex < 0)
		return false;
	sms.phone = data.substring(index + 3, endIndex);
	sms.message = message;
	return true;
}
