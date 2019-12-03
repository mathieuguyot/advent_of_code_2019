#include "aoc_2.hpp"

#include <fstream>
#include <sstream>

using namespace std;

int find_noun_and_verb(const intcode_program_t& program)
{
    for(int cur_noun = 0 ; cur_noun <= 99; cur_noun++)
    {
        for(int cur_verb = 0 ; cur_verb <= 99; cur_verb++)
        {
            intcode_program_t cur_program(program);
            cur_program[1] = cur_noun;
            cur_program[2] = cur_verb;
            program_execution_result_t res = execute_program(cur_program);
            if(res.second[0] == 19690720)
            {
                return 100 * cur_noun + cur_verb;
            }
        }
    }
    return -1;
}

inline bool is_index_in_vector(const intcode_program_t& program, int index)
{
    return index >=0 && index < program.size();
}

program_execution_result_t execute_program(const intcode_program_t& program)
{
    if(program.empty())
    {
        return {EMPTY_PROGRAM, {}};
    }

    intcode_program_t cur_program(program);
    int cur_opcode_index = 0;
    return_code error_message = EXECUTION_OK;
    bool program_ended = false;
    while(!program_ended)
    {
        if(is_index_in_vector(cur_program, cur_opcode_index))
        {
            int cur_opcode = cur_program[cur_opcode_index];
            if(cur_opcode == 1 || cur_opcode == 2)
            {
                if( is_index_in_vector(cur_program, cur_opcode_index + 1) &&
                    is_index_in_vector(cur_program, cur_opcode_index + 2) && 
                    is_index_in_vector(cur_program, cur_opcode_index + 3) &&
                    is_index_in_vector(cur_program, cur_program[cur_opcode_index + 1]) &&
                    is_index_in_vector(cur_program, cur_program[cur_opcode_index + 2]) &&
                    is_index_in_vector(cur_program, cur_program[cur_opcode_index + 3]))
                {
                    int a_index = cur_program[cur_opcode_index + 1];
                    int b_index = cur_program[cur_opcode_index + 2];
                    int c_index = cur_program[cur_opcode_index + 3];
                    int a = cur_program[a_index];
                    int b = cur_program[b_index];
                    if(cur_opcode == 1)
                    {
                        cur_program[c_index] = a + b;
                    }
                    else 
                    {
                        cur_program[c_index] = a * b;
                    }
                    cur_opcode_index += 4;
                }
                else
                {
                    error_message = WRONG_INDEX;
                    program_ended = true;
                }
            }
            else if(cur_opcode == 99)
            {
                program_ended = true;
            }
            else 
            {
                error_message = WRONG_OPCODE;
                program_ended = true;
            }
        }
        
    }
    return {error_message, cur_program};
}

intcode_program_t parse_intcode_program(const string& file_path)
{
    intcode_program_t program;

    ifstream file_stream(file_path);
    if(!file_stream.fail())
    {
        string str_program;
        if(!file_stream.eof())
        {
            getline(file_stream, str_program);
            stringstream ss(str_program);
            string intcode;
            while (getline(ss, intcode, ',')) 
            {
                if(!intcode.empty())
                {
                    program.push_back(atoi(intcode.c_str()));
                }
            }
        }
    }

    return program;
}