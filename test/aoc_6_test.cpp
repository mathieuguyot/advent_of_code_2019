#include <catch2/catch.hpp>

#include "aoc_6.hpp"
#include "utils.hpp"

using namespace std;

TEST_CASE("AOC6 - PART 1", "[visit]") 
{   
    auto st = get_start_time();

    Galaxy galaxy = parse_galaxy_file("../data/aoc_6.txt");
    int res = galaxy.visit();

    log_end_aoc_part(st, to_string(res), 6, 1);
    
    REQUIRE(res == 154386);
}

TEST_CASE("AOC6 - PART 2", "[get_distance]") 
{   
    auto st = get_start_time();

    Galaxy galaxy = parse_galaxy_file("../data/aoc_6.txt");
    int res = galaxy.get_distance("YOU", "SAN") - 2;

    log_end_aoc_part(st, to_string(res), 6, 2);
    
    REQUIRE(res == 346);
}

TEST_CASE("AOC6 - test galaxy visit", "[visit]") 
{
    Galaxy galaxy;
    galaxy.add_orbit("K", "L");
    galaxy.add_orbit("J", "K");
    galaxy.add_orbit("E", "J");
    galaxy.add_orbit("D", "I");
    galaxy.add_orbit("G", "H");
    galaxy.add_orbit("B", "G");
    galaxy.add_orbit("E", "F");
    galaxy.add_orbit("D", "E");
    galaxy.add_orbit("C", "D");
    galaxy.add_orbit("B", "C");
    galaxy.add_orbit("COM", "B");
    REQUIRE(galaxy.visit() == 42);
}

TEST_CASE("AOC6 - test get_distance", "[get_distance]") 
{
    Galaxy galaxy;
    galaxy.add_orbit("K", "L");
    galaxy.add_orbit("J", "K");
    galaxy.add_orbit("E", "J");
    galaxy.add_orbit("D", "I");
    galaxy.add_orbit("G", "H");
    galaxy.add_orbit("B", "G");
    galaxy.add_orbit("E", "F");
    galaxy.add_orbit("D", "E");
    galaxy.add_orbit("C", "D");
    galaxy.add_orbit("B", "C");
    galaxy.add_orbit("COM", "B");
    galaxy.add_orbit("K", "YOU");
    galaxy.add_orbit("I", "SAN");
    REQUIRE(galaxy.get_distance("YOU", "SAN") == 6);
    REQUIRE(galaxy.get_distance("SAN", "YOU") == 6);
}

