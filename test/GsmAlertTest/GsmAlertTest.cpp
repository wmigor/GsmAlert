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

void beginMotion()
{
	MotionDetectorFake detector;
	GsmModuleFake gsm;
	GsmAlert alert(&detector, &gsm, "+7");
    alert.begin();
	detector.motion = true;
	alert.update();
    TEST_ASSERT_TRUE(gsm.message != "");
	TEST_ASSERT_TRUE(gsm.phone == "+7");
}

void runTests()
{
    RUN_TEST(beginTest);
	RUN_TEST(beginMotion);
}


void setup()
{
    delay(2000);
    UNITY_BEGIN();
    runTests();
    UNITY_END();
}

void loop()
{
    delay(500);
}
