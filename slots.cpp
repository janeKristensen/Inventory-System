#include "slots.h"

Slots::Slots()
{
	rect.setSize(Vector2f(size, size));
	rect.setFillColor(Color::White);
	invFont.loadFromFile("D:/Visual Studio stuff/Projekts/Work_In_Progress/fonts/invText.ttf");
	invText.setFont(invFont);
	invText.setFillColor(Color::Black);
}


void Slots::setPositions(int i, int j)
{
	float xPos = i * size + 25 *i + 10;
	float yPos = j * size + 25 *j + 10;
	Vector2f position(xPos, yPos);
	rect.setPosition(position);
	invText.setPosition(Vector2f(position.x, position.y + 20));
}

void Slots::draw(RenderTarget& target)
{
	target.draw(rect);
}
void Slots::drawText(RenderTarget& target)
{
	invText.setString(std::to_string(stackSize));
	if(showStack)
		target.draw(invText);
}

Vector2f Slots::getPosition()
{
	return rect.getPosition();
}

void Slots::highLight()
{
	 hiLight = true;
}

void Slots::noHighLight()
{
	 hiLight = false;
}

void Slots::setColor()
{
	if (hiLight == false)
	{
		rect.setFillColor(Color::White);
	}
	else if (hiLight == true)
	{
		rect.setFillColor(Color::Cyan);
	}
}

bool Slots::intSec(Vector2f mousePos)
{
	if (rect.getGlobalBounds().contains(mousePos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Slots::getSlotSize()
{
	return size;
}

bool Slots::isFilled()
{
	return filled;
}

void Slots::fill()
{
	filled = true;
	addToStack();
}

void Slots::clear()
{
	filled = false;
	removeFromStack();
}

void Slots::addToStack()
{
	stackSize++;
	if (stackSize > 1)
	{
		showStack = true;
	}
}

void Slots::removeFromStack()
{
	stackSize--;
	if (stackSize < 2)
	{
		showStack = false;
	}
}


