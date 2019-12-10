#include <catch2/catch.hpp>

#include "aoc_7.hpp"
#include "utils.hpp"

using namespace std;

TEST_CASE("AOC7 - PART 1", "[find_highest_thruster_signal]") 
{
    auto st = get_start_time();

    Intcode_Program program = parse_intcode_program_file("../data/aoc_7.txt");
    int res = find_highest_thruster_signal(program);
    
    log_end_aoc_part(st, to_string(res), 7, 1);

    REQUIRE(res == 79723);
}

TEST_CASE("AOC7 - PART 2", "[find_highest_thruster_signal]") 
{
    auto st = get_start_time();

    Intcode_Program program = parse_intcode_program_file("../data/aoc_7.txt");
    int res = find_highest_thruster_signal_loopback_mode(program);
    
    log_end_aoc_part(st, to_string(res), 7, 2);

    REQUIRE(res == 70602018);
}

TEST_CASE("AOC7 - test find_highest_thruster_signal", "[find_highest_thruster_signal]") 
{   
    string str_program = "3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0";
    Intcode_Program program = parse_intcode_program_string(str_program);
    
    REQUIRE(find_highest_thruster_signal(program) == 43210);

    str_program = "3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0";
    program = parse_intcode_program_string(str_program);
    
    REQUIRE(find_highest_thruster_signal(program) == 54321);

    str_program = "3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0";
    program = parse_intcode_program_string(str_program);
    
    REQUIRE(find_highest_thruster_signal(program) == 65210);
}

TEST_CASE("AOC7 - test find_highest_thruster_signal_loopback_mode", "[find_highest_thruster_signal_loopback_mode]") 
{   
    string str_program = "3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5";
    Intcode_Program program = parse_intcode_program_string(str_program);
    
    REQUIRE(find_highest_thruster_signal_loopback_mode(program) == 139629729);

    str_program = "3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,-5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10";
    program = parse_intcode_program_string(str_program);
    
    REQUIRE(find_highest_thruster_signal_loopback_mode(program) == 18216);
}