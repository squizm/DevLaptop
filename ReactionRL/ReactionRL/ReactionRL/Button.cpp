#include "Button.h"
#include <string.h>

Button::Button(int x, int y, const char* text, void(*function)(), TCODColor backColor, TCODColor foreColor, TCODColor hoverColor)
{
	setEntityInfo(x, y, ' ', TCODColor::black, -1,-1);
	this->width = strlen(text) + 2;
	this->height = 1;
	this->text = text;
	this->onClick = function;
	this->backColor = backColor;
	this->foreColor = foreColor;
	this->hoverColor = hoverColor;
	this->isHover = false;
}

void Button::update(TCOD_event_t event, int mouseX, int mouseY, TCOD_key_t key, uint32 deltaTime)
{
	switch (event){
	case TCOD_EVENT_MOUSE_PRESS:
		if (mouseX >= x && mouseY >= y && mouseX <= x + width +1 && mouseY <= y + height +1)
			onClick();
		break;
	case TCOD_EVENT_MOUSE_MOVE:
		if (mouseX >= x && mouseY >= y && mouseX <= x + width +1 && mouseY <= y + height +1)
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