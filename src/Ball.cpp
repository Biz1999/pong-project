#include "../include/Ball.h"

const float UPDATE_VELOCITY_ON_COLISION = 30.0f;

bool Ball::collidesWithPaddle(float diff, Paddle paddle)
{
	float paddleFinalWidth = paddle.getX() + paddle.getWidth();

	if (diff <= paddle.getHeight() / 2.0f && this->position.x <= paddleFinalWidth && this->position.x >= paddle.getX())
		return true;

    return false;
}

void Ball::updateBallDirection()
{
	if (this->velocity.x > 0)
		this->velocity.x += UPDATE_VELOCITY_ON_COLISION;
	else
		this->velocity.x -= UPDATE_VELOCITY_ON_COLISION;

	this->velocity.x *= -1.0f;
}

void Ball::reverseBallXDirection()
{
	this->velocity.x *= -1.0f;
}

void Ball::reverseBallYDirection()
{
	this->velocity.y *= -1.0f;
}

bool Ball::isBallOutOfLeftSide()
{
	if (this->position.x <= 0.0f)
		return true;

	return false;
}

bool Ball::isBallOutOfRightSide(int ballWidth)
{
	if (this->position.x >= (1024.0f - ballWidth) && this->velocity.x > 0.0f)
		return true;

	return false;
}

bool Ball::collidesWithTopWall(int ballWidth)
{
	if (this->position.y <= ballWidth && this->velocity.y < 0.0f)
		return true;

	return false;
}

bool Ball::collidesWithBottomWall(float windowWidth, int ballWidth)
{
	if (this->position.y >= (windowWidth - ballWidth) && this->velocity.y > 0.0f)
		return true;

	return false;
}
