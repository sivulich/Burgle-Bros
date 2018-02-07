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

	if (!al_reserve_samples(1)) {
		std::cout << "failed to reserve samples!\n" << std::endl;
	}

	backround = new alx::Sample("./backround.wav");
	
}

void SoundEffects::playBackroundMusic()
{
	backround->play(1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP);
	std::cout << "PLAYING MUSIC" << std::endl;
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