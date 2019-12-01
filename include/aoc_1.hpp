#ifndef DEF_AOC_1_HPP
#define DEF_AOC_1_HPP

#include <vector>
#include <string>

typedef std::vector<int> module_masses_t;

int compute_required_fuel_part_1(const module_masses_t& masses);
int compute_required_fuel_part_2(const module_masses_t& masses);
module_masses_t parse_module_masses_file(const std::string& file_path);

#endif