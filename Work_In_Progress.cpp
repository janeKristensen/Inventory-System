#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "States.h"


using namespace sf;



int main()
{
	
	GameState state;
	RenderWindow window(VideoMode::getDesktopMode(), "Game");
	Game game;
	Event event;
	Mouse mouse;
	Vector2f mousePos;
	

	while (window.isOpen())
	{
		state.setState((int)GameState::state::PLAYING);
		mousePos = (Vector2f)mouse.getPosition(window);

		while (window.pollEvent(event))
		{
			game.handleInput(state, event, mousePos, window);
		}
		game.update(state, mousePos);
		game.drawGame(state, window);
	}
	
	game.deleteObjects();
	return 0;
};





