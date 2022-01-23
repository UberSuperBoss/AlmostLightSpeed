#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include "Enums.h"

class Mixer
{
public:
	static void init();
	static void clean();

	static void playSoundEffect(SoundEffect sound);
	static void playSong(Song song);

	static Mix_Chunk* soundeffects[2];
	static Mix_Music* songs[2];
};