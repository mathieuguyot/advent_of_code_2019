#include "aoc_3.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

using namespace std;

int find_shortest_manhattan_distance(const points_set& points, const point& central_port)
{
    int closest_manhattan_distance = -1;

    for(const auto& p : points)
    {
        int cur_manhattan_distance = abs(central_port.x - p.x) + abs(central_port.y - p.y);
        if(closest_manhattan_distance == -1 || closest_manhattan_distance > cur_manhattan_distance)
        {
            closest_manhattan_distance = cur_manhattan_distance;
        }
    }

    return closest_manhattan_distance; 
}

points_set find_intersection_points(const std::vector<line_segments>& lines, const point& central_port)
{
    points_set overlaping_points = {};
    points_set visisted_points = {};
    point current_position = central_port;
    bool is_second_wire = false;

    for(const auto& line : lines)
    {
        for(const auto& seg : line)
        {
            
            for(unsigned int i = 0; i < seg.intensity; ++i)
            {
                switch(seg.dir)
                {
                    case UP:
                        current_position.y -= 1; 
                        break;
                    case DOWN:
                        current_position.y += 1;
                        break;
                    case LEFT:
                        current_position.x -= 1;
                        break;
                    case RIGHT:
                        current_position.x += 1;
                        break;
                }
                if(visisted_points.find(current_position) != visisted_points.end())
                {
                    if(is_second_wire)
                    {
                        overlaping_points.insert(current_position);overlaping_points.insert(current_position);
                    }
                }
                else
                {
                    if(!is_second_wire)
                    {
                        visisted_points.insert(current_position);
                    }
                }
            }
        }
        is_second_wire = true;
        current_position = central_port;
    }

    return overlaping_points;
}

direction str_to_direction(const std::string& str) 
{
    direction dir;
    if(str == "U")
    {
        dir = UP;
    }
    else if(str == "L")
    {
        dir = LEFT;
    }
    else if(str == "R")
    {
        dir = RIGHT;
    }
    else if(str == "D")
    {
        dir = DOWN;
    }
    else 
    {
        cerr << "Can't parse direction: " << str;
        throw;
    }
    return dir;
}

vector<line_segments> parse_lines_file(const string& file_path)
{
    vector<line_segments> lines;
    
    ifstream file_stream(file_path);
    if(!file_stream.fail())
    {
        string str_line;
        while(!file_stream.eof()) {
            getline(file_stream, str_line);
            if(!str_line.empty())
            {
                line_segments line;
                regex re("(\\w)(\\d+)");

                auto words_begin = sregex_iterator(str_line.begin(), str_line.end(), re);
                auto words_end = sregex_iterator();
                for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                    smatch m = *i;
                    line.push_back({str_to_direction(m[1]), stoi(m[2])});
                }
                lines.push_back(line);
            }
        }
    }
    
    return lines;
}