#include <Arduino.h>
#include <unity.h>
#include <SmsParser.h>

void setUp()
{
}

void tearDown()
{
}

void parseSuccessTest()
{
	SmsParser parser;
	Sms sms;
	auto success = parser.parse("10,\"REC UNREAD\",\"+1231231212\",\"\",\"20/12/13,10:34:00+12\"", "Hello!", sms);
	TEST_ASSERT_TRUE(success);
	TEST_ASSERT_EQUAL(10, sms.id);
	TEST_ASSERT_EQUAL_STRING("Hello!", sms.message.c_str());
	TEST_ASSERT_EQUAL_STRING("+1231231212", sms.phone.c_str());
}

void parseSuccessTest2()
{
	SmsParser parser;
	Sms sms;
	auto success = parser.parse("123,\"REC READ\",\"+123123\",\"\",\"20/12/13,10:34:00+12\"","Hello World!", sms);
	TEST_ASSERT_TRUE(success);
	TEST_ASSERT_EQUAL(123, sms.id);
	TEST_ASSERT_EQUAL_STRING("Hello World!", sms.message.c_str());
	TEST_ASSERT_EQUAL_STRING("+123123", sms.phone.c_str());
}

void parseSuccessTest3()
{
	SmsParser parser;
	Sms sms;
	auto success = parser.parse("3,\"REC UNREAD\",\"+71234567890\",\"\",\"20/12/13,20:46:12+12\",145,4,0,0,\"+79043490000\",145,4", "Hello!", sms);
	TEST_ASSERT_TRUE(success);
	TEST_ASSERT_EQUAL(3, sms.id);
	TEST_ASSERT_EQUAL_STRING("Hello!", sms.message.c_str());
	TEST_ASSERT_EQUAL_STRING("+71234567890", sms.phone.c_str());
}

void parseFailTest()
{
	SmsParser parser;
	Sms sms;
	auto success = parser.parse("10\"REC UNREAD\",\"+1231231212\",\"\",\"20/12/13,10:34:00+12\"", "Hello!", sms);
	TEST_ASSERT_FALSE(success);
}


void runTests()
{
	RUN_TEST(parseSuccessTest);
	RUN_TEST(parseSuccessTest2);
	RUN_TEST(parseSuccessTest3);
	RUN_TEST(parseFailTest);
}


void setup()
{
	UNITY_BEGIN();
	runTests();
	UNITY_END();
}

void loop()
{
	delay(500);
}
