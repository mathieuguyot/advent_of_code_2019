#ifndef DEF_AOC_11_HPP
#define DEF_AOC_11_HPP

#include "intcode_computer.hpp"

#include <map>
#include <string>

#define TURNED_LEFT 0

enum class Paint_color {
    black = 0,
    white = 1
};

enum class Orientation {
    top = 0,
    bottom = 1,
    left = 2,
    right = 3
};

using Position = std::pair<int, int>;
using Paint = std::map<Position, Paint_color>;

Paint perform_robot_paint(const Intcode_Program& program, Paint_color start_color);
int find_how_many_panels_are_painted(const Intcode_Program& program);
std::string find_registration_identifier(const Intcode_Program& program);

#endif