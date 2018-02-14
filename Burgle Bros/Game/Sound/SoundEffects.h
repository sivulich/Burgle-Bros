#pragma once
#include <observer.h>
#include <alx.hpp>

class SoundEffects
{
public:
	SoundEffects();

	void playbackgroundMusic();
	void stopBackgroundMusic();
	void playFlipCard();
	void playWalk();
	void playAlarm();
	void playChangeTurn();
private:
	alx::Sample * background;
	
};