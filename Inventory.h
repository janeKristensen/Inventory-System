#pragma once
#include "slots.h"
#include <SFML/Graphics.hpp>
#include "object.h"

using namespace sf;

class Inventory : public Slots
{
private:
	
	int invCol = 0;
	int invRow = 0;

	const int columns = 5;
	const int rows = 4;
	unsigned int maxSlots = columns * rows;
	Slots inv[5][4];
	Vector2f invPos = inv[0][0].getPosition();
	float slotSize = inv[0]->getSlotSize();
	float invWidth = slotSize * columns + columns * 20;
	float invHeight = slotSize * rows + rows * 20;


public: 
	Inventory();
	void clearInv();
	void clearSlot(int column, int row);
	void sortInv(std::vector<Object*>& obj);
	Vector2f placeInv(Object* obj, std::vector<Object*>& objList);
	bool fullInv();
	int returnInvObj(Vector2f inv_pos, std::vector<Object*>& obj);
	int getRows();
	int getColumns();
	int getCurrentRow();
	int getCurrentColumn();
	Vector2f getPosition(int column, int row);
	void fill(int column, int row);
	bool isFilled(int column, int row);
	void draw(RenderTarget& target);
	void drawText(RenderTarget& target);
	void mouseoverHighlight(Vector2f position);
};