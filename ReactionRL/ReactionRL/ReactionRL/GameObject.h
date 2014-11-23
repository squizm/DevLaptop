#pragma once
class GameObject
{
public:
	int x, y;
	int ch;
	GameObject(int x, int y, int ch) :x(x), y(y), ch(ch){};
	~GameObject();
};

