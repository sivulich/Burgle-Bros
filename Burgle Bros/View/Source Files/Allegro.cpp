#include "../Header Files/Allegro.h"



Allegro::Allegro()
{
	if (al_init() == true)
	{
		if (al_init_primitives_addon() == true &&
			al_install_keyboard() == true &&
			al_init_font_addon() == true &&
			al_init_ttf_addon() == true &&
			al_init_image_addon() == true &&
			al_init_primitives_addon() == true)
		{
			initOk = true;
			DEBUG_MSG_V("Correctly initialized allegro");
		}
		else
			DEBUG_MSG("Couldnt init allegro addons");
	}
	else
		DEBUG_MSG("Couldnt init allegro");
}


Allegro::~Allegro()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_uninstall_system();
}
