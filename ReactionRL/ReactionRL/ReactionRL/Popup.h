#pragma once
#include <libtcod.hpp>
#include "Button.h"

#define POPUP_YESNO			0
#define POPUP_NOTIFICATION	1

#define MIN_WIDTH  10
#define MAX_WIDTH  30
#define MIN_HEIGHT  8


class Popup
{
private:
	char* title;
	char* message;
	short type;	
	Button* button1;
	Button* button2;
public:
	bool isShown;
	TCODConsole* console;
	int locX, locY, width, height;
	Popup(short type, char* title, int locX, int locY, char* message);
	void update(TCOD_event_t e, TCOD_mouse_t m, TCOD_key_t k, uint32 delta);
	void render();
	~Popup();
};