#pragma once

#include "glm/vec2.hpp"

#include "mapbox/variant.hpp"

struct  circle
{
	float radius;
};

struct aabb
{
	glm::vec2 halfExtents;
};

using shape = mapbox::util::variant<circle, aabb>;

class PhysObject
{
public:
	glm::vec2 pos;
	glm::vec2 vel;

	glm::vec2 forces;

	float mass;
	float drag;

	shape collider;

	PhysObject();

	void tickPhys(float delta);
	void draw() const;

	//add continuous force with respect to mass
	void addForce(glm::vec2 force);
	//add an instantaneous force with respect to mass
	void addImpulse(glm::vec2 impulse);
	//accelerates the object w/o respect to mass
	void addAccel(glm::vec2 accel);
	//adds an instantaneous force w/o respect to mass
	void addVelocityChange(glm::vec2 delta);
};

bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB);
bool checkAABBAABB(glm::vec2 posA, aabb aabbA, glm::vec2 posB, aabb aabbB);
bool checkCircleAABB(glm::vec2 posA, circle circ, glm::vec2 posB, aabb ab);

bool checkCircleX(glm::vec2 posA, circle lhs, glm::vec2 posB, shape rhs);
bool checkAABBX(glm::vec2 posA, aabb lhs, glm::vec2 posB, shape rhs);

void resolvePhysBodies(PhysObject& lhs, PhysObject& rhs);

void resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA, glm::vec2 posB, glm::vec2 velB, float massB, float elasticity, glm::vec2 normal, glm::vec2* dst);
