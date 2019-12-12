#include <catch2/catch.hpp>

#include "aoc_10.hpp"
#include "utils.hpp"
#include <sstream>

using namespace std;

TEST_CASE("AOC10 - PART 1", "[find_max_monitoring_capacity]")
{
    auto st = get_start_time();
    
    Asteroid_positions positions = parse_asteroid_map_file("../data/aoc_10.txt");
    int res = find_max_monitoring_capacity(positions);

    REQUIRE(res == 299);

    log_end_aoc_part(st, to_string(res), 10, 1);
}


TEST_CASE("AOC10 - good str", "[parse_asteroid_map_string]") 
{
    stringstream ss_map;
    ss_map << ".#..#" << endl;
    ss_map << "....." << endl;
    ss_map << "#####" << endl;
    ss_map << "....#" << endl;
    ss_map << "...##" << endl;

    Asteroid_positions positions = parse_asteroid_map_string(ss_map.str());
	REQUIRE(positions.size() == 10);
    REQUIRE(find(positions.begin(), positions.end(), make_pair(0,0)) == positions.end());
    REQUIRE(find(positions.begin(), positions.end(), make_pair(4,4)) != positions.end());
    REQUIRE(find(positions.begin(), positions.end(), make_pair(4,0)) != positions.end());
    REQUIRE(find(positions.begin(), positions.end(), make_pair(1,0)) != positions.end());
}

TEST_CASE("AOC10 - test find_monitoring_capacity", "[find_monitoring_capacity]") 
{
    stringstream ss_map;
    ss_map << ".#..#" << endl;
    ss_map << "....." << endl;
    ss_map << "#####" << endl;
    ss_map << "....#" << endl;
    ss_map << "...##" << endl;

    Asteroid_positions positions = parse_asteroid_map_string(ss_map.str());
    REQUIRE(find_monitoring_capacity(positions, make_pair(1,0)) == 7);
    REQUIRE(find_monitoring_capacity(positions, make_pair(3,4)) == 8);
    REQUIRE(find_monitoring_capacity(positions, make_pair(4,2)) == 5);
}

TEST_CASE("AOC10 - test find_max_monitoring_capacity", "[find_max_monitoring_capacity]") 
{
    stringstream ss_map;
    ss_map << ".#..#" << endl;
    ss_map << "....." << endl;
    ss_map << "#####" << endl;
    ss_map << "....#" << endl;
    ss_map << "...##" << endl;

    Asteroid_positions positions = parse_asteroid_map_string(ss_map.str());
    REQUIRE(find_max_monitoring_capacity(positions) == 8);

    ss_map.str("");
    ss_map.clear();
    ss_map << "......#.#." << endl;
    ss_map << "#..#.#...." << endl;
    ss_map << "..#######." << endl;
    ss_map << ".#.#.###.." << endl;
    ss_map << ".#..#....." << endl;
    ss_map << "..#....#.#" << endl;
    ss_map << "#..#....#." << endl;
    ss_map << ".##.#..###" << endl;
    ss_map << "##...#..#." << endl;
    ss_map << ".#....####" << endl;
    positions = parse_asteroid_map_string(ss_map.str());
    REQUIRE(find_max_monitoring_capacity(positions) == 33);

    ss_map.str("");
    ss_map.clear();
    ss_map << "#.#...#.#." << endl;
    ss_map << ".###....#." << endl;
    ss_map << ".#....#..." << endl;
    ss_map << "##.#.#.#.#" << endl;
    ss_map << "....#.#.#." << endl;
    ss_map << ".##..###.#" << endl;
    ss_map << "..#...##.." << endl;
    ss_map << "..##....##" << endl;
    ss_map << "......#..." << endl;
    ss_map << ".####.###." << endl;

    positions = parse_asteroid_map_string(ss_map.str());
    REQUIRE(find_max_monitoring_capacity(positions) == 35);

    ss_map.str("");
    ss_map.clear();
    ss_map << ".#..#..###" << endl;
    ss_map << "####.###.#" << endl;
    ss_map << "....###.#." << endl;
    ss_map << "..###.##.#" << endl;
    ss_map << "##.##.#.#." << endl;
    ss_map << "....###..#" << endl;
    ss_map << "..#.#..#.#" << endl;
    ss_map << "#..#.#.###" << endl;
    ss_map << ".##...##.#" << endl;
    ss_map << ".....#.#.." << endl;

    positions = parse_asteroid_map_string(ss_map.str());
    REQUIRE(find_max_monitoring_capacity(positions) == 41);

    ss_map.str("");
    ss_map.clear();
    ss_map << ".#..##.###...#######" << endl;
    ss_map << "##.############..##." << endl;
    ss_map << ".#.######.########.#" << endl;
    ss_map << ".###.#######.####.#." << endl;
    ss_map << "#####.##.#.##.###.##" << endl;
    ss_map << "..#####..#.#########" << endl;
    ss_map << "####################" << endl;
    ss_map << "#.####....###.#.#.##" << endl;
    ss_map << "##.#################" << endl;
    ss_map << "#####.##.###..####.." << endl;
    ss_map << "..######..##.#######" << endl;
    ss_map << "####.##.####...##..#" << endl;
    ss_map << ".#####..#.######.###" << endl;
    ss_map << "##...#.##########..." << endl;
    ss_map << "#.##########.#######" << endl;
    ss_map << ".####.#.###.###.#.##" << endl;
    ss_map << "....##.##.###..#####" << endl;
    ss_map << ".#.#.###########.###" << endl;
    ss_map << "#.#.#.#####.####.###" << endl;
    ss_map << "###.##.####.##.#..##" << endl;

    positions = parse_asteroid_map_string(ss_map.str());
    REQUIRE(find_max_monitoring_capacity(positions) == 210);
}

TEST_CASE("AOC10 - good path", "[parse_asteroid_map_file]") 
{
    Asteroid_positions positions = parse_asteroid_map_file("../data/aoc_10.txt");
	REQUIRE(positions.size() == 348);
    REQUIRE(find(positions.begin(), positions.end(), make_pair(1,1)) != positions.end());
    REQUIRE(find(positions.begin(), positions.end(), make_pair(38,0)) != positions.end());
    REQUIRE(find(positions.begin(), positions.end(), make_pair(0,37)) != positions.end());
    REQUIRE(find(positions.begin(), positions.end(), make_pair(34,37)) != positions.end());
    REQUIRE(find(positions.begin(), positions.end(), make_pair(0,0)) == positions.end());
    REQUIRE(find(positions.begin(), positions.end(), make_pair(38,38)) == positions.end());
}

TEST_CASE("AOC10 - bad path", "[parse_asteroid_map_file]") 
{
	REQUIRE(parse_asteroid_map_file("foo.txt").size() == 0);
}

