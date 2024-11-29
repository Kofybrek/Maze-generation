#pragma once

class Game
{
	//Whether or not the window has focus.
	bool has_focus;

	//Number of steps it takes for each algorithm to complete.
	unsigned maze_0_steps;
	unsigned maze_1_steps;
	unsigned maze_2_steps;
	unsigned maze_3_steps;

	std::chrono::microseconds maze_0_duration;
	std::chrono::microseconds maze_1_duration;
	std::chrono::microseconds maze_2_duration;
	std::chrono::microseconds maze_3_duration;

	sf::Event event;

	sf::RenderWindow window;

	sf::Texture font_texture;

	RandomManager random_manager;

	//I'm storing 4 mazes and 4 algorithms in one grid. Yeah, I'm stupid.
	Grid grid;
public:
	Game();

	bool is_open() const;

	void draw();
	void draw_stats(const unsigned& i_steps, const unsigned short& i_x, const unsigned short& i_y, const std::chrono::microseconds& i_duration);
	void handle_events();
	void update();
};