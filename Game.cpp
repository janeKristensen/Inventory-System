#include "Game.h"

Game::Game()
{
	for (int i = 0; i < 25; i++)
	{
		mapObj.push_back(new Object());
	}
}

void Game::transferToInv(Vector2f mousePos)
{
	for (unsigned int i = 0; i < std::size(mapObj); i++)
	{
		if (mapObj[i]->mouseIntersect(mousePos) == true)
		{
			if (inventory.fullInv() == false)
			{
				Object* temp = mapObj[i];
				invObj.push_back(temp);
				mapObj.erase(mapObj.begin() + i);
				inventory.placeInv(invObj[size(invObj) - 1], invObj);
			}
			else
			{

			}
		}
	}
}

void Game::handleInput(GameState& state, Event event, Vector2f mousePos, RenderWindow& window)
{
	adjMousePos = (Vector2f)mousePos + Vector2f(5, 5);
	negAdjMousePos = (Vector2f)mousePos - Vector2f(25, 25);

	if (state.getState() == (int)GameState::state::PLAYING)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				window.close();
			}
			else if (event.key.code == Keyboard::I)
			{
				state.setState((int)GameState::state::INVENTORY);
			}
		}
		else if (event.type == Event::MouseButtonPressed)
		{
			if (event.key.code == Mouse::Button::Left)
			{
				this->transferToInv(mousePos);
			}
		}
	}

	//Keyboard controls inventory
	if (state.getState() == (int)GameState::state::INVENTORY)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				state.setState((int)GameState::state::PLAYING);
			}
			else if (event.key.code == Keyboard::S && std::size(invObj) != NULL)
			{
				inventory.sortInv(invObj);
			}
		}


		//Pick up and release of objects
		else if (event.type == Event::MouseButtonPressed)
		{
			if (event.key.code == Mouse::Button::Left && std::size(invObj) != NULL)
			{
				state.setItemState((int)GameState::itemstate::ITEM_PICKUP);
			}
		}

		else if (event.type == Event::MouseButtonReleased)
		{
			if (event.key.code == Mouse::Button::Left && std::size(invObj) != NULL)
			{
				state.setItemState((int)GameState::itemstate::ITEM_DROP);
			}
		}
	}

	
}

void Game::update(GameState& state, Vector2f mousePos)
{
	if (state.getState() == (int)GameState::state::INVENTORY)
	{
		if (size(invObj) != NULL)
		{
			for (unsigned int i = 0; i < std::size(invObj); i++)
			{
				//Object follows mouse
				if (invObj[i]->isPicked() == true)
				{
					invObj[i]->setPosition(negAdjMousePos);
				}
			}
		}

		//Highlights slots when mouseover
		if (mousePos.x <= invWidth && mousePos.y <= invHeight)
		{
			inventory.mouseoverHighlight(mousePos);
		}

		invCol = inventory.getCurrentColumn();
		invRow = inventory.getCurrentRow();
		invPos = inventory.getPosition(invCol, invRow);

		if (state.getItemState() == (int)GameState::itemstate::ITEM_PICKUP)
		{
			for (unsigned int i = 0; i < std::size(invObj); i++)
			{
				if (invObj[i]->mouseIntersect(mousePos) == true)
				{
					inventory.clearSlot(invCol, invRow);
					invObj[i]->pickUp(negAdjMousePos);
					state.setItemState((int)GameState::itemstate::DEFAULT);
					break;
				}
			}
		}
		
		if (state.getItemState() == (int)GameState::itemstate::ITEM_DROP)
		{			
			for (unsigned int i = 0; i < std::size(invObj); i++)
			{
				if (invObj[i]->isPicked() == true)
				{
					if (inventory.isFilled(invCol, invRow) == true)
					{
						for (unsigned int j = 0; j < std::size(invObj); j++)
						{
							if (invObj[j]->getPosition() == inventory.getPosition(invCol, invRow) && j != i)
							{
								if (invObj[i]->compareType(*invObj[j]) == true)
								{
									invObj[i]->drop(invPos);
									inventory.fill(invCol, invRow);
									state.setItemState((int)GameState::itemstate::DEFAULT);
									break;
								}
								else
								{
									invObj[i]->drop(inventory.placeInv(invObj[i], invObj));		
									state.setItemState((int)GameState::itemstate::DEFAULT);
								}
							}
						}
					}
					else
					{
						invObj[i]->drop(invPos);
						inventory.fill(invCol, invRow);
						state.setItemState((int)GameState::itemstate::DEFAULT);
						break;
					}	
				}
				state.setItemState((int)GameState::itemstate::DEFAULT);
			}
		}	
	}	
}

void Game::drawGame(GameState& state, RenderWindow& window)
{
	/*DRAW*/
	if (state.getState() == (int)GameState::state::PLAYING)
	{
		window.clear();

		for (unsigned int i = 0; i < std::size(mapObj); i++)
		{
			mapObj[i]->draw(window);
		}
		window.display();
	}

	if (state.getState() == (int)GameState::state::INVENTORY)
	{
		window.clear();
		inventory.draw(window);

		if (size(invObj) != NULL)
		{
			for (unsigned int i = 0; i < std::size(invObj); i++)
			{
				invObj[i]->draw(window);
			}
		}

		inventory.drawText(window);
		window.display();
	}
}

void Game::deleteObjects()
{
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
}
