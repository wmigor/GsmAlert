#include <Arduino.h>
#include <unity.h>
#include <GsmAlert.h>
#include <MotionDetectorFake.h>
#include <GsmModuleFake.h>

void setUp()
{
}

void tearDown()
{
}

void beginTest()
{
	MotionDetectorFake detector;
	GsmModuleFake gsm;
	GsmAlert alert(&detector, &gsm, "+7xxxxxxxxx");
    alert.begin();
    TEST_ASSERT_TRUE(detector.started);
	TEST_ASSERT_TRUE(gsm.started);
}

void beginMotionEnabled()
{
	MotionDetectorFake detector;
	GsmModuleFake gsm;
	GsmAlert alert(&detector, &gsm, "+7");
    alert.begin();
	alert.setEnabled(true);
	detector.motion = true;
	alert.update();
    TEST_ASSERT_TRUE(gsm.message != "");
	TEST_ASSERT_TRUE(gsm.phone == "+7");
}

void beginMotionDisabled()
{
	MotionDetectorFake detector;
	GsmModuleFake gsm;
	GsmAlert alert(&detector, &gsm, "+7");
    alert.begin();
	alert.setEnabled(false);
	detector.motion = true;
	alert.update();
    TEST_ASSERT_TRUE(gsm.message == "");
	TEST_ASSERT_TRUE(gsm.phone == "");
}

void runTests()
{
    RUN_TEST(beginTest);
	RUN_TEST(beginMotionEnabled);
	RUN_TEST(beginMotionDisabled);
}


void setup()
{
    delay(500);
    UNITY_BEGIN();
    runTests();
    UNITY_END();
}

void loop()
{
    delay(500);
}
