#include <catch2/catch.hpp>

#include "aoc_2.hpp"
#include "intcode_computer.hpp"
#include "utils.hpp"

using namespace std;

TEST_CASE("AOC2 - PART 1", "[compute]") 
{
    auto st = get_start_time();

    Intcode_Program program = parse_intcode_program_file("../data/aoc_2.txt");
    program[1] = 12;    
    program[2] = 2;
    Computation_result res = compute(program);

    REQUIRE(res.return_code == Return_code::ok);
    REQUIRE(res.program[0] == 6568671);

    log_end_aoc_part(st, to_string(res.program[0]), 2, 1);
}

TEST_CASE("AOC2 - PART 2", "[find_noun_and_verb]") 
{
    auto st = get_start_time();

    Intcode_Program program = parse_intcode_program_file("../data/aoc_2.txt");
    int res = find_noun_and_verb(program);

    REQUIRE(res == 3951);

    log_end_aoc_part(st, to_string(res), 2, 2);
}
