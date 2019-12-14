#include <catch2/catch.hpp>

#include "aoc_13.hpp"
#include "utils.hpp"

using namespace std;

TEST_CASE("AOC13 - PART 1", "[get_number_of_tiles_in_game]")
{
    auto st = get_start_time();
    
    Intcode_Program program = parse_intcode_program_file("../data/aoc_13.txt");
    int res = get_number_of_block_tiles_in_game(program);

    REQUIRE(res == 344);

    log_end_aoc_part(st, to_string(res), 13, 1);
}

TEST_CASE("AOC13 - PART 2", "[beat_the_game]")
{
    auto st = get_start_time();
    
    Intcode_Program program = parse_intcode_program_file("../data/aoc_13.txt");
    int res = beat_the_game(program);

    REQUIRE(res == 17336);

    log_end_aoc_part(st, to_string(res), 13, 2);
}
