// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL/SDL.h"
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"
#include <vector>

using namespace std;

// Vector2 struct just stores x/y coordinates
// (for now)
struct Vector2
{
	float x;
	float y;
};

// Game class
class Game
{
public:
	Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void updateSingleGame(float deltaTime);
	void updateMultiplayerGame(float deltaTime);
	void GenerateOutput();
	bool generateRandomBool();
	

	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;
	
	// Pong specific
	// Direction of paddle
	int mPaddleDir1;
	int mPaddleDir2;
	// Position of paddle
	Vector2 mPaddlePos1;
	Vector2 mPaddlePos2;

	int scoreCount;
	int scoreCount2;
	bool isMultiplayerActive;

	Ball ball;

	vector<Ball> balls;

	Paddle paddleFirstPlayer;
	Paddle paddleSecondPlayer;

	Score scoreFirstPlayer;
	Score scoreSecondPlayer;
};
