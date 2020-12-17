#include <Arduino.h>
#include <unity.h>
#include <GsmAlert.h>
#include <Test/MotionDetectorFake.h>
#include <Test/GsmModuleFake.h>
#include <Test/TimeFake.h>

MotionDetectorFake detector;
GsmModuleFake gsm;
TimeFake time;

void setUp()
{
	detector = MotionDetectorFake();
	gsm = GsmModuleFake();
	time = TimeFake();
}

void tearDown()
{
}

void beginTest()
{
	GsmAlert alert(detector, gsm, time, "+7xxxxxxxxx");
    alert.begin();
    TEST_ASSERT_TRUE(detector.started);
	TEST_ASSERT_TRUE(gsm.started);
}

void sendSmsEnabled()
{
	GsmAlert alert(detector, gsm, time, "+7");
    alert.begin();
	alert.setEnabled(true);
	detector.motion = true;
	alert.update();
    TEST_ASSERT_TRUE(gsm.message != "");
	TEST_ASSERT_TRUE(gsm.phone == "+7");
}

void sendSmsDisabled()
{
	GsmAlert alert(detector, gsm, time, "+7");
    alert.begin();
	alert.setEnabled(false);
	detector.motion = true;
	alert.update();
    TEST_ASSERT_TRUE(gsm.message == "");
	TEST_ASSERT_TRUE(gsm.phone == "");
}

void readSms()
{
	GsmAlert alert(detector, gsm, time, "+7");
	alert.setReadSmsPeriod(20000);
    alert.begin();
	alert.update();
	time.delay(19999);
	alert.update();
	TEST_ASSERT_FALSE(gsm.smsReaded);
	time.delay(1);
	alert.update();
	TEST_ASSERT_TRUE(gsm.smsReaded);
	gsm.smsReaded = false;
	time.delay(19999);
	alert.update();
	TEST_ASSERT_FALSE(gsm.smsReaded);
	time.delay(4);
	alert.update();
	TEST_ASSERT_TRUE(gsm.smsReaded);
}

void deleteSmsAfterRead()
{
	GsmAlert alert(detector, gsm, time, "+7");
	alert.setReadSmsPeriod(1000);
	Sms sms;
	sms.id = 11;
	gsm.smsList.push_back(sms);
    alert.begin();
	alert.update();
	time.delay(999);
	alert.update();
	TEST_ASSERT_EQUAL(0, gsm.deletedSms);
	time.delay(1);
	alert.update();
	TEST_ASSERT_EQUAL(11, gsm.deletedSms);
	gsm.deletedSms = 0;
	time.delay(999);
	alert.update();
	TEST_ASSERT_EQUAL(0, gsm.deletedSms);
	time.delay(1);
	alert.update();
	TEST_ASSERT_EQUAL(11, gsm.deletedSms);
}

void runTests()
{
    RUN_TEST(beginTest);
	RUN_TEST(sendSmsEnabled);
	RUN_TEST(sendSmsDisabled);
	RUN_TEST(readSms);
	RUN_TEST(deleteSmsAfterRead);
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
