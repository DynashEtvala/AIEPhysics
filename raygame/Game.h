#pragma once

#include <vector>

#include "Physics.h"

class Game
{
private:
	float accmulatedFixedTime;

	std::vector<PhysObject> physObjects;

public:
	Game();
	~Game();

	void init();
	void tick();
	void tickPhys();
	void draw() const;
	void exit();

	bool shouldClose() const;
	bool shouldPhysics() const;

	float targetFixedStep;
};

