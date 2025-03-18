#include "pch.h"
#include "Game.h"
#include "Engine.h"

#include "Mesh.h"
#include "Shader.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void Game::Init( const WindowInfo& win_info )
{
	GEngine->Init( win_info );

	vector<Vertex> vec = {
		Vertex{ Vec3{   0.f,   0.5, 0.5f }, Vec4{ 1.f, 0.f, 0.f, 1.f } },
		Vertex{ Vec3{  0.5f, -0.5f, 0.5f }, Vec4{ 0.f, 1.f, 0.f, 1.f } },
		Vertex{ Vec3{ -0.5f, -0.5f, 0.5f }, Vec4{ 0.f, 0.f, 1.f, 1.f } }
	};

	mesh->Init( vec );

	shader->Init( L"..\\Resource\\Shader\\default.hlsli" );

	GEngine->GetCommandQueue()->WaitSync();
}

void Game::Update()
{
	GEngine->RenderBegin();

	shader->Update();
	mesh->Render();

	GEngine->RenderEnd();
}
