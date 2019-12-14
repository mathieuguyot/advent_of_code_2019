#include "aoc_13.hpp"

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int get_number_of_block_tiles_in_game(const Intcode_Program& program)
{
    int number_of_block = 0;
    int current_instruction = 0;

    Ouput_callback game_callback = [&](Code output) {
        if(current_instruction == 0)
        {
            current_instruction = 1;
        } 
        else if(current_instruction == 1)
        {
            current_instruction = 2;
        }
        else
        {
            Tile tile = static_cast<Tile>(output);
            if(tile == Tile::block)
            {
                number_of_block++; 
            }
            current_instruction = 0;
        } 
    };

    Parameter_queue input_queue;
    compute(program, input_queue, game_callback);

    return number_of_block;
}

int beat_the_game(const Intcode_Program& program)
{
    Intcode_Program p = program;
    p[0] = 2;
    
    int score;
    bool is_score = false;

    Position current_position;
    Position ball_position;
    Position paddle_position;

    int current_instruction = 0;

    Ouput_callback game_callback = [&](Code output) {
        if(current_instruction == 0)
        {
            if(output == -1)
            {
                is_score = true;
            }
            else
            {
                current_position.first = output;
            }
            current_instruction = 1;
        } 
        else if(current_instruction == 1)
        {
            if(!is_score)
            {
                current_position.second = output;
            }
            current_instruction = 2;
        }
        else 
        {
            if(is_score)
            {
                score = output;
                is_score = false;
            }
            else
            {
                Tile tile = static_cast<Tile>(output);
                if(tile == Tile::ball)
                {
                    ball_position = current_position;
                }
                else if(tile == Tile::horizontal_paddle)
                {
                    paddle_position = current_position;
                }
            }
            current_instruction = 0;
        }
    };
    
    Parameter_queue input_queue;

    Input_callback input_callback = [&](Parameter_queue& input_queue) {
        int paddle_offset_move = 0;
        if(ball_position.first > paddle_position.first)
        {
            paddle_offset_move = 1;
        }
        else if(ball_position.first < paddle_position.first)
        {
            paddle_offset_move = -1;
        }
        paddle_position.first += paddle_offset_move;
        input_queue.push(paddle_offset_move);
    };

    Computation_result res = compute(p, input_queue, game_callback, input_callback);

    return score;
}