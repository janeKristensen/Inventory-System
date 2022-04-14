#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Slots 
{
private:

	RectangleShape rect;
	Text invText;
	Font invFont;
	
	float size = 50;
	bool hiLight = false;
	bool filled = false;
	int stackSize = 0;
	bool showStack = false;

public:
	
	Slots();
	void setPositions(int i, int j);
	void draw(RenderTarget& target);
	void drawText(RenderTarget& target);
	Vector2f getPosition();
	void highLight();
	void noHighLight();
	void setColor();
	bool intSec(Vector2f mousePos);
	float getSlotSize();
	bool isFilled();
	void fill();
	void clear();
	void addToStack();
	void removeFromStack();
	
};

