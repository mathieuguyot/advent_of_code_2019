#include "aoc_8.hpp"

#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

string parse_image_data_file(const string& file_path)
{
    std::string file_data;

    ifstream file_stream(file_path);
    if(!file_stream.fail())
    {
        if(!file_stream.eof())
        {
            getline(file_stream, file_data);
        }
    }    

    return file_data;
}

int check_image_not_corrupted(const std::string& image_data)
{
    size_t min_number_of_zeros = -1;
    string selected_row;
    for (size_t i = 0; i < image_data.size(); i += PIXELS_WIDE * PIXELS_TALL) 
    {
        string row = image_data.substr(i, PIXELS_WIDE * PIXELS_TALL);
        size_t cur_number_of_zeros = count(row.begin(), row.end(), '0');
        if(min_number_of_zeros == -1 || cur_number_of_zeros < min_number_of_zeros)
        {
            min_number_of_zeros = cur_number_of_zeros; 
            selected_row = row;
        }
    }
    size_t cur_number_of_ones = count(selected_row.begin(), selected_row.end(), '1');
    size_t cur_number_of_twos = count(selected_row.begin(), selected_row.end(), '2');
    return cur_number_of_ones * cur_number_of_twos;
}

string decode_image(const std::string& image_data)
{
    stringstream decoded_image_stream;
    for(int i = 0; i < PIXELS_TALL ; i++)
    {
        for(int j = 0; j < PIXELS_WIDE; j++)
        {
            int index = PIXELS_WIDE * i + j;
            char color = '2';
            while(index < image_data.size())
            {
                if(image_data[index] == '0')
                {
                    color = ' ';
                    break;
                }
                if(image_data[index] == '1')
                {
                    color = '#';
                    break;
                }
                index += PIXELS_WIDE * PIXELS_TALL;
            }
            decoded_image_stream << color;
        }
        decoded_image_stream << endl;
    }
    return decoded_image_stream.str();
}