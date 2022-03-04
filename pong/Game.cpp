// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "stdio.h"

const int thickness = 15;//sera usado para setar a altura de alguns objetos
const float paddleH = 200.0f;//tamanho da raquete

Game::Game()
:mWindow(nullptr)//para criar uma janela
,mRenderer(nullptr)//para fins de renderização na tela
,mTicksCount(0)//para guardar o tempo decorrido no jogo
,mIsRunning(true)//verificar se o jogo ainda deve continuar sendo executado
,mPaddleDir(0)//direcao da bolinha
{
	
}

bool Game::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter 1)", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	mPaddlePos.x = 10.0f;//posição inicial da raquete eixo x
	mPaddlePos.y = 768.0f/2.0f;//posição inicial da raquee eixo y

	balls[0].position.x = 1024.0f / 2.0f;
	balls[0].position.y = 768.0f / 2.0f;
	balls[0].velocity.x = -200.0f;
	balls[0].velocity.y = 500.0f;

	balls[1].position.x = 1024.0f / 2.0f;
	balls[1].position.y = 768.0f / 2.0f;
	balls[1].velocity.x = 200.0f;
	balls[1].velocity.y = 400.0f;

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;//evento, inputs do jogador são armazenados aqui
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	
	// Get state of keyboard - podemos buscar por alguma tecla específica pressionada no teclado, nesse caso, Escape
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	
	// Update paddle direction based on W/S keys - atualize a direção da raquete com base na entrada do jogador
	// W -> move a raquete para cima, S -> move a raquete para baixo
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 3;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 3;
	}
}

void Game::UpdateGame()
{
	// Espere que 16ms tenham passado desde o último frame - limitando os frames
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Delta time é a diferença em ticks do último frame
	// (convertido pra segundos) - calcula o delta time para atualização do jogo
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// "Clamp" (lima/limita) valor máximo de delta time
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// atualize a contagem de ticks par ao próximo frame
	mTicksCount = SDL_GetTicks();
	
	// atualiza a posição da raquete
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		// verifique que a raquete não se move para fora da tela - usamos "thickness", que definimos como a altura dos elementos
		if (mPaddlePos.y < (paddleH/2.0f + thickness))
		{
			mPaddlePos.y = paddleH/2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH/2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH/2.0f - thickness;
		}
	}
	
	// atualiza a posição da bola com base na sua velocidade
	balls[0].position.x += balls[0].velocity.x * deltaTime;
	balls[0].position.y += balls[0].velocity.y * deltaTime;

	balls[1].position.x += balls[1].velocity.x * deltaTime;
	balls[1].position.y += balls[1].velocity.y * deltaTime;
	
	// atualiza a posição da bola se ela colidiu com a raquete
	float diff = mPaddlePos.y - balls[0].position.y;
	float diff1 = mPaddlePos.y - balls[1].position.y;
	//pegue o valor absoluto de diferença entre o eixo y da bolinha e da raquete
	//isso é necessário para os casos em que no próximo frame a bolinha ainda não esteja tão distante da raquete
	//verifica se a bola está na area da raquete e na mesma posição no eixo x
	diff = (diff > 0.0f) ? diff : -diff;
	diff1 = (diff1 > 0.0f) ? diff1 : -diff1;

	if (
		// A diferença no eixo y y-difference is small enough
		diff <= paddleH / 2.0f &&
		balls[0].position.x <= 25.0f && balls[0].position.x >= 20.0f &&
		// A bolinha está se movendo para a esquerda
		balls[0].velocity.x < 0.0f)

	{
		if (balls[0].velocity.x > 0) {
			balls[0].velocity.x += 20;
		}
		else {
			balls[0].velocity.x -= 20;
		}
		balls[0].velocity.x *= -1.0f;
		//printf("%f\n", balls[0].velocity.x);
	}

	if (
		// A diferença no eixo y y-difference is small enough
		diff1 <= paddleH / 2.0f &&
			balls[1].position.x <= 25.0f && balls[1].position.x >= 20.0f &&
			// A bolinha está se movendo para a esquerda
			balls[1].velocity.x < 0.0f)

	{
		if (balls[1].velocity.x > 0) {
			balls[1].velocity.x += 20;
		}
		else {
			balls[1].velocity.x -= 20;
		}
		balls[1].velocity.x *= -1.0f;
		//printf("%f\n", balls[1].velocity.x);
	}

	//Verifica se a bola saiu da tela (no lado esquerdo, onde é permitido)
	//Se sim, encerra o jogo
	// 
	else if (balls[0].position.x <= 0.0f || balls[1].position.x <= 0.0f)
	{
		mIsRunning = false;
	}

	// Atualize (negative) a velocidade da bola se ela colidir com a parede do lado direito
	// 
	else if (balls[0].position.x >= (1024.0f - thickness) && balls[0].velocity.x > 0.0f)
	{
		balls[0].velocity.x *= -1.0f;
	}

	else if (balls[1].position.x >= (1024.0f - thickness) && balls[1].velocity.x > 0.0f)
	{
		balls[1].velocity.x *= -1.0f;
	}
	
	// Atualize (negative) a posição da bola se ela colidir com a parede de cima
	// 
	if (balls[0].position.y <= thickness && balls[0].velocity.y < 0.0f)
	{
		balls[0].velocity.y *= -1;
	}	
	else if (balls[0].position.y >= (768 - thickness) &&
		balls[0].velocity.y > 0.0f)
	{
		balls[0].velocity.y *= -1;
	}

	if (balls[1].position.y <= thickness && balls[1].velocity.y < 0.0f)
	{
		balls[1].velocity.y *= -1;
	}

	else if (balls[1].position.y >= (768 - thickness) &&
		balls[1].velocity.y > 0.0f)
	{
		balls[1].velocity.y *= -1;
	}

	// Atualize (negative) a posição da bola se ela colidiu com a parede de baixo
	// Did the ball collide with the bottom wall?


	
}

//Desenhando a tela do jogo
void Game::GenerateOutput()
{
	// Setamos a cor de fundo par azul
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);
	
	// limpa o back buffer
	SDL_RenderClear(mRenderer);

	// Desenha as paredes - mudamos a cor de mRenderer para o desenho dos retangulos que formaram as paredes
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 255, 255);
	
	// Desenha a parede de cima - desenhando um retangulo no topo da tela, coordenada x e y = 0, 0 representa o topo esquerdo
	//primeiro definimos as coordenadas e tamanhos do triangulo
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);//finalmente, desenhamos um retangulo no topo
	
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

	//desenhamos as outras paredes apenas mudando as coordenadas de wall

	// parede de baixo
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);
	
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);

	// parede da direita
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = 1024;
	wall.h = thickness;
	SDL_RenderFillRect(mRenderer, &wall);
	
	//como as posições da raquete e da bola serão atualizadas a cada iteração do game loop, criamos "membros" na classe
	//Game.h para tal

	//mudar a cor da raquete
	SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);

	//desenhando a raquete - usando mPaddlePos que é uma struc de coordenada que foi definida em Game.h
	// 
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),//static_cast converte de float para inteiros, pois SDL_Rect trabalha com inteiros
		static_cast<int>(mPaddlePos.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);
	

	//desenhando a bola - usando balls[0].position que é uma struc de coordenadas definida como membro em Game.h
	
	//mudar a cor do renderizador para a bola
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
	// Draw ball
	SDL_Rect ball0{	
		static_cast<int>(balls[0].position.x - thickness/2),
		static_cast<int>(balls[0].position.y - thickness/2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball0);

	SDL_Rect ball1{
		static_cast<int>(balls[1].position.x - thickness / 2),
		static_cast<int>(balls[1].position.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball1);

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);	

	
	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

//Para encerrar o jogo
void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);//encerra o renderizador
	SDL_DestroyWindow(mWindow);//encerra a janela aberta
	SDL_Quit();//encerra o jogo
}
