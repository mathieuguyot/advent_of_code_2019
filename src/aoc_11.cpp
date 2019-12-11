#include "aoc_11.hpp"

#include <iostream>
#include<bits/stdc++.h>
#include <sstream>

using namespace std;

Orientation compute_new_orientation(bool turned_left, Orientation current_orientation)
{
    Orientation new_orientation;
    
    if(turned_left)
    {
        if(current_orientation == Orientation::top)
        {
            new_orientation = Orientation::left;
        }
        else if(current_orientation == Orientation::left)
        {
            new_orientation = Orientation::bottom;
        }
        else if(current_orientation == Orientation::bottom)
        {
            new_orientation = Orientation::right;
        }
        else // Current orientation right 
        {
            new_orientation = Orientation::top;
        }
    }
    else
    {
        if(current_orientation == Orientation::top)
        {
            new_orientation = Orientation::right;
        }
        else if(current_orientation == Orientation::left)
        {
            new_orientation = Orientation::top;
        }
        else if(current_orientation == Orientation::bottom)
        {
            new_orientation = Orientation::left;
        }
        else // Current orientation right 
        {
            new_orientation = Orientation::bottom;
        }
    }

    return new_orientation;
}

Position compute_new_robot_position(Position current_position, Orientation current_orientation)
{
    Position new_position = current_position;
    if(current_orientation == Orientation::top)
    {
        new_position.second += 1;
    }
    else if(current_orientation == Orientation::left)
    {
        new_position.first -= 1;
    }
    else if(current_orientation == Orientation::bottom)
    {
        new_position.second -= 1;
    }
    else // Current orientation right 
    {
        new_position.first += 1;
    }
    return new_position;
}

Paint perform_robot_paint(const Intcode_Program& program, Paint_color start_color)
{
    Paint panels_painted;
    Position robot_position;
    Orientation robot_orientation = Orientation::top;
    Parameter_queue robot_inputs;
    robot_inputs.push(static_cast<int>(start_color));
    bool wait_for_color = true;

    Ouput_callback robot_callback = [&](Code output) {
        if(wait_for_color)
        {
            panels_painted[robot_position] = static_cast<Paint_color>(output);
            wait_for_color = false;
        }
        else if(!wait_for_color)
        {
            bool turned_left = output == TURNED_LEFT;
            robot_orientation = compute_new_orientation(turned_left, robot_orientation);
            robot_position = compute_new_robot_position(robot_position, robot_orientation);
            
            auto it = panels_painted.find(robot_position);
            if(it != panels_painted.end())
            {
                robot_inputs.push(static_cast<int>(panels_painted[robot_position]));
            }
            else
            {
                robot_inputs.push(static_cast<int>(Paint_color::black));
            }
            wait_for_color = true;
        }
    };
    
    Computation_result res = compute(program, robot_inputs, robot_callback);
    return panels_painted;
}

int find_how_many_panels_are_painted(const Intcode_Program& program)
{
    return perform_robot_paint(program, Paint_color::black).size();
}

std::string find_registration_identifier(const Intcode_Program& program)
{
    stringstream ss_text;
    Paint paint = perform_robot_paint(program, Paint_color::white);

    int min_x = INT_MAX;
    int min_y = INT_MAX;
    int max_x = INT_MIN;
    int max_y = INT_MIN;

    for(const auto& p : paint)
    {
        Position pos = p.first;
        if(pos.second < min_y) 
        {
            min_y = pos.second;
        }
        if(pos.second > max_y) 
        {
            max_y = pos.second;
        }
        if(pos.first < min_x) 
        {
            min_x = pos.first;
        }
        if(pos.first > max_x) 
        {
            max_x = pos.first;
        }
    }

    for(int y = max_y; y >= min_y; y--)
    {
        for(int x = min_x; x <= max_x; x++)
        {
            if(paint.find({x,y}) != paint.end() && paint[{x,y}] == Paint_color::white)
            {
                ss_text << "#";
            }
            else
            {
                ss_text << " ";
            }
        }
        ss_text << endl;
    }
    return ss_text.str();
}