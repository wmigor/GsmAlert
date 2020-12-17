#include <Arduino.h>
#include <unity.h>
#include <Test/PinFake.h>
#include <MotionDetector.h>

void setUp()
{
}

void tearDown()
{
}

void beginTest()
{
	PinFake pin1;
	PinFake pin2;
	MotionDetector detector({&pin1, &pin2});
	detector.begin();
	TEST_ASSERT_TRUE(pin1.input);
	TEST_ASSERT_TRUE(pin2.input);
}

void hasMotion00()
{
	PinFake pin1;
	PinFake pin2;
	MotionDetector detector({&pin1, &pin2});
	detector.begin();
	pin1.digitalValue = false;
	pin2.digitalValue = false;
	TEST_ASSERT_FALSE(detector.hasMotion());
}

void hasMotion01()
{
	PinFake pin1;
	PinFake pin2;
	MotionDetector detector({&pin1, &pin2});
	detector.begin();
	pin1.digitalValue = false;
	pin2.digitalValue = true;
	TEST_ASSERT_FALSE(detector.hasMotion());
}

void hasMotion10()
{
	PinFake pin1;
	PinFake pin2;
	MotionDetector detector({&pin1, &pin2});
	detector.begin();
	pin1.digitalValue = true;
	pin2.digitalValue = false;
	TEST_ASSERT_FALSE(detector.hasMotion());
}

void hasMotion11()
{
	PinFake pin1;
	PinFake pin2;
	MotionDetector detector({&pin1, &pin2});
	detector.begin();
	pin1.digitalValue = true;
	pin2.digitalValue = true;
	TEST_ASSERT_TRUE(detector.hasMotion());
}

void runTests()
{
	RUN_TEST(beginTest);
	RUN_TEST(hasMotion00);
	RUN_TEST(hasMotion01);
	RUN_TEST(hasMotion10);
	RUN_TEST(hasMotion11);
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
