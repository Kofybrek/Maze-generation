#include <chrono>
#include <random>
#include <stack>
#include <SFML/Graphics.hpp>

#include "Headers/Cell.hpp"
#include "Headers/DrawText.hpp"
#include "Headers/Global.hpp"
#include "Headers/RandomManager.hpp"
#include "Headers/Grid.hpp"
#include "Headers/Game.hpp"

Game::Game() :
	window(sf::VideoMode(gbl::SCREEN::RESIZE * gbl::SCREEN::WIDTH, gbl::SCREEN::RESIZE * gbl::SCREEN::HEIGHT), "Maze Generator", sf::Style::Close),
	grid(random_manager)
{
	has_focus = window.hasFocus();

	window.setView(sf::View(sf::FloatRect(0, 0, gbl::SCREEN::WIDTH, gbl::SCREEN::HEIGHT)));

	font_texture.loadFromFile("Resources/Images/Font8.png");
}

bool Game::is_open() const
{
	return window.isOpen();
}

void Game::draw()
{
	if (1 == has_focus)
	{
		window.clear();

		grid.draw(0, gbl::MAP::BORDER_OFFSET, gbl::MAP::BORDER_OFFSET, window);
		grid.draw(1, 3 * gbl::MAP::BORDER_OFFSET + gbl::CELL::SIZE * gbl::MAP::COLUMNS, gbl::MAP::BORDER_OFFSET, window);
		grid.draw(2, gbl::MAP::BORDER_OFFSET, 16 + 3 * gbl::MAP::BORDER_OFFSET + gbl::CELL::SIZE * gbl::MAP::ROWS, window);
		grid.draw(3, 3 * gbl::MAP::BORDER_OFFSET + gbl::CELL::SIZE * gbl::MAP::COLUMNS, 16 + 3 * gbl::MAP::BORDER_OFFSET + gbl::CELL::SIZE * gbl::MAP::ROWS, window);

		draw_stats(maze_0_steps, gbl::MAP::BORDER_OFFSET, 2 * gbl::MAP::BORDER_OFFSET + gbl::CELL::SIZE * gbl::MAP::ROWS, maze_0_duration);
		draw_stats(maze_1_steps, 3 * gbl::MAP::BORDER_OFFSET + gbl::CELL::SIZE * gbl::MAP::COLUMNS, 2 * gbl::MAP::BORDER_OFFSET + gbl::CELL::SIZE * gbl::MAP::ROWS, maze_1_duration);
		draw_stats(maze_2_steps, gbl::MAP::BORDER_OFFSET, 16 + 4 * gbl::MAP::BORDER_OFFSET + 2 * gbl::CELL::SIZE * gbl::MAP::ROWS, maze_2_duration);
		draw_stats(maze_3_steps, 3 * gbl::MAP::BORDER_OFFSET + gbl::CELL::SIZE * gbl::MAP::COLUMNS, 16 + 4 * gbl::MAP::BORDER_OFFSET + 2 * gbl::CELL::SIZE * gbl::MAP::ROWS, maze_3_duration);

		window.display();
	}
}

void Game::draw_stats(const unsigned& i_steps, const unsigned short& i_x, const unsigned short& i_y, const std::chrono::microseconds& i_duration)
{
	std::stringstream string_stream;
	string_stream << std::fixed << std::setprecision(2) << i_duration.count() / 1000.f;

	draw_text(0, 0, i_x, i_y, "Total steps: " + std::to_string(i_steps) + " - Time: " + string_stream.str() + "ms", window, font_texture);
}

void Game::handle_events()
{
	while (1 == window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				window.close();
			}
		}
	}
}

void Game::update()
{
	has_focus = window.hasFocus();

	if (1 == has_focus)
	{
		for (unsigned char a = 0; a < gbl::MAP::STEPS_PER_FRAME; a++)
		{
			grid.update_maze_generator(0, maze_0_steps, maze_0_duration);
			grid.update_maze_generator(1, maze_1_steps, maze_1_duration);
			grid.update_maze_generator(2, maze_2_steps, maze_2_duration);
			grid.update_maze_generator(3, maze_3_steps, maze_3_duration);
		}
	}
}