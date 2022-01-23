#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "Entity.hpp"
#include "Enums.h"
#include "Collision.hpp"

class EntityManager
{
public:
	EntityManager(double screenMultiplier);
	static void createEntity(EntityType entityType);
	static void render();
	static void destroy(Entity* entity);
	static void destroyAll();

	static int animationFrame;
	static int animationCounter;

	static int speed;

	static double screenSizeMultiplier;

	static void collisionDetection(Entity* protagonist);

	static std::vector<Entity*> entityList;
};