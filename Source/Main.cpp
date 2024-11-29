#include <chrono>
#include <random>
#include <stack>
#include <SFML/Graphics.hpp>

#include "Headers/Cell.hpp"
#include "Headers/Global.hpp"
#include "Headers/RandomManager.hpp"
#include "Headers/Grid.hpp"
#include "Headers/Game.hpp"

int main()
{
	std::chrono::microseconds lag(0);

	std::chrono::steady_clock::time_point previous_time;

	Game game;

	game.draw();

	previous_time = std::chrono::steady_clock::now();

	while (1 == game.is_open())
	{
		//Making our project framerate-independent.
		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;

		while (gbl::SCREEN::FRAME_DURATION <= lag)
		{
			lag -= gbl::SCREEN::FRAME_DURATION;

			game.handle_events();
			game.update();

			if (gbl::SCREEN::FRAME_DURATION > lag)
			{
				game.draw();
			}
		}
	}
}