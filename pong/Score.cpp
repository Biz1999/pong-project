#include "Score.h"

bool Score::Initialize(float digitPositionX, float digitPositionY)
{
	if(decimal.Initialize(0, digitPositionY) && numeral.Initialize(50, digitPositionY))
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
