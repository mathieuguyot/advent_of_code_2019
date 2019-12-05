#include <catch2/catch.hpp>

#include "aoc_2.hpp"
#include "utils.hpp"

using namespace std;

TEST_CASE("AOC2 - PART 1", "[execute_program]") 
{
    intcode_program_t program = parse_intcode_program("../data/aoc_2.txt");
    program[1] = 12;    
    program[2] = 2;
    auto st = get_start_time();

    program_execution_result_t res = execute_program(program);

    log_end_aoc_part(st, to_string(res.second[0]), 2, 1);

    REQUIRE(res.first == EXECUTION_OK);
    REQUIRE(res.second[0] == 6568671);
}

TEST_CASE("AOC2 - PART 2", "[execute_program]") 
{
    intcode_program_t program = parse_intcode_program("../data/aoc_2.txt");

    auto st = get_start_time();
    int res = find_noun_and_verb(program);
    log_end_aoc_part(st, to_string(res), 2, 2);

    REQUIRE(res == 3951);
}

TEST_CASE("AOC2 - programs tests", "[execute_program]") 
{
    intcode_program_t program = {1,0,0,0,99};
    program_execution_result_t res = execute_program(program);
    intcode_program_t expected_program = {2,0,0,0,99};
    REQUIRE(res.first == EXECUTION_OK);
    REQUIRE(res.second == expected_program);

    program = {2,3,0,3,99};
    res = execute_program(program);
    expected_program = {2,3,0,6,99};
    REQUIRE(res.first == EXECUTION_OK);
    REQUIRE(res.second == expected_program);

    program = {2,4,4,5,99,0};
    res = execute_program(program);
    expected_program = {2,4,4,5,99,9801};
    REQUIRE(res.first == EXECUTION_OK);
    REQUIRE(res.second == expected_program);

    program = {1,1,1,4,99,5,6,0,99};
    res = execute_program(program);
    expected_program = {30,1,1,4,2,5,6,0,99};
    REQUIRE(res.first == EXECUTION_OK);
    REQUIRE(res.second == expected_program);
}

TEST_CASE("AOC2 - good path", "[parse_intcode_program]") 
{
    intcode_program_t program = parse_intcode_program("../data/aoc_2.txt");
    REQUIRE(program.size() == 153);
    REQUIRE(program[0] == 1);
    REQUIRE(program[1] == 0);
    REQUIRE(program[151] == 14);
    REQUIRE(program[152] == 0);
}

TEST_CASE("AOC2 - bad path", "[parse_intcode_program]") 
{
	REQUIRE(parse_intcode_program("foo.txt").size() == 0);
}