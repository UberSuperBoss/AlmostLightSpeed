#include "EntityManager.hpp"
#include "GameManager.hpp"
#include <chrono>
#include "Mixer.hpp"

using namespace std;
#pragma warning(disable : 4996)

int EntityManager::animationCounter = 1;
int EntityManager::animationFrame = 0;

double EntityManager::screenSizeMultiplier = 0;
int EntityManager::speed = 1000;
std::vector<Entity*> EntityManager::entityList;

EntityManager::EntityManager(double screenMultiplier)
{
	screenSizeMultiplier = screenMultiplier;
	createEntity(EntityType::StarShip);
}

void EntityManager::createEntity(EntityType entityType)
{
	entityList.push_back(new Entity(entityType));
}

void EntityManager::render()
{
	/*
	std::string speedText = std::string() + "Speed: " + std::to_string(((double)speed)/10000) + "c";
	Renderer::renderText(speedText, 20, 20);
	*/

	if (animationFrame >= 4)
	{
		animationFrame = 0;
		
		if (animationCounter >= 4)
		{
			animationCounter = 0;
		}
		animationCounter++;
	}
	animationFrame++;

	speed = (double) speed * 1.00101;

	int x = (10000 - speed) / 200 * screenSizeMultiplier;

	int random_variable = (rand() % x) + 1;

	if (random_variable == 1)
	{ 
		createEntity(EntityType::Asteroid);
	}

	for (Entity* entity : entityList)
	{
		entity->update();
		if (GameManager::gameStatus != GameStatus::Playing) break;
		entity->render();
	}
}

void EntityManager::collisionDetection(Entity* protagonist)
{

	bool touched = false;

	for (Entity* entity : entityList)
	{
		if (entity != protagonist)
		{	
			if (Collision::isTouching(protagonist->destR, entity->destR))
			{

				touched = true;

			}	
		}
	}

	if (touched)
	{
		Mix_HaltMusic();

		destroyAll();

		Mixer::playSong(Song::TitleScreen);

		GameManager::gameStatus = GameStatus::Dead;

		createEntity(EntityType::StarShip);
	}

}

void EntityManager::destroy(Entity* entity)
{

	auto it = find(entityList.begin(), entityList.end(), entity);
	int index = it - entityList.begin();

	entityList.erase(entityList.begin() + index);

	delete entity;

}

void EntityManager::destroyAll()
{

	std::cout << "Began Delete All" << std::endl;

	
	for (Entity* ent : entityList)
	{
		delete ent;
		std::cout << "delete" << std::endl;
	}

	std::cout << "Finished Delete loop" << std::endl;

	entityList.clear();

	std::cout << "Completed Destroy All" << std::endl;

}