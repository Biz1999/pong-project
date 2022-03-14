
#include <vector>

using namespace std;

class Led
{
public:
	float x;
	float y;
	float height;
	float width;
	bool Initialize(float x, float y, float height, float width) {
		this->x = x;
		this->y = y;
		this->height = height;
		this->width = width;

		return true;
	}
};

class Digit
{
public:

	bool Initialize(float digitPositionX, float digitPositionY);

	vector<Led> checkDrawnLeds(int num);

private:
	Led led1;
	Led led2;
	Led led3;
	Led led4;
	Led led5;
	Led led6;
	Led led7;	

	vector<Led> renderNumber0();
	vector<Led> renderNumber1();
	vector<Led> renderNumber2();
	vector<Led> renderNumber3();
	vector<Led> renderNumber4();
	vector<Led> renderNumber5();
	vector<Led> renderNumber6();
	vector<Led> renderNumber7();
	vector<Led> renderNumber8();
	vector<Led> renderNumber9();



};