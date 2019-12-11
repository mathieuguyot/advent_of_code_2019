#include <catch2/catch.hpp>

#include "aoc_4.hpp"
#include "utils.hpp"

using namespace std;

TEST_CASE("AOC4 - PART 1", "[find_corrects_passwords]") 
{
    auto st = get_start_time();

    auto res = find_correct_passwords();
    
    REQUIRE(res.size() == 1610);

    log_end_aoc_part(st, to_string(res.size()), 4, 1);
}

TEST_CASE("AOC4 - PART 2", "[find_correct_passwords_part_two]") 
{
    auto st = get_start_time();

    auto res = find_correct_passwords_part_two();
    
    REQUIRE(res.size() == 1104);

    log_end_aoc_part(st, to_string(res.size()), 4, 2);
}