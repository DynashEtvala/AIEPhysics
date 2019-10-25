#include "raylib.h"

#include "Game.h"

int main()
{
	Game app;
	app.init();
	app.targetFixedStep = 1.0f / 30.0f;

	while (!app.shouldClose())
	{
		app.tick();

		while (app.shouldPhysics())
		{
			app.tickPhys();
		}

		app.draw();
	}

	app.exit();

	return 0;
}