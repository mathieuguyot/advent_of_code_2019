#include "intcode_computer.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

Mode char_to_mode(char c)
{
    Mode m = Mode::position;
    if(c == '1')
    {
        m = Mode::immediate;
    }
    else if(c == '2')
    {
        m = Mode::relative;
    }
    return m;
}

Instruction int_to_instruction(Code opcode)
{
    Instruction i {Opcode::unknown, Mode::position, Mode::position, Mode::position};

    if(opcode >= 1 && opcode <= 9 || opcode == 99)
    {
        i.code = static_cast<Opcode>(opcode);
    }
    else if(opcode >= 10)
    {
        string str_opcode = to_string(opcode);
        opcode = stoi(str_opcode.substr(str_opcode.length() - 2));
        if(opcode >= 1 && opcode <= 9 || opcode == 99)
        {
            i.code = static_cast<Opcode>(opcode);
            if(str_opcode.length() == 5)
            {
                i.param3_mode = char_to_mode(str_opcode[0]);
                i.param2_mode = char_to_mode(str_opcode[1]);
                i.param1_mode = char_to_mode(str_opcode[2]);
            }
            else if(str_opcode.length() == 4)
            {
                i.param2_mode = char_to_mode(str_opcode[0]);
                i.param1_mode = char_to_mode(str_opcode[1]);
            }
            else if(str_opcode.length() == 3)
            {
                i.param1_mode = char_to_mode(str_opcode[0]);
            }
        }
    }

    return i;
}

Return_code get_value(Intcode_Program& program, Mode mode, int index, int relative_base, Code& value)
{
    Return_code code = Return_code::ok;
    if(program.find(index) == program.end())
    {
        code = Return_code::wrong_index;
    }
    else if(mode == Mode::position && program.find(program.at(index)) == program.end())
    {
        program[program.at(index)] = 0;
        value = program.at(program.at(index));
    }
    else if(mode == Mode::position)
    {
        value = program.at(program.at(index));
    }
    else if(mode == Mode::relative && program.find(program.at(index) + relative_base) == program.end())
    {
        program[program.at(index) + relative_base] = 0;
        value = program.at(program.at(index) + relative_base);
    }
    else if(mode == Mode::relative)
    {
        value = program.at(program.at(index) + relative_base);
    }
    else 
    {
        value = program.at(index);
    }
    return code;
}

Return_code opcode_operator(Intcode_Program& program, const Instruction& i, int index, int relative_base)
{
    Return_code code = Return_code::ok;
    Code a_value = -1;
    Code b_value = -1;
    if(
        index + 3 < program.size() &&
        get_value(program, i.param1_mode, index + 1, relative_base, a_value) == Return_code::ok &&
        get_value(program, i.param2_mode, index + 2, relative_base, b_value) == Return_code::ok 
    )
    {
        int write_index = i.param3_mode == Mode::position ? program[index + 3] : program[index + 3] + relative_base;
        if(i.code == Opcode::add)
        {
            program[write_index] = a_value + b_value;
        }
        else if(i.code == Opcode::times)
        {
            program[write_index] = a_value * b_value;
        }
        else if(i.code == Opcode::equals)
        {
            program[write_index] = a_value == b_value ? 1 : 0;
        }
        else if(i.code == Opcode::less_than)
        {
            program[write_index] = a_value < b_value ? 1 : 0;
        }
    }
    else
    {
        code = Return_code::wrong_index;
    }
    return code;
}

Return_code opcode_jump_if(Intcode_Program& program, const Instruction& i, int& index, int relative_base, bool jump_if_true)
{
    Return_code code = Return_code::ok;
    Code a_value = -1;
    Code b_value = -1;
    if(
        index + 2 < program.size() &&
        get_value(program, i.param1_mode, index + 1, relative_base, a_value) == Return_code::ok && 
        get_value(program, i.param2_mode, index + 2, relative_base, b_value) == Return_code::ok
    )
    {
        if(jump_if_true && a_value != 0)
        {
            index = b_value;
        }
        else if(!jump_if_true && a_value == 0)
        {
            index = b_value;
        }
        else
        {
            index += 3;
        }
    }
    else
    {
        code = Return_code::wrong_index;
    }

    return code;
}

Return_code opcode_input(Intcode_Program& program, const Instruction& i, int index, int relative_base, Parameter_queue& inputs)
{
    Return_code code = Return_code::ok;
    if(inputs.size() == 0)
    {
        code = Return_code::empty_input_queue;
    }
    else if(index + 1 >= program.size())
    {
        code = Return_code::wrong_index;
    }
    else
    {
        int write_index = i.param1_mode == Mode::position ? program[index + 1] : program[index + 1] + relative_base;
        program[write_index] = inputs.front();
        inputs.pop();
    }
    return code;
}

Return_code opcode_output(Intcode_Program& program, const Instruction& i, int index, int relative_base, Parameter_queue& outputs)
{
    Return_code code = Return_code::ok;
    if(index + 1 >= program.size())
    {
        code = Return_code::wrong_index;
    }
    else if(i.param1_mode == Mode::immediate)
    {
        outputs.push(program.at(index+1));
    }
    else if(i.param1_mode == Mode::position && program.find(program.at(index + 1)) != program.end())
    {
        outputs.push(program.at(program.at(index+1)));
    }
    else if(i.param1_mode == Mode::relative && program.find(program.at(index + 1) + relative_base) != program.end())
    {
        outputs.push(program.at(program.at(index + 1) + relative_base));
    }
    else
    {
        code = Return_code::wrong_index;
    }
    
    return code;
}

Return_code opcode_adjust_relative_base(Intcode_Program& program, const Instruction& i, int index, int& relative_base)
{
    Return_code code = Return_code::ok;

    Code a_value = -1;
    if(index + 1 < program.size() &&
        get_value(program, i.param1_mode, index + 1, relative_base, a_value) == Return_code::ok)
    {
        relative_base += a_value;
    }
    else
    {
        code = Return_code::wrong_index;
    }
    
    return code;
}

Computation_result compute(
    const Intcode_Program& program
)
{
    Parameter_queue input_queue;
    return compute(program, input_queue);
}

Computation_result compute(
    const Intcode_Program& program, 
    Parameter_queue& input_queue, 
    const Ouput_callback& output_callback, 
    bool wait_for_inputs
)
{
    Return_code c = Return_code::ok;
    Intcode_Program p(program);
    Parameter_queue outputs;
    
    int relative_base = 0;
    int param_index = 0;
    int cur_index = 0;
    Instruction i;
    do {
        // Check the validity of cur_index
        if(cur_index >= program.size())
        {
            c = Return_code::wrong_index;
            break;
        }
        // Parse new cur_index opcode
        i = int_to_instruction(p[cur_index]);
        if(i.code == Opcode::unknown)
        {
            c = Return_code::wrong_opcode;
            break;
        }

        // Execute an operation 
        if(i.code == Opcode::times || i.code == Opcode::add || i.code == Opcode::equals || i.code == Opcode::less_than)
        {
            c = opcode_operator(p, i, cur_index, relative_base);
            cur_index += 4;
        }
        else if(i.code == Opcode::input)
        { 
            while(wait_for_inputs && input_queue.empty()) {}
            c = opcode_input(p, i, cur_index, relative_base, input_queue);
            cur_index += 2;
        }
        else if(i.code == Opcode::output)
        {
            c = opcode_output(p, i, cur_index, relative_base, outputs);
            if(c == Return_code::ok)
            {
               output_callback(outputs.back());
            }
            cur_index += 2;
        }
        else if(i.code == Opcode::jump_if_true || i.code == Opcode::jump_if_false)
        {
            c = opcode_jump_if(p, i, cur_index, relative_base, i.code == Opcode::jump_if_true);
        }
        else if(i.code == Opcode::adjust_relative_base)
        {
            c = opcode_adjust_relative_base(p, i, cur_index, relative_base);
            cur_index += 2;
        }

        if(c != Return_code::ok)
        {
            break;
        }
        
    } while(i.code != Opcode::end);

    return {c, p, outputs};
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
                    program[index] = stoll(intcode.c_str());
                    index += 1;
                }
            }
        }
    }

    return program;
}

Intcode_Program parse_intcode_program_string(const std::string& intcode_program)
{
    Intcode_Program program;

    if(!intcode_program.empty())
    {
        stringstream ss(intcode_program);
        string intcode;
        int index = 0;
        while (getline(ss, intcode, ','))
        {
            if (!intcode.empty())
            {
                program[index] = stoll(intcode.c_str());
                index += 1;
            }
        }
    }

    return program;
}