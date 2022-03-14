#pragma once
#include "../include/Paddle.h"

struct Position
{
	float x;
	float y;
};

struct Velocity
{
	float x;
	float y;
};

class Ball
{
public:
	Position position;
	Velocity velocity;
	bool collidesWithPaddle(float diff, Paddle paddle);
	void updateBallDirection();
	void reverseBallXDirection();
	void reverseBallYDirection();
	bool isBallOutOfLeftSide();
	bool isBallOutOfRightSide(int ballWidth = 15);
	bool collidesWithTopWall(int ballWidth = 15);
	bool collidesWithBottomWall(float windowWidth = 600.0f, int ballWidth = 15);

public:
};

