#include "../include/Digit.h"


bool Digit::Initialize(float digitPositionX, float digitPositionY) {

	if (
		led1.Initialize(212.0f + digitPositionX, 50.0f + digitPositionY, 20.0f, 5.0f) &&
		led2.Initialize(237.0f + digitPositionX, 50.0f + digitPositionY, 20.0f, 5.0f) &&
		led3.Initialize(212.0f + digitPositionX, 75.0f + digitPositionY, 20.0f, 5.0f) &&
		led4.Initialize(237.0f + digitPositionX, 75.0f + digitPositionY, 20.0f, 5.0f) &&
		led5.Initialize(217.0f + digitPositionX, 45.0f + digitPositionY, 5.0f, 20.0f) &&
		led6.Initialize(217.0f + digitPositionX, 70.0f + digitPositionY, 5.0f, 20.0f) &&
		led7.Initialize(217.0f + digitPositionX, 95.0f + digitPositionY, 5.0f, 20.0f)
		)
		return true;

	return false;

}

vector<Led> Digit::checkDrawnLeds(int num)
{

	switch(num)
	{
		case 0:
			return renderNumber0();
		case 1:
			return renderNumber1();
		case 2:
			return renderNumber2();
		case 3:
			return renderNumber3();
		case 4:
			return renderNumber4();
		case 5:
			return renderNumber5();
		case 6:
			return renderNumber6();
		case 7:
			return renderNumber7();
		case 8:
			return renderNumber8();
		case 9:
			return renderNumber9();
		default:
			break;
	}

	
}

vector<Led> Digit::renderNumber0()
{
	return { led1, led2, led3, led4, led5, led7 };
}

vector<Led> Digit::renderNumber1()
{
	return { led2, led4 };
}

vector<Led> Digit::renderNumber2()
{
	return { led2, led3, led5, led6, led7 };
}

vector<Led> Digit::renderNumber3()
{
	return { led2, led4, led5, led6, led7 };
}

vector<Led> Digit::renderNumber4()
{
	return { led1, led2, led4, led6 };
}

vector<Led> Digit::renderNumber5()
{
	return { led1, led4, led5, led6, led7 };
}

vector<Led> Digit::renderNumber6()
{
	return { led1, led3, led4, led5, led6, led7 };
}

vector<Led> Digit::renderNumber7()
{
	return {  led2,  led4, led5 };
}

vector<Led> Digit::renderNumber8()
{
	return{ led1, led2, led3, led4, led5,led6, led7 };
}

vector<Led> Digit::renderNumber9()
{
	return { led1, led2, led4, led5, led6 };
}
