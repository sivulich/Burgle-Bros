#include "SoundEffects.h"
#include <allegro5/allegro_acodec.h>

SoundEffects::SoundEffects()
{
	if (!al_init()) {
		std::cout << "failed to initialize allegro!\n" << std::endl;
	}

	if (!al_install_audio()) {
		std::cout << "failed to initialize audio!\n" << std::endl;
	}
	if (!al_init_acodec_addon()) {
		std::cout << "failed to initialize audio codecs!\n" << std::endl;
	}

	if (!al_reserve_samples(10)) {
		std::cout << "failed to reserve samples!\n" << std::endl;
	}

	
	
}

void SoundEffects::playbackgroundMusic()
{
	if (background)
		return;
	background = new alx::Sample("../Game/Sound/background.wav");

	if (!background) {
		printf("Audio clip sample not loaded!\n");
	}
	if (std::get<0>(background->play(0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP)) == true)
		std::cout << "PLAYING MUSIC" << std::endl;
	else
		std::cout << "Couldnt play music" << std::endl;
}
void SoundEffects::stopBackgroundMusic()
{
	if(background)
		delete background;
	background = nullptr;
}
void SoundEffects::playFlipCard()
{

}
void SoundEffects::playWalk()
{

}
void SoundEffects::playAlarm()
{

}
void SoundEffects::playChangeTurn()
{

}