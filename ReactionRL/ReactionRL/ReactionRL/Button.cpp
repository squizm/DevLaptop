#include "Button.h"
#include <string.h>

Button::Button(int x, int y, const char* text, void(*function)(), TCODColor backColor, TCODColor foreColor, TCODColor hoverColor)
{
	setEntityInfo(x, y, ' ', TCODColor::black, -1,-1);
	width = strlen(text) + 2;
	height = 1;
	this->text = text;
	onClick = function;
	this->backColor = backColor;
	this->foreColor = foreColor;
	this->hoverColor = hoverColor;
	isHover = false;
}

void Button::update(TCOD_event_t event, TCOD_mouse_t mouse, TCOD_key_t key, uint32 deltaTime)
{
	switch (event){
	case TCOD_EVENT_MOUSE_PRESS:
		if (mouse.cx >= x && mouse.cy >= y && mouse.cx <= x + width +1 && mouse.cy <= y + height +1)
			onClick();
		break;
	case TCOD_EVENT_MOUSE_MOVE:
		if (mouse.cx >= x && mouse.cy >= y && mouse.cx <= x + width +1 && mouse.cy <= y + height +1)
			isHover = true;
		else
			isHover = false;
		break;
	}
}

void Button::render(TCODConsole *console)
{
	for (int i = 0; i < width; i++)
	{
		console->setCharBackground(x + i, y, isHover ? hoverColor : backColor);
		console->setCharBackground(x + i, y + 1, isHover ? hoverColor : backColor);
		console->setCharBackground(x + i, y + 2, isHover ? hoverColor : backColor);
	}	
	console->setDefaultForeground(foreColor);
	console->printEx(x + 1, y + 1, TCOD_BKGND_NONE, TCOD_alignment_t::TCOD_LEFT, text);
}