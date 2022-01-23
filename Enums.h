#pragma once

enum class EntityType
{
	StarShip,
	Asteroid
};

enum class SoundEffect
{	
	Dead,
	Start
};

enum class Song
{
	TitleScreen,
	Main
};

enum class TextureType
{
	Background,
	StarShip,
	Asteroid1,
	Asteroid2,
	Exhaust1,
	Exhaust2,
	Exhaust3,
	Exhaust4,
	ExhaustT1,
	ExhaustT2,
	ExhaustT3,
	ExhaustT4,
	Title,
	Dead
};

enum class GameStatus
{
	StartMenu,
	Playing,
	Dead,
	Pause
};

enum class ScreenSize
{
	Low,
	Medium,
	High
};