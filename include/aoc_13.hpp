#ifndef DEF_AOC_13_HPP
#define DEF_AOC_13_HPP

#include "intcode_computer.hpp"

#include <map>

enum class Tile {
    empty = 0,
    wall = 1,
    block = 2,
    horizontal_paddle = 3,
    ball = 4
};

using Position = std::pair<Code, Code>;

int get_number_of_block_tiles_in_game(const Intcode_Program& program);
int beat_the_game(const Intcode_Program& program);

#endif