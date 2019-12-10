#include <catch2/catch.hpp>

#include "aoc_2.hpp"
#include "intcode_computer.hpp"
#include "utils.hpp"

using namespace std;

TEST_CASE("AOC9 - PART 1", "[compute]") 
{
    auto st = get_start_time();

    Intcode_Program program = parse_intcode_program_file("../data/aoc_9.txt");
    Parameter_queue inputs;
    inputs.push(1);
    Computation_result res = compute(program, inputs, [](Code output){cout << "OUTPUT=" << output << endl;});

    log_end_aoc_part(st, to_string(res.output_queue.back()), 9, 1);
    REQUIRE(res.return_code == Return_code::ok);
    //REQUIRE(res.output_queue.back() == 15508323);
}

TEST_CASE("AOC9 - relative parameter tests", "[compute]")
{
    Intcode_Program program = parse_intcode_program_string("1102,34915192,34915192,7,4,7,99,0");
    Parameter_queue inputs;
    string str_code;
    Computation_result res = compute(program, inputs, [&](Code output){str_code = to_string(output);});
    REQUIRE(res.return_code == Return_code::ok);
    REQUIRE(str_code == "1219070632396864");

    program = parse_intcode_program_string("104,1125899906842624,99");
    res = compute(program, inputs, [&](Code output){str_code = to_string(output);});
    REQUIRE(res.return_code == Return_code::ok);
    REQUIRE(str_code == "1125899906842624");

    program = parse_intcode_program_string("109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99");
    res = compute(program, inputs, [&](Code output){cout << "QUINE: " << output; });
    REQUIRE(res.return_code == Return_code::ok);
}