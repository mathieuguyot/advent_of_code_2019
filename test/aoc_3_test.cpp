#include <catch2/catch.hpp>

#include "aoc_3.hpp"
#include "utils.hpp"

#include <iostream>

using namespace std;

TEST_CASE("AOC3 - PART 1", "[find_intersection_points]") 
{
    vector<line_segments> lines = parse_lines_file("../data/aoc_3.txt");
    auto st = get_start_time();

    points_set s = find_intersection_points(lines, {1,1});
    int res = find_shortest_manhattan_distance(s, {1, 1});
    log_end_aoc_part(st, to_string(res), 3, 1);
    
    REQUIRE(res == 245);
}

TEST_CASE("AOC3 - nominal test", "[find_intersection_points]") 
{
    vector<line_segments> lines = {
        {{RIGHT, 8}, {UP, 5}, {LEFT, 5}, {DOWN, 3}},
        {{UP, 7}, {RIGHT, 6}, {DOWN, 4}, {LEFT, 4}}
    };
    points_set s = find_intersection_points(lines, {1,8});
    REQUIRE(s.size() == 2);
    REQUIRE(s.find({4, 5}) != s.end());
    REQUIRE(s.find({7, 3}) != s.end());
    REQUIRE(find_shortest_manhattan_distance(s, {1, 8}) == 6);
}


TEST_CASE("AOC3 - find_shortest_manhattan_distance test", "[find_shortest_manhattan_distance]") 
{
    vector<line_segments> lines = {
        {{RIGHT, 75},{DOWN, 30},{RIGHT, 83},{UP, 83},{LEFT, 12},{DOWN, 49},{RIGHT, 71},{UP, 7},{LEFT, 72}},
        {{UP,62},{RIGHT,66},{UP,55},{RIGHT,34},{DOWN,71},{RIGHT,55},{DOWN,58},{RIGHT,83}}
    };
    points_set s = find_intersection_points(lines, {1,1});
    REQUIRE(find_shortest_manhattan_distance(s, {1,1}) == 159);

    lines = {
        {{RIGHT,98},{UP,47},{RIGHT,26},{DOWN,63},{RIGHT,33},{UP,87},{LEFT,62},{DOWN,20},{RIGHT,33},{UP,53},{RIGHT,51}},
        {{UP,98},{RIGHT,91},{DOWN,20},{RIGHT,16},{DOWN,67},{RIGHT,40},{UP,7},{RIGHT,15},{UP,6},{RIGHT,7}}
    };
    s = find_intersection_points(lines, {1,8});
    REQUIRE(find_shortest_manhattan_distance(s, {1,8}) == 135);
}


TEST_CASE("AOC3 - good path", "[parse_intcode_program]") 
{
    vector<line_segments> lines = parse_lines_file("../data/aoc_3.txt");
    REQUIRE(lines.size() == 2);
    REQUIRE(lines[0].size() == 301);
    REQUIRE(lines[1].size() == 301);
    REQUIRE(lines[0][0] == line_segment {RIGHT, 1002});
    REQUIRE(lines[0][300] == line_segment {LEFT, 156});
    REQUIRE(lines[1][0] == line_segment {LEFT, 1003});
    REQUIRE(lines[1][300] == line_segment {RIGHT, 376});
}

TEST_CASE("AOC3 - bad path", "[parse_intcode_program]") 
{
	REQUIRE(parse_lines_file("foo.txt").size() == 0);
}

