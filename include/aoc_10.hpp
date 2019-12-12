#ifndef DEF_AOC_10_HPP
#define DEF_AOC_10_HPP

#include <string>
#include <vector>

#define ASTEROID_CHAR '#'

using Position = std::pair<int, int>;
using Asteroid_positions = std::vector<Position>;

int find_monitoring_capacity(const Asteroid_positions& positions, Position asteroid_position);
int find_max_monitoring_capacity(const Asteroid_positions& positions);
Asteroid_positions parse_asteroid_map_file(const std::string& file_path);
Asteroid_positions parse_asteroid_map_string(const std::string& str_map);

#endif