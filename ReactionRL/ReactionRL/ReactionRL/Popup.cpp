#include "Popup.h"

void btnOK()
{

}

void btnYES()
{

}

void btnNO()
{

}

Popup::Popup(short type, char* title, int locX, int locY,char* message) : 
	locX(locX), locY(locY), title(title), message(message), type(type)
{

	int numCharacters = strlen(message);
	if (numCharacters + 4 > MAX_WIDTH)
		width = MAX_WIDTH;
	else
		width = numCharacters + 4;

	height = 12;

	switch (type)
	{
	case POPUP_YESNO:
		button1 = new Button(1,height - 4, "YES", btnYES);
		button2 = new Button(width/2 + 1, height - 4, "NO", btnNO);
		break;
	case POPUP_NOTIFICATION:
		button1 = new Button(1, height - 4, "OK", btnOK);
		button2 = 0;
		break;
	}

	console = new TCODConsole(width,height);
	isShown = false;
}

Popup::~Popup()
{
	button1 = 0;
	button2 = 0;
	console->~TCODConsole();
}

void Popup::update(TCOD_event_t e, TCOD_mouse_t m, TCOD_key_t k, uint32 delta)
{
	if (isShown)
	{
		if (button1)
			button1->update(e, m, k, delta);
		if (button2)
			button2->update(e, m, k, delta);
	}
}

void Popup::render()
{
	if (isShown)
	{
		console->clear();
		console->printFrame(0, 0, width, height, true, TCOD_BKGND_DEFAULT, title);
		console->printRect(2, 2, width, height, message);

		switch (type)
		{
		case POPUP_YESNO:
			button1->render(console);
			button2->render(console);
			break;
		case POPUP_NOTIFICATION:
			button1->render(console);
			break;
		}
	}
}