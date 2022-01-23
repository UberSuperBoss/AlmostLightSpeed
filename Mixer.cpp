#include "Mixer.hpp"
#include <iostream>

Mix_Chunk* Mixer::soundeffects[2] = { nullptr };
Mix_Music* Mixer::songs[2] = { nullptr };

void Mixer::init()
{
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);

	/*
	Mixer::soundeffects[0] = Mix_LoadWAV("./assets/audio/soundeffects/dead.wav");
	Mixer::soundeffects[1] = Mix_LoadWAV("./assets/audio/soundeffects/start.wav");
	*/

	Mixer::songs[0] = Mix_LoadMUS("./assets/audio/songs/titlescreen.wav");
	Mixer::songs[1] = Mix_LoadMUS("./assets/audio/songs/main.wav");
}

void Mixer::clean()
{
	for (Mix_Chunk* sound : soundeffects) Mix_FreeChunk(sound);
	for (Mix_Music* song : songs) Mix_FreeMusic(song);
}

void Mixer::playSoundEffect(SoundEffect sound)
{
	Mix_PlayChannel(-1, soundeffects[static_cast<int>(sound)], 0);
}

void Mixer::playSong(Song song)
{
	Mix_PlayMusic(songs[static_cast<int>(song)], -1);
}

