#pragma once
#include "Digit.h"
#include <vector>

using namespace std;

class Score
{
public:
	bool Initialize(float digitPositionX = 0.0f, float digitPositionY = 0.0f);

	Digit decimal;
	Digit numeral;

	vector<Led> checkDrawnLeds(int decimalNumber, int numeralNumber);
};
