#include <catch2/catch.hpp>

#include "aoc_1.hpp"
#include "utils.hpp"

using namespace std;

TEST_CASE("AOC1 - PART 1", "[compute_required_fuel_part_1]") 
{
    REQUIRE(compute_required_fuel_part_1({12}) == 2);
    REQUIRE(compute_required_fuel_part_1({14}) == 2);
    REQUIRE(compute_required_fuel_part_1({1969}) == 654);
    REQUIRE(compute_required_fuel_part_1({100756}) == 33583);

    auto st = get_start_time();

    module_masses_t masses = parse_module_masses_file("../data/aoc_1.txt");
    int res = compute_required_fuel_part_1(masses);
    
    log_end_aoc_part(st, to_string(res), 1, 1);
    REQUIRE(res == 3412496);
}

TEST_CASE("AOC1 - PART 2", "[compute_required_fuel_part_2]") 
{
    auto st = get_start_time();

    module_masses_t masses = parse_module_masses_file("../data/aoc_1.txt");
    int res = compute_required_fuel_part_2(masses);
    log_end_aoc_part(st, to_string(res), 1, 2);
    
    REQUIRE(res == 5115845);
}

TEST_CASE("AOC1 - good path", "[parse_module_masses_file]") 
{
    module_masses_t masses = parse_module_masses_file("../data/aoc_1.txt");
	REQUIRE(masses.size() == 100);
    REQUIRE(masses[0] == 148623);
    REQUIRE(masses[1] == 147663);
    REQUIRE(masses[99] == 116287);
}

TEST_CASE("AOC1 - bad path", "[parse_module_masses_file]") 
{
	REQUIRE(parse_module_masses_file("foo.txt").size() == 0);
}