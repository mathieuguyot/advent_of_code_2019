#include "intcode_computer.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Instruction int_to_instruction(int opcode)
{
    Instruction i {Opcode::unknown, Mode::position, Mode::position, Mode::position};

    if(opcode == 1 || opcode == 2 || opcode == 3 || opcode == 4 || opcode == 99)
    {
        i.code = static_cast<Opcode>(opcode);
    }
    else if(opcode >= 10)
    {
        string str_opcode = to_string(opcode);
        opcode = stoi(str_opcode.substr(str_opcode.length() - 2));
        if(opcode == 1 || opcode == 2 || opcode == 3 || opcode == 4 || opcode == 99)
        {
            i.code = static_cast<Opcode>(opcode);
            if(str_opcode.length() == 5)
            {
                if(str_opcode[0] == '1')
                    i.param3_mode = Mode::immediate;
                if(str_opcode[1] == '1')
                    i.param2_mode = Mode::immediate;
                if(str_opcode[2] == '1')
                    i.param1_mode = Mode::immediate;
            }
            else if(str_opcode.length() == 4)
            {
                if(str_opcode[0] == '1')
                    i.param2_mode = Mode::immediate;
                if(str_opcode[1] == '1')
                    i.param1_mode = Mode::immediate;
            }
            else if(str_opcode.length() == 3)
            {
                if(str_opcode[0] == '1')
                    i.param1_mode = Mode::immediate;
            }
        }
    }

    return i;
}

Return_code get_value(Intcode_Program& program, Mode mode, int index, int& value)
{
    Return_code code = Return_code::ok;
    if(program.find(index) == program.end())
    {
        code = Return_code::wrong_index;
    }
    else if(mode == Mode::position && program.find(program.at(index)) == program.end())
    {
        code = Return_code::wrong_index;
    }
    else if(mode == Mode::position)
    {
        value = program.at(program.at(index));
    }
    else 
    {
        value = program.at(index);
    }
    return code;
}

Return_code opcode_add(Intcode_Program& program, const Instruction& i, int index)
{
    Return_code code = Return_code::ok;
    int a_value = -1;
    int b_value = -1;
    int c_value = -1;
    if(
        index + 3 < program.size() &&
        get_value(program, i.param1_mode, index + 1, a_value) == Return_code::ok &&
        get_value(program, i.param2_mode, index + 2, b_value) == Return_code::ok &&
        get_value(program, i.param3_mode, index + 3, c_value) == Return_code::ok &&
        program.find(program.at(c_value)) != program.end()
    )
    {
        program[program.at(c_value)] = a_value + b_value;
    }
    else
    {
        code = Return_code::wrong_index;
    }
    return code;
}


Computation_result compute(const Intcode_Program& program, const std::vector<int>& input_parameters)
{
    Return_code c = Return_code::ok;
    Intcode_Program p(program);

    int param_index = 0;
    int cur_index = 0;
    Instruction i;
    do {
        if(cur_index >= program.size())
        {
            c = Return_code::wrong_index;
            break;
        }
        i = int_to_instruction(p[cur_index]);
        if(i.code == Opcode::unknown)
        {
            c = Return_code::wrong_opcode;
            break;
        }
        else if(i.code == Opcode::times || i.code == Opcode::add)
        {
            if(cur_index + 3 >= program.size())
            {
                c = Return_code::wrong_index;
                break;
            }
            int a = -1;
            int b = -1;/*
            if(i.param1_mode == Mode::position)
            {
                if(p.find(p[cur_index+1]) != p.end())
                {
                    a = p[p[cur_index+1]];
                }
                else
                {
                    c = Return_code::wrong_index;
                    break;
                }
            }
            else
            {
                a = p[cur_index+1];
            }

            if(i.param2_mode == Mode::position)
            {
                if(p.find(p[cur_index+2]) != p.end())
                {
                    b = p[p[cur_index+2]];
                }
                else
                {
                    c = Return_code::wrong_index;
                    break;
                }
            }
            else
            {
                b = p[cur_index+2];
            }*/
            get_value(p, i.param1_mode, cur_index + 1, a);
            get_value(p, i.param2_mode, cur_index + 2, b);
            int c = -1;
            get_value(p, i.param3_mode, cur_index + 3, c);
            cout << c << " " << p[cur_index+3] << endl;

            if(i.code == Opcode::add) 
            {
                p[p[cur_index+3]] = a + b;
            }
            else
            {
                p[p[cur_index+3]] = a * b;
            }
            cur_index += 4;
        }
        else if(i.code == Opcode::input)
        {
            p[p[cur_index + 1]] = input_parameters[param_index];
            param_index += 1;
            cur_index += 2;
        }
        else if(i.code == Opcode::output)
        {
            if(i.param1_mode == Mode::position)
            {
                cout << "#" << cur_index << "   " << p[p[cur_index + 1]] << endl;
            }
            else
            {
                cout << "#" << cur_index << "   " << p[cur_index + 1] << endl;
            }
            cur_index += 2;
        }
    } while(i.code != Opcode::end);

    return {c, p};
}

Intcode_Program parse_intcode_program_file(const std::string &file_path)
{
    Intcode_Program program;

    ifstream file_stream(file_path);
    if (!file_stream.fail())
    {
        string str_program;
        if (!file_stream.eof())
        {
            getline(file_stream, str_program);
            stringstream ss(str_program);
            string intcode;
            int index = 0;
            while (getline(ss, intcode, ','))
            {
                if (!intcode.empty())
                {
                    program[index] = atoi(intcode.c_str());
                    index += 1;
                }
            }
        }
    }

    return program;
}
