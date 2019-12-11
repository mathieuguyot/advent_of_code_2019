#include <catch2/catch.hpp>

#include "aoc_11.hpp"
#include "utils.hpp"
#include <sstream>

using namespace std;

TEST_CASE("AOC11 - PART 1", "[perform_robot_paint]")
{
    auto st = get_start_time();
    
    Intcode_Program program = parse_intcode_program_file("../data/aoc_11.txt");
    int res = find_how_many_panels_are_painted(program);

    REQUIRE(res == 2883);

    log_end_aoc_part(st, to_string(res), 11, 1);
}

TEST_CASE("AOC11 - PART 2", "[find_registration_identifier]")
{
    auto st = get_start_time();
    
    Intcode_Program program = parse_intcode_program_file("../data/aoc_11.txt");
    string text = find_registration_identifier(program);
    
    stringstream ss_text;
    ss_text << " #    #### ###   ##  ###  #     ##  ####   " << endl;
    ss_text << " #    #    #  # #  # #  # #    #  #    #   " << endl;
    ss_text << " #    ###  #  # #    #  # #    #      #    " << endl;
    ss_text << " #    #    ###  #    ###  #    # ##  #     " << endl;
    ss_text << " #    #    #    #  # #    #    #  # #      " << endl;
    ss_text << " #### #### #     ##  #    ####  ### ####   " << endl;

    REQUIRE(text == ss_text.str());
    
    log_end_aoc_part(st, "\n" + text, 11, 2);
}