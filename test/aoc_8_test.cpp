#include <catch2/catch.hpp>

#include "aoc_8.hpp"
#include "utils.hpp"
#include <sstream>

using namespace std;

TEST_CASE("AOC8 - PART 1", "[check_image_not_corrupted]") 
{
    auto st = get_start_time();

    std::string file_data = parse_image_data_file("../data/aoc_8.txt");
    int res = check_image_not_corrupted(file_data);
    
    REQUIRE(res == 1463);

    log_end_aoc_part(st, to_string(res), 8, 1);
}

TEST_CASE("AOC8 - PART 2", "[decode_image]") 
{
    auto st = get_start_time();

    std::string file_data = parse_image_data_file("../data/aoc_8.txt");
    string res = decode_image(file_data);
    
    stringstream ss_text;
    ss_text << " ##  #  #  ##  #  # #  # " << endl;
    ss_text << "#  # # #  #  # # #  #  # " << endl;
    ss_text << "#    ##   #    ##   #### " << endl;
    ss_text << "# ## # #  #    # #  #  # " << endl;
    ss_text << "#  # # #  #  # # #  #  # " << endl;
    ss_text << " ### #  #  ##  #  # #  # " << endl;
    
    REQUIRE(res == ss_text.str());
    
    log_end_aoc_part(st, "\n" + res, 8, 2);
}

TEST_CASE("AOC8 - good path", "[parse_image_data_file]") 
{
    std::string file_data = parse_image_data_file("../data/aoc_8.txt");
	REQUIRE(file_data.size() == 15000);
    REQUIRE(file_data[0] == '2');
    REQUIRE(file_data[1] == '2');
    REQUIRE(file_data[14999] == '0');
}

TEST_CASE("AOC8 - bad path", "[parse_image_data_file]") 
{
	REQUIRE(parse_image_data_file("foo.txt").size() == 0);
}