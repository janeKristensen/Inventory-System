#include "Inventory.h"

Inventory::Inventory() 
{
	
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			inv[i][j].setPositions(i, j);
		}
	}
	
}

void Inventory::clearInv()
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			inv[i][j].clear();
		}
	}
}



void Inventory::sortInv(std::vector<Object*>& obj)
{
	clearInv();

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



Vector2f Inventory::placeInv(Object* obj, std::vector<Object*>& objList)
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



bool Inventory::fullInv()
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
			if (flag >= maxSlots)
			{
				return true;
			}
		}
	}

	return false;

}


int Inventory::returnInvObj(Vector2f inv_pos, std::vector<Object*>& obj)
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
	}
	else return NULL;

}


int Inventory::getRows()
{
	return rows;
}

int Inventory::getColumns()
{
	return columns;
}

void Inventory::draw(RenderTarget& target)
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			inv[i][j].setColor();
			inv[i][j].draw(target);
		}
	}
}

void Inventory::drawText(RenderTarget& target)
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			inv[i][j].setColor();
			inv[i][j].drawText(target);
		}
	}
}

void Inventory::mouseoverHighlight(Vector2f position)
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			if (inv[i][j].intSec(position) == true)
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