#pragma once
#include <SFML/Graphics.hpp>
#include "object.h"
#include "slots.h"

using namespace sf;



class Utils
{
private:



public:
	void sortInv(std::vector<Object*>& obj, Slots(&inv)[5][4], int columns);
	Vector2f placeInv(Object* dot, Slots(&inv)[5][4], int columns, int rows, std::vector<Object*>& objList);
	bool fullInv(Slots(&inv)[5][4], int columns, int rows, int max);
	int returnInvObj(Vector2f inv_pos, std::vector<Object*>& obj);
};

