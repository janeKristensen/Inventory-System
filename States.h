#pragma once 
#include <SFML/Graphics.hpp>

using namespace sf;

class GameState {
private:
	
	int gameState;
	int itemState;

public:
	enum class state { PLAYING, INVENTORY };
	enum class itemstate {ITEM_PICKUP, ITEM_DROP, DEFAULT };

	void setState(int state)
	{
		gameState = state;
	}
	int getState()
	{
		return gameState;
	}

	void setItemState(int state)
	{
		itemState = state;
	}
	int getItemState()
	{
		return itemState;
	}
};

