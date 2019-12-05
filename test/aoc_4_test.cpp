#include <catch2/catch.hpp>

#include "aoc_4.hpp"
#include "utils.hpp"

#include <iostream>

using namespace std;

TEST_CASE("AOC4 - PART 1", "[find_corrects_passwords]") 
{
    auto st = get_start_time();

    auto res = find_correct_passwords();
    
    log_end_aoc_part(st, to_string(res.size()), 4, 1);

    REQUIRE(res.size() == 1610);
}
