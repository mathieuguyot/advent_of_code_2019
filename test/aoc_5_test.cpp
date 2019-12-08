#include <catch2/catch.hpp>

#include "aoc_2.hpp"
#include "intcode_computer.hpp"
#include "utils.hpp"

using namespace std;

TEST_CASE("AOC5 - PART 1", "[compute]") 
{
    auto st = get_start_time();

    Intcode_Program program = parse_intcode_program_file("../data/aoc_5.txt");
    Computation_result res = compute(program, {1});

    log_end_aoc_part(st, "TEST", 2, 1);
    
/*
    for(Intcode_Program::const_iterator it = res.second.begin();
        it != res.second.end(); ++it)
    {
        std::cout << it->first << " " << it->second << " " << "\n";
    }*/
    REQUIRE(res.first == Return_code::ok);
    //REQUIRE(res.second[0] == 6568671);
}
