// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

//Integrantes:
//Alessandro Biz
//Islan Silva Figueredo
//Ivan Sanchez tuzita
//Lucas da Silva Oliveira
//Arthur Gatti

#include "Game.h"

int main(int argc, char** argv)
{
	Game game;

	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}
