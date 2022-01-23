#include "Entity.hpp"	
#include "EntityManager.hpp"

Entity::Entity(EntityType type)
{

	entityType = type;

	int randnum = (rand() % 2) + 1;

	switch (entityType)
	{
	case EntityType::StarShip:
		textureType = TextureType::StarShip;
		break;
	case EntityType::Asteroid:
		
		if (randnum == 1)
		{
			textureType = TextureType::Asteroid1;
		}
		else
		{
			textureType = TextureType::Asteroid2;
		}

		break;
	default:
		textureType = TextureType::StarShip;
		break;
	}

	//Location of Entity

	if (entityType == EntityType::StarShip)
	{
		destR.x = 50.0 * EntityManager::screenSizeMultiplier; destR.y = 30;
	}
	else
	{
		destR.x = 960.0 * EntityManager::screenSizeMultiplier;

		int random_variable = (rand() % (int) (540.0 * EntityManager::screenSizeMultiplier)) + 1;

		destR.y = random_variable - 40;
	}

	Renderer::setSize(textureType, &destR);

}

Entity::~Entity()
{
	//std::cout << "destroyed" << std::endl;
}

 
void Entity::render()
{
	if (entityType == EntityType::Asteroid)
	{
		Renderer::render(textureType, &destR);
	} 
	else
	{
		Renderer::render(textureType, &destR);
	}

	if (entityType == EntityType::StarShip)
	{

		bool turbo = false;

		if (EntityManager::speed > 6000) turbo = true;

		SDL_Rect exhaustRect = destR;

		TextureType exhaustTexture;

		if (turbo)
		{
			exhaustRect.x += -53.0 * EntityManager::screenSizeMultiplier;
			exhaustRect.y += -16.0 * EntityManager::screenSizeMultiplier;
			switch (EntityManager::animationCounter)
			{
			case 1:
				exhaustTexture = TextureType::ExhaustT1;
				break;
			case 2:
				exhaustTexture = TextureType::ExhaustT2;
				break;
			case 3:
				exhaustTexture = TextureType::ExhaustT3;
				break;
			case 4:
				exhaustTexture = TextureType::ExhaustT4;
				break;
			}
		}
		else
		{
			exhaustRect.x += -28.0 * EntityManager::screenSizeMultiplier;
			switch (EntityManager::animationCounter)
			{
			case 1:
				exhaustTexture = TextureType::Exhaust1;
				break;
			case 2:
				exhaustTexture = TextureType::Exhaust2;
				break;
			case 3:
				exhaustTexture = TextureType::Exhaust3;
				break;
			case 4:
				exhaustTexture = TextureType::Exhaust4;
				break;
			}
		}
		Renderer::setSize(exhaustTexture, &exhaustRect);
		Renderer::render(exhaustTexture, &exhaustRect);
	}
}

void Entity::update()
{

	if (entityType == EntityType::StarShip)
	{
		int mouseY = 0;

		SDL_GetMouseState(NULL, &mouseY);

		if (mouseY > 511.0 * EntityManager::screenSizeMultiplier)
		{
			destR.y = 511.0 * EntityManager::screenSizeMultiplier;
		}
		else
		{
			destR.y = mouseY;
		}

		EntityManager::collisionDetection(this);
	}
	else
	{
		destR.x = destR.x - (((double) EntityManager::speed) / 100);

		if (destR.x < -100)
		{
			//destR.x = 1920;
			
			// Removed the deletion of entity due to the jumping forward bug
			//EntityManager::destroy(this);
		}
	}
}