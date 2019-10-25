#include "Game.h"

#include "raylib.h"

#include <iostream>

Game::Game()
{
	targetFixedStep = 1.0f / 30.0f;
	accmulatedFixedTime = 0.0f;
}

Game::~Game()
{
}

void Game::init()
{
	int screenWidth = 800;
	int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Sand Game");

	SetTargetFPS(60);
}

void Game::tick()
{
	accmulatedFixedTime += GetFrameTime();

	bool mb0 = IsMouseButtonPressed(0);
	bool mb1 = IsMouseButtonPressed(1);

	if (mb0 || mb1) {
		physObjects.emplace_back();
		std::cout << "Added a physics object!" << std::endl;

		auto& babyPhys = physObjects[physObjects.size() - 1];
		auto mousPos = GetMousePosition();
		babyPhys.pos = { mousPos.x, mousPos.y };

		if (mb0) {
			babyPhys.collider = circle{ 15.0f };
		}
		else {
			babyPhys.collider = aabb{ { 15.0f, 15.0f } };
		}
	}
}

void Game::tickPhys()
{
	accmulatedFixedTime -= targetFixedStep;

	for (auto& i : physObjects) 
	{
		i.tickPhys(targetFixedStep);
	}

	for (auto &i : physObjects) {
		for (auto &j : physObjects) {
			if (&i == &j) { continue; }

			i.collider.match([i, j](circle c) { if (checkCircleX(i.pos, c, j.pos, j.collider)) { std::cout << "collision!" << std::endl; }},
							 [i, j](aabb a) { if (checkAABBX(i.pos, a, j.pos, j.collider)) { std::cout << "collllllllision!" << std::endl; }});
		}
	}
}

void Game::draw() const
{
	BeginDrawing();

	ClearBackground(BLACK);

	for (const auto& i : physObjects)
	{
		i.draw();
	}

	EndDrawing();
}

void Game::exit()
{
	CloseWindow();
}

bool Game::shouldClose() const
{
	return WindowShouldClose();
}

bool Game::shouldPhysics() const
{
	return accmulatedFixedTime >= targetFixedStep;
}
