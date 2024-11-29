#pragma once

namespace gbl
{
	namespace CELL
	{
		constexpr unsigned char SIZE = 4;

		namespace COLORS
		{
			const sf::Color GENERATION_PATH(0, 146, 255);
			const sf::Color DEFAULT(36, 36, 85);
			const sf::Color MAZE_PATH(255, 255, 255);
		}
	}

	namespace MAP
	{
		//We're showing 4 mazes. This is the margin around them.
		constexpr unsigned char BORDER_OFFSET = 2;
		//How many times we run the algorithm per frame.
		constexpr unsigned char STEPS_PER_FRAME = 16;

		constexpr unsigned short COLUMNS = 79;
		constexpr unsigned short ROWS = 40;
	}

	namespace SCREEN
	{
		constexpr unsigned char RESIZE = 2;

		constexpr unsigned short HEIGHT = 360;
		constexpr unsigned short WIDTH = 640;

		//1 Second / 60 Frames = 16.667 ms per frame
		constexpr std::chrono::microseconds FRAME_DURATION(16667);
	}

	template <typename i_value_type>
	using Vector2D = std::vector<std::vector<i_value_type>>;
}