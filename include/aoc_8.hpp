#ifndef DEF_AOC_8_HPP
#define DEF_AOC_8_HPP

#include <string>

#define PIXELS_WIDE 25
#define PIXELS_TALL 6

std::string parse_image_data_file(const std::string& file_path);

int check_image_not_corrupted(const std::string& image_data);
std::string decode_image(const std::string& image_data);

#endif