#pragma once
class Paddle
{
public:
	bool Initialize(float x, float y, float width, float height, int direction);
	void changePaddleDirection(int direction);
	bool isPaddleMoving(int newDirection);
	void updatePaddlePosition(int newDirection, float deltaTime, int wallWidth);
	float getX();
	float getY();
	float getWidth();
	float getHeight();


private:
	float x;
	float y;
	float width;
	float height;
	int direction;

};