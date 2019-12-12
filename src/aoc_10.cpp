#include "aoc_10.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

float distance_between_positions(const Position& a, const Position& b)
{
    return sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2));
}

int find_monitoring_capacity(const Asteroid_positions& positions, Position asteroid_position)
{
    Asteroid_positions matching_asteroids;
    Asteroid_positions sorted_positions(positions);
    auto it = find(sorted_positions.begin(), sorted_positions.end(), asteroid_position);
    if(it != sorted_positions.end())
    {
        sorted_positions.erase(it);

        // 1 - Sort asteroids by shortest distance from asteroid_position
        auto sort_lambda = [&](const Position& a, const Position& b) -> bool 
        {
            float a_distance = distance_between_positions(a, asteroid_position);
            float b_distance = distance_between_positions(b, asteroid_position);
            return a_distance < b_distance;
        };
        sort(sorted_positions.begin(), sorted_positions.end(), sort_lambda);
        
        // 2 - Find monitored asteroids
        for(const Position& checked_asteroid : sorted_positions)
        {
            bool is_asteroid_monitored = true;
            for(const Position& potential_obstacle : matching_asteroids)
            {
                float asteroid_obstacle_distance = distance_between_positions(asteroid_position, potential_obstacle);
                float checked_obstacle_distance = distance_between_positions(checked_asteroid, potential_obstacle);
                float checked_asteroid_distance = distance_between_positions(checked_asteroid, asteroid_position);

                if(checked_asteroid_distance - (asteroid_obstacle_distance + checked_obstacle_distance) >= -0.00001)
                {
                    is_asteroid_monitored = false;
                }
            }
            if(is_asteroid_monitored)
            {
                matching_asteroids.push_back(checked_asteroid);
            }
        }
    }

    return matching_asteroids.size();
}

int find_max_monitoring_capacity(const Asteroid_positions& positions)
{
    int max_monitoring_capacity = 0;
    for(const Position& current_position : positions)
    {
        int monitoring_capacity = find_monitoring_capacity(positions, current_position);
        if(monitoring_capacity > max_monitoring_capacity)
        {
            max_monitoring_capacity = monitoring_capacity;
        }
    }
    return max_monitoring_capacity;
}

Asteroid_positions parse_asteroid_map_file(const std::string& file_path)
{
    Asteroid_positions positions;

    ifstream stream(file_path);
    if(!stream.fail())
    {
        int y_pos = 0;
        int x_pos = 0;
        string line;
        while(!stream.eof()) {
            getline(stream, line);
            if(!line.empty())
            {
                for(const char& car : line)
                {
                    if(car == ASTEROID_CHAR)
                    {
                        positions.push_back({x_pos, y_pos});
                    }
                    x_pos += 1;
                }
                x_pos = 0;
                y_pos += 1;
            }
        }
    }   

    return positions;
}


Asteroid_positions parse_asteroid_map_string(const std::string& str_map)
{
    Asteroid_positions positions;

    if(!str_map.empty())
    {
        stringstream ss(str_map);
        int y_pos = 0;
        int x_pos = 0;
        string line;
        while(!ss.eof()) {
            getline(ss, line);
            if(!line.empty())
            {
                for(const char& car : line)
                {
                    if(car == ASTEROID_CHAR)
                    {
                        positions.push_back({x_pos, y_pos});
                    }
                    x_pos += 1;
                }
                x_pos = 0;
                y_pos += 1;
            }
        }
    }   

    return positions;
}