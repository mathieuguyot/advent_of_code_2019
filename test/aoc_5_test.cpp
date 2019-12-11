#include <catch2/catch.hpp>

#include "aoc_2.hpp"
#include "intcode_computer.hpp"
#include "utils.hpp"

using namespace std;

TEST_CASE("AOC5 - PART 1", "[compute]") 
{
    auto st = get_start_time();

    Intcode_Program program = parse_intcode_program_file("../data/aoc_5.txt");
    Parameter_queue inputs;
    inputs.push(1);
    Computation_result res = compute(program, inputs);

    REQUIRE(res.return_code == Return_code::ok);
    REQUIRE(res.output_queue.back() == 15508323);

    log_end_aoc_part(st, to_string(res.output_queue.back()), 5, 1);
    
}

TEST_CASE("AOC5 - PART 2", "[compute]") 
{
    auto st = get_start_time();

    Intcode_Program program = parse_intcode_program_file("../data/aoc_5.txt");
    Parameter_queue inputs;
    inputs.push(5);
    Computation_result res = compute(program, inputs);

    REQUIRE(res.return_code == Return_code::ok);
    REQUIRE(res.output_queue.back() == 9006327);

    log_end_aoc_part(st, to_string(res.output_queue.back()), 5, 1);
}
