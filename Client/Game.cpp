#include "pch.h"
#include "Game.h"
#include "Engine.h"

void Game::Init(const WindowInfo& win_info)
{
	GEngine->Init( win_info );
}

void Game::Update()
{
	GEngine->Render();
}
