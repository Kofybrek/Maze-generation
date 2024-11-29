#pragma once

class Grid
{
	unsigned maze_2_counter;
	unsigned maze_3_counter;

	std::stack<Cell*> maze_0_stack;

	//This should've been a set. I don't know why I used a vector and called it "stack".
	std::vector<Cell*> maze_1_stack;
	std::vector<Cell*> maze_2_stack;

	sf::Sprite cell_sprite;

	sf::Texture cell_texture;

	//Maybe I should've made 4 classes for each algorithm that all inherit from the Grid class.
	gbl::Vector2D<Cell> maze_0_map;
	gbl::Vector2D<Cell> maze_1_map;
	gbl::Vector2D<Cell> maze_2_map;
	gbl::Vector2D<Cell> maze_3_map;

	Cell* maze_3_current_cell;

	RandomManager* random_manager;
public:
	Grid(RandomManager& i_random_manager);

	bool contains(const int& i_cell_x, const int& i_cell_y) const;

	void set_cells_connection(const bool& i_value, Cell& i_cell_0, Cell& i_cell_1);
	void draw(const unsigned char& i_maze_index, const unsigned short& i_position_x, const unsigned short& i_position_y, sf::RenderWindow& i_window);
	void update_maze_generator(const unsigned char& i_maze_index, unsigned& i_maze_steps, std::chrono::microseconds& maze_duration);

	std::vector<Cell*> get_available_neighbors(const bool& i_get_checked, const unsigned char& i_maze_index, const Cell& i_cell);
};