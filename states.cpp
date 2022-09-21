#pragma once 
#include <SFML/Graphics.hpp>

using namespace sf;

class GameState {

public:
	virtual ~GameState(){}
	virtual void handleInput(Event event){}
	
	//static InventoryState invState;
	//static PlayingState playState;
};

class InventoryState : public GameState
{
public: 
	virtual ~InventoryState() {}
	virtual void handleInput(Event event)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				//GameState::playState;
			}
			else if (event.key.code == Keyboard::S)
			{
				
				//sort inv.
			}
		}
	}
};

class PlayingState : public GameState
{
public:
	virtual ~PlayingState() {}
	virtual void handleInput(Event event)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				//window.close();
			}
			else if (event.key.code == Keyboard::I)
			{
				//GameState::invState;
			}
		}
	}
};