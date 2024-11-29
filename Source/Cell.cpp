#include <chrono>
#include <SFML/Graphics.hpp>

#include "Headers/Cell.hpp"
#include "Headers/Global.hpp"

Cell::Cell(const unsigned short& i_x, const unsigned short& i_y) :
	checked(0),
	wall_bottom(1),
	wall_left(1),
	wall_right(1),
	wall_top(1),
	x(i_x),
	y(i_y),
	color(gbl::CELL::COLORS::DEFAULT)
{

}

bool Cell::get_checked() const
{
	return checked;
}

bool Cell::get_wall_bottom() const
{
	return wall_bottom;
}

bool Cell::get_wall_left() const
{
	return wall_left;
}

bool Cell::get_wall_right() const
{
	return wall_right;
}

bool Cell::get_wall_top() const
{
	return wall_top;
}

unsigned short Cell::get_x() const
{
	return x;
}

unsigned short Cell::get_y() const
{
	return y;
}

void Cell::set_checked(const bool& i_value)
{
	checked = i_value;
}

void Cell::set_color(const sf::Color& i_value)
{
	color = i_value;
}

void Cell::set_wall_bottom(const bool& i_value)
{
	wall_bottom = i_value;
}

void Cell::set_wall_left(const bool& i_value)
{
	wall_left = i_value;
}

void Cell::set_wall_right(const bool& i_value)
{
	wall_right = i_value;
}

void Cell::set_wall_top(const bool& i_value)
{
	wall_top = i_value;
}

sf::Color Cell::get_color() const
{
	return color;
}