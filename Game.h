#pragma once
#include <SFML/Graphics.hpp>
#include "slots.h"
#include "object.h"
#include "Inventory.h"
#include <iostream>
#include "States.h"


using namespace sf;


class Game
{
private:
	static Game game;
	Inventory inventory;
	std::vector<Object*> mapObj;
	std::vector<Object*> invObj;

	Vector2f adjMousePos;
	Vector2f negAdjMousePos;

	int invCol;
	int invRow;
	Vector2f invPos;
	float slotSize = inventory.getSlotSize();
	int columns = inventory.getColumns();
	int rows = inventory.getRows();
	float invWidth = slotSize * columns + columns * 20;
	float invHeight = slotSize * rows + rows * 20;

public:
	Game();
	void transferToInv(Vector2f mousePos);
	void handleInput(GameState& state, Event event, Vector2f mousePos, RenderWindow& window);
	void update(GameState& state, Vector2f mousePos);
	void drawGame(GameState& state, RenderWindow& window);
	void deleteObjects();
};

