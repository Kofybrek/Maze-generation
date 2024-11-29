#pragma once

class Cell
{
	bool checked;
	bool wall_bottom;
	bool wall_left;
	bool wall_right;
	bool wall_top;

	unsigned short x;
	unsigned short y;

	sf::Color color;
public:
	Cell(const unsigned short& i_x, const unsigned short& i_y);

	bool get_checked() const;
	bool get_wall_bottom() const;
	bool get_wall_left() const;
	bool get_wall_right() const;
	bool get_wall_top() const;

	unsigned short get_x() const;
	unsigned short get_y() const;

	void set_checked(const bool& i_value);
	void set_color(const sf::Color& i_value);
	void set_wall_bottom(const bool& i_value);
	void set_wall_left(const bool& i_value);
	void set_wall_right(const bool& i_value);
	void set_wall_top(const bool& i_value);

	sf::Color get_color() const;
};