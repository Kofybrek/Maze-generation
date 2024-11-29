#include <chrono>
#include <random>
#include <stack>
#include <SFML/Graphics.hpp>

#include "Headers/Cell.hpp"
#include "Headers/Global.hpp"
#include "Headers/RandomManager.hpp"
#include "Headers/Grid.hpp"

Grid::Grid(RandomManager& i_random_manager) :
	maze_2_counter(1),
	maze_3_counter(1),
	cell_sprite(cell_texture),
	maze_0_map(gbl::MAP::COLUMNS),
	maze_1_map(gbl::MAP::COLUMNS),
	maze_2_map(gbl::MAP::COLUMNS),
	maze_3_map(gbl::MAP::COLUMNS),
	random_manager(&i_random_manager)
{
	//All 4 algorithms will start from the same random cell.
	unsigned short random_cell_x = random_manager->get_random(gbl::MAP::COLUMNS - 1, 0);
	unsigned short random_cell_y = random_manager->get_random(gbl::MAP::ROWS - 1, 0);

	cell_texture.loadFromFile("Resources/Images/Cell" + std::to_string(gbl::CELL::SIZE) + ".png");

	for (unsigned short a = 0; a < gbl::MAP::COLUMNS; a++)
	{
		for (unsigned short b = 0; b < gbl::MAP::ROWS; b++)
		{
			//Maybe there's a better way to fill the grid with cells.
			//Maybe...
			maze_0_map[a].push_back(Cell(a, b));
			maze_1_map[a].push_back(Cell(a, b));
			maze_2_map[a].push_back(Cell(a, b));
			maze_3_map[a].push_back(Cell(a, b));
		}
	}

	maze_0_stack.push(&maze_0_map[random_cell_x][random_cell_y]);
	maze_0_stack.top()->set_color(gbl::CELL::COLORS::GENERATION_PATH);

	maze_1_stack.push_back(&maze_1_map[random_cell_x][random_cell_y]);
	maze_1_stack.back()->set_color(gbl::CELL::COLORS::GENERATION_PATH);

	maze_3_current_cell = &maze_3_map[random_cell_x][random_cell_y];
	//Marking the start cell as part of the 4th maze.
	maze_3_current_cell->set_checked(1);
	maze_3_current_cell->set_color(gbl::CELL::COLORS::GENERATION_PATH);

	maze_2_stack.push_back(&maze_2_map[random_cell_x][random_cell_y]);
	maze_2_stack.back()->set_color(gbl::CELL::COLORS::GENERATION_PATH);

	do
	{
		random_cell_x = random_manager->get_random(gbl::MAP::COLUMNS - 1, 0);
		random_cell_y = random_manager->get_random(gbl::MAP::ROWS - 1, 0);
	}
	while (random_cell_x == maze_2_stack.back()->get_x() && random_cell_y == maze_2_stack.back()->get_y());

	//Marking a random cell as part of the 3rd maze.
	maze_2_map[random_cell_x][random_cell_y].set_checked(1);
	maze_2_map[random_cell_x][random_cell_y].set_color(gbl::CELL::COLORS::MAZE_PATH);
}

bool Grid::contains(const int& i_cell_x, const int& i_cell_y) const
{
	if (0 > i_cell_x || gbl::MAP::COLUMNS <= i_cell_x)
	{
		return 0;
	}

	if (0 > i_cell_y || gbl::MAP::ROWS <= i_cell_y)
	{
		return 0;
	}

	return 1;
}

void Grid::set_cells_connection(const bool& i_value, Cell& i_cell_0, Cell& i_cell_1)
{
	//Every programming teacher on Youtube explains this concept like it's something revolutionary.
	//"Make your code more advanced using this trick!"
	//"Only experts like me know this!"
	if (1 < abs(i_cell_0.get_x() - i_cell_1.get_x()) || 1 < abs(i_cell_0.get_y() - i_cell_1.get_y()))
	{
		return;
	}

	if (i_cell_0.get_x() == i_cell_1.get_x() && i_cell_0.get_y() == i_cell_1.get_y())
	{
		return;
	}

	if (i_cell_0.get_x() != i_cell_1.get_x() && i_cell_0.get_y() != i_cell_1.get_y())
	{
		return;
	}

	if (i_cell_0.get_x() < i_cell_1.get_x())
	{
		i_cell_0.set_wall_right(i_value);
		i_cell_1.set_wall_left(i_value);
	}
	else if (i_cell_0.get_x() > i_cell_1.get_x())
	{
		i_cell_0.set_wall_left(i_value);
		i_cell_1.set_wall_right(i_value);
	}
	else if (i_cell_0.get_y() < i_cell_1.get_y())
	{
		i_cell_0.set_wall_bottom(i_value);
		i_cell_1.set_wall_top(i_value);
	}
	else if (i_cell_0.get_y() > i_cell_1.get_y())
	{
		i_cell_0.set_wall_top(i_value);
		i_cell_1.set_wall_bottom(i_value);
	}
}

void Grid::draw(const unsigned char& i_maze_index, const unsigned short& i_position_x, const unsigned short& i_position_y, sf::RenderWindow& i_window)
{
	gbl::Vector2D<Cell>* current_maze = &maze_0_map;

	if (1 == i_maze_index)
	{
		current_maze = &maze_1_map;
	}
	else if (2 == i_maze_index)
	{
		current_maze = &maze_2_map;
	}
	else if (3 == i_maze_index)
	{
		current_maze = &maze_3_map;
	}

	for (unsigned short a = 0; a < gbl::MAP::COLUMNS; a++)
	{
		for (unsigned short b = 0; b < gbl::MAP::ROWS; b++)
		{
			//Converting our 4 booleans into a decimal number from 0 to 15.
			unsigned char cell_state = (*current_maze)[a][b].get_wall_bottom() + 2 * (*current_maze)[a][b].get_wall_left() + 4 * (*current_maze)[a][b].get_wall_right() + 8 * (*current_maze)[a][b].get_wall_top();

			cell_sprite.setColor((*current_maze)[a][b].get_color());
			cell_sprite.setPosition(i_position_x + gbl::CELL::SIZE * a, i_position_y + gbl::CELL::SIZE * b);
			cell_sprite.setTextureRect(sf::IntRect(gbl::CELL::SIZE * cell_state, 0, gbl::CELL::SIZE, gbl::CELL::SIZE));

			i_window.draw(cell_sprite);
		}
	}
}

void Grid::update_maze_generator(const unsigned char& i_maze_index, unsigned& i_maze_steps, std::chrono::microseconds& maze_duration)
{
	//Come to think of it, I should've put the maze generation code separately from the Grid class.
	//Oh, well.
	if (0 == i_maze_index) //The Backtracking Algorithm
	{
		if (0 == maze_0_stack.empty())
		{
			//I'm pretty sure the duration calculation code is wrong. So I recommend just ignoring this.
			std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

			std::vector<Cell*> neighbors;

			Cell* current_cell = maze_0_stack.top();

			neighbors = get_available_neighbors(0, i_maze_index, *current_cell);

			if (1 == neighbors.empty())
			{
				//We're backtracking here.
				current_cell->set_color(gbl::CELL::COLORS::MAZE_PATH);
				maze_0_stack.pop();
			}
			else
			{
				Cell* next_cell = neighbors[random_manager->get_random(neighbors.size() - 1, 0u)];

				current_cell->set_checked(1);
				next_cell->set_checked(1);
				next_cell->set_color(gbl::CELL::COLORS::GENERATION_PATH);

				set_cells_connection(0, *current_cell, *next_cell);

				maze_0_stack.push(next_cell);
			}

			i_maze_steps++;

			maze_duration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
		}
	}
	else if (1 == i_maze_index) //The Randomized Prim's Algorithm
	{
		if (0 == maze_1_stack.empty())
		{
			std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

			unsigned current_cell_index = random_manager->get_random(maze_1_stack.size() - 1, 0u);

			std::vector<Cell*> neighbors;

			Cell* current_cell;

			current_cell = maze_1_stack[current_cell_index];

			neighbors = get_available_neighbors(0, i_maze_index, *current_cell);

			if (1 == neighbors.empty())
			{
				//If we can't expand from our cell, we remove it from our set.
				current_cell->set_color(gbl::CELL::COLORS::MAZE_PATH);
				maze_1_stack.erase(current_cell_index + maze_1_stack.begin());
			}
			else
			{
				Cell* next_cell = neighbors[random_manager->get_random(neighbors.size() - 1, 0u)];

				current_cell->set_checked(1);
				next_cell->set_checked(1);
				next_cell->set_color(gbl::CELL::COLORS::GENERATION_PATH);

				set_cells_connection(0, *current_cell, *next_cell);

				maze_1_stack.push_back(next_cell);
			}

			i_maze_steps++;

			maze_duration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
		}
	}
	else if (2 == i_maze_index) //Wilson's Algorithm
	{
		if (0 == maze_2_stack.empty())
		{
			std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

			std::vector<Cell*> neighbors;

			Cell* current_cell = maze_2_stack.back();
			Cell* next_cell;

			neighbors = get_available_neighbors(1, i_maze_index, *current_cell);

			//Making sure we're not choosing the previous cell.
			do
			{
				next_cell = neighbors[random_manager->get_random(neighbors.size() - 1, 0u)];
			}
			while (1 < maze_2_stack.size() && next_cell == maze_2_stack[maze_2_stack.size() - 2]);

			//We reached the cell that's part of our maze.
			if (1 == next_cell->get_checked())
			{
				//Making our generation path part of the maze.
				for (unsigned a = 0; a < maze_2_stack.size(); a++)
				{
					maze_2_counter++;

					maze_2_stack[a]->set_checked(1);
					maze_2_stack[a]->set_color(gbl::CELL::COLORS::MAZE_PATH);
				}

				set_cells_connection(0, *current_cell, *next_cell);

				maze_2_stack.clear();

				//Starting a new generation path (if we can, of course).
				if (maze_2_counter < gbl::MAP::COLUMNS * gbl::MAP::ROWS)
				{
					unsigned short random_cell_x;
					unsigned short random_cell_y;

					do
					{
						random_cell_x = random_manager->get_random(gbl::MAP::COLUMNS - 1, 0);
						random_cell_y = random_manager->get_random(gbl::MAP::ROWS - 1, 0);
					}
					while (1 == maze_2_map[random_cell_x][random_cell_y].get_checked());

					maze_2_stack.push_back(&maze_2_map[random_cell_x][random_cell_y]);
					maze_2_stack.back()->set_color(gbl::CELL::COLORS::GENERATION_PATH);
				}
			}
			else
			{
				bool looped = 0;

				for (unsigned a = 0; a < maze_2_stack.size() - 1; a++)
				{
					if (maze_2_stack[a] == next_cell)
					{
						looped = 1;

						//We're disconnecting the cells that are part of the loop.
						for (unsigned b = 1 + a; b < maze_2_stack.size(); b++)
						{
							maze_2_stack[b]->set_color(gbl::CELL::COLORS::DEFAULT);

							set_cells_connection(1, *maze_2_stack[b - 1], *maze_2_stack[b]);
						}

						//Deleting the loop cells.
						maze_2_stack.erase(1 + a + maze_2_stack.begin(), maze_2_stack.end());

						break;
					}
				}

				if (0 == looped)
				{
					next_cell->set_color(gbl::CELL::COLORS::GENERATION_PATH);

					set_cells_connection(0, *current_cell, *next_cell);

					maze_2_stack.push_back(next_cell);
				}
			}

			i_maze_steps++;

			maze_duration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
		}
	}
	else if (3 == i_maze_index) //The Aldous-Broder Algorithm
	{
		if (maze_3_counter < gbl::MAP::COLUMNS * gbl::MAP::ROWS)
		{
			std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

			std::vector<Cell*> neighbors;

			Cell* next_cell;

			neighbors = get_available_neighbors(1, i_maze_index, *maze_3_current_cell);

			//Moving randomly.
			next_cell = neighbors[random_manager->get_random(neighbors.size() - 1, 0u)];

			maze_3_current_cell->set_color(gbl::CELL::COLORS::MAZE_PATH);

			//Connecting the cells that haven't been checked yet.
			if (0 == next_cell->get_checked())
			{
				maze_3_counter++;

				set_cells_connection(0, *maze_3_current_cell, *next_cell);

				next_cell->set_checked(1);
			}

			maze_3_current_cell = next_cell;

			if (maze_3_counter == gbl::MAP::COLUMNS * gbl::MAP::ROWS)
			{
				next_cell->set_color(gbl::CELL::COLORS::MAZE_PATH);
			}
			else
			{
				next_cell->set_color(gbl::CELL::COLORS::GENERATION_PATH);
			}

			i_maze_steps++;

			maze_duration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
		}
	}
}

std::vector<Cell*> Grid::get_available_neighbors(const bool& i_get_checked, const unsigned char& i_maze_index, const Cell& i_cell)
{
	std::vector<Cell*> available_neighbors;

	gbl::Vector2D<Cell>* current_maze = &maze_0_map;

	if (1 == i_maze_index)
	{
		current_maze = &maze_1_map;
	}
	else if (2 == i_maze_index)
	{
		current_maze = &maze_2_map;
	}
	else if (3 == i_maze_index)
	{
		current_maze = &maze_3_map;
	}

	for (unsigned char a = 0; a < 4; a++)
	{
		//Coming up with this formula took longer than I'd like to admit.
		int neighbor_x = i_cell.get_x() + (1 < a) - a % 2;
		int neighbor_y = i_cell.get_y() + (2 > a) - a % 2;

		if (0 == contains(neighbor_x, neighbor_y))
		{
			continue;
		}

		if (0 == i_get_checked && 1 == (*current_maze)[neighbor_x][neighbor_y].get_checked())
		{
			continue;
		}

		//Working with pointers will force you to write things like this.
		available_neighbors.push_back(&(*current_maze)[neighbor_x][neighbor_y]);
	}

	return available_neighbors;
}