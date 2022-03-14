#include "../include/Score.h"

bool Score::Initialize(float digitPositionX, float digitPositionY)
{
	if(decimal.Initialize(0 + digitPositionX, digitPositionY) && numeral.Initialize(50 + digitPositionX, digitPositionY))
		return true;

	return false;
}

vector<Led> Score::checkDrawnLeds(int decimalNumber, int numeralNumber)
{
	vector<Led> decimalLeds = decimal.checkDrawnLeds(decimalNumber);
	vector<Led> numeralLeds = numeral.checkDrawnLeds(numeralNumber);

	decimalLeds.insert(decimalLeds.end(), numeralLeds.begin(), numeralLeds.end());

	return decimalLeds;
}
