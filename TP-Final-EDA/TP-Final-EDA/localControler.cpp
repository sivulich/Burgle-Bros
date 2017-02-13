#include "localControler.h"

localControler::localControler(Screen* source)
{
	this->source = source;
	ALLEGRO_DISPLAY* temp = source->getDisplay()->_Get();
	al_install_keyboard();
	al_install_mouse();
	events = al_create_event_queue();
	al_register_event_source(events,al_get_display_event_source(temp));
	al_register_event_source(events, al_get_keyboard_event_source());
	al_register_event_source(events, al_get_mouse_event_source());
}
localControler::~localControler()
{
	// Deshacer todo lo del constructor, teclado mouse etc
	al_destroy_event_queue(events);
}
string
localControler::input()
{
	if (!al_event_queue_is_empty(events))
	{
		al_get_next_event(events, &event);
		switch (event.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			{
				return "exit";
			}
			case ALLEGRO_EVENT_MOUSE_AXES:
			{
				source->overYou(event.mouse.y, event.mouse.x);
				return "";
			}
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			{
				return source->click(event.mouse.y, event.mouse.x);
			}
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			{
				source->unClick();
				return "";
			}
			case ALLEGRO_EVENT_KEY_DOWN:
			{
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					return "exit";
				// Si se aprieta otra tecla no se la tiene que pasar a la screen??
			}
		}
	}
	return "";
}