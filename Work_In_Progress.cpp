#pragma once
#include <SFML/Graphics.hpp>
#include "slots.h"
#include "object.h"
#include "utils.h"
#include <iostream>


using namespace sf;



int main()
{
	enum class State { PLAYING, INVENTORY };
	State state = State::PLAYING;
	RenderWindow window(VideoMode::getDesktopMode(), "Game");
	Event event;
	Mouse mouse;
	Utils utils;
	Vector2f mousePos;
	Vector2f adjMousePos;
	Vector2f negAdjMousePos;
	
	std::vector<Object*> mapObj;
	for (int i = 0; i < 25; i++)
	{
		mapObj.push_back(new Object());
	}
	std::vector<Object*> invObj;
	

	int invCol = 0;
	int invRow = 0;
	
	const int columns = 5;
	const int rows = 4;
	unsigned int maxSlots = columns * rows;
	Slots inv[columns][rows];
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			inv[i][j].setPositions(i, j);
		}
	}
	Vector2f invPos = inv[0][0].getPosition();
	float slotSize = inv[0]->getSlotSize();
	float invWidth =  slotSize * columns + columns * 20;
	float invHeight = slotSize * rows + rows * 20;

	
	
	

	while (window.isOpen())
	{
		
		adjMousePos = (Vector2f)mouse.getPosition(window) + Vector2f(5, 5);
		mousePos = (Vector2f)mouse.getPosition(window);
		negAdjMousePos = (Vector2f)mouse.getPosition(window) - Vector2f(25, 25);

		while (window.pollEvent(event))
		{

			//Keyboard controls playing
			if (state == State::PLAYING)
			{
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Escape)
					{
						window.close();
					}
					else if (event.key.code == Keyboard::I)
					{
						state = State::INVENTORY;
					}
				}
				else if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Button::Left)
					{
						
						for (unsigned int i = 0; i < std::size(mapObj); i++)
						{
							if(mapObj[i]->mouseIntersect(mousePos) == true)
							{
								if (utils.fullInv(inv, columns, rows, maxSlots) == false)
								{
									Object* temp = mapObj[i];
									invObj.push_back(temp);
									mapObj.erase(mapObj.begin() + i);
									utils.placeInv(invObj[size(invObj) - 1], inv, columns, rows, invObj);
								}
								else
								{

								}
							}
						}
					}
				}
			}

			//Keyboard controls inventory
			if (state == State::INVENTORY)
			{
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Escape)
					{
						state = State::PLAYING;
					}
					else if (event.key.code == Keyboard::S && std::size(invObj) != NULL)
					{
						for (int i = 0; i < columns; i++)
						{
							for (int j = 0; j < rows; j++)
							{
								inv[i][j].clear();
							}
						}
						utils.sortInv(invObj, inv, columns);
					}
				}
			

				//Pick up and release of objects
				else if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Button::Left && std::size(invObj) != NULL)
					{
						for (unsigned int i = 0; i < std::size(invObj); i++)
						{
							if (invObj[i]->mouseIntersect(mousePos) == true)
							{
								inv[invCol][invRow].clear();
								invObj[i]->pickUp(negAdjMousePos);
								break;
							}
						}
					}
				}

				else if (event.type == Event::MouseButtonReleased)
				{
					if (event.key.code == Mouse::Button::Left && std::size(invObj) != NULL)
					{
						for (unsigned int i = 0; i < std::size(invObj); i++)
						{
							if (invObj[i]->mouseIntersect(mousePos) && invObj[i]->isPicked() == true)
							{	
								if (inv[invCol][invRow].isFilled())
								{
									for (unsigned int j = 0; j < std::size(invObj); j++)
									{
										if (invObj[j]->getPosition() == inv[invCol][invRow].getPosition() && j != i)
										{
											if (invObj[i]->compareType(*invObj[j]) == true)
											{
												invObj[i]->drop(invPos);
												
												inv[invCol][invRow].fill();
												break;
											}
											else
											{
												invObj[i]->drop(utils.placeInv(invObj[i], inv, columns,rows, invObj));
											}
										}
									}	
								}
								else 
								{
									invObj[i]->drop(invPos);
									inv[invCol][invRow].fill();
									break;
								}
								
							}
						}
					}
				}
			}
		}

		
		if (state == State::INVENTORY)
		{
			if (size(invObj) != NULL)
			{//Object follows mouse
				for (unsigned int i = 0; i < std::size(invObj); i++)
				{
					if (invObj[i]->isPicked() == true)
					{
						invObj[i]->setPosition(negAdjMousePos);
					}
				}
			}
		
			//Highlights slots when mouseover
			if (mousePos.x <= invWidth && mousePos.y <= invHeight)
			{
				for (int i = 0; i < columns; i++)
				{
					for (int j = 0; j < rows; j++)
					{
						if (inv[i][j].intSec(mousePos) == true)
						{
							inv[i][j].highLight();
							invPos = inv[i][j].getPosition();
							invCol = i;
							invRow = j;
						}
						else
						{
							inv[i][j].noHighLight();
						}

						if (inv[i][j].isFilled() == true)
						{
							inv[i][j].highLight();
						}
					}
				}
			}
		}

		
		/*DRAW*/
		if (state == State::PLAYING)
		{
			window.clear();
			
			for (unsigned int i = 0; i < std::size(mapObj); i++)
			{
				mapObj[i]->draw(window);
			}	
			window.display();
		}

		if (state == State::INVENTORY)
		{
			window.clear();

			for (int i = 0; i < columns; i++)
			{
				for (int j = 0; j < rows; j++)
				{
					inv[i][j].setColor();
					inv[i][j].draw(window);
				}
			}
			
			if (size(invObj) != NULL)
			{
				for (unsigned int i = 0; i < std::size(invObj); i++)
				{
					invObj[i]->draw(window);
				}
			}

			for (int i = 0; i < columns; i++)
			{
				for (int j = 0; j < rows; j++)
				{
					inv[i][j].setColor();
					inv[i][j].drawText(window);
				}
			}
			window.display();
		}
	
	}

	for (unsigned int i = 0; i < std::size(mapObj); i++)
	{
		delete mapObj[i];
	}
	

	if (std::size(invObj) != NULL)
	{
		for (unsigned int i = 0; i < std::size(invObj); i++)
		{
			delete invObj[i];
		}
	}
	
	mapObj.clear();
	invObj.clear();
	

	return 0;
};





