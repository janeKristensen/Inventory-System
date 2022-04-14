#include "utils.h"


void Utils::sortInv(std::vector<Object*>& obj, Slots(&inv)[5][4], int columns)
{
	for (unsigned int i = 0; i < std::size(obj); i++)
	{
		int j = 0;
	label:
		for (int k = 0; k < columns; k++)
		{

			if (inv[k][j].isFilled() == false)
			{
				obj[i]->setPosition(inv[k][j].getPosition());
				inv[k][j].fill();
				break;
			}
			if (k == columns - 1)
			{
				j++;
				goto label;
			}
		}
	}
}



Vector2f Utils::placeInv(Object* obj, Slots(&inv)[5][4], int columns, int rows, std::vector<Object*>& objList)
{
	int j = 0;
label:
	for (int k = 0; k < columns; k++)
	{
		int type = returnInvObj(inv[k][j].getPosition(), objList);
		

		
		if (inv[k][j].isFilled() == false)
		{
			obj->setPosition(inv[k][j].getPosition());
			inv[k][j].fill();
			return inv[k][j].getPosition();
			break;
		}
		else if (obj->compareType(type) == true)
		{
			obj->setPosition(inv[k][j].getPosition());
			inv[k][j].fill();
			return inv[k][j].getPosition();
			break;
		}
		if (k == columns - 1)
		{
			j++;
			if (j == rows)
			{
				return obj->getPosition();
			}
			goto label;
		}
	}
}



bool Utils::fullInv(Slots(&inv)[5][4], int columns, int rows, int max)
{
	int flag = 0;
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (inv[i][j].isFilled() == true)
			{
				flag++;
			}
			if (flag >= max)
			{
				return true;
			}
		}
	}

	return false;
	
}


int Utils::returnInvObj(Vector2f inv_pos, std::vector<Object*> &obj)
{
	if (std::size(obj) > 0)
	{
		for (int i = 0; i < std::size(obj); i++)
		{
			if (obj[i]->getPosition() == inv_pos)
			{
				return obj[i]->getType();
				break;
			}
		}

		return NULL;
	}
	else return NULL;

}


