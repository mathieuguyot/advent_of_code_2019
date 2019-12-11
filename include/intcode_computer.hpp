#ifndef DEF_AOC_6_HPP
#define DEF_AOC_6_HPP

#include <map>
#include <string>
#include <queue>
#include <functional>

using Code = long long;

enum class Opcode {
    unknown = -1,
    add = 1,
    times = 2,
    end = 99,
    input = 3,
    output = 4,
    jump_if_true = 5,
    jump_if_false = 6,
    less_than = 7,
    equals = 8,
    adjust_relative_base = 9
};

enum class Mode {
    position = 0,
    immediate = 1,
    relative = 2
};

struct Instruction {
    Opcode code;
    Mode param1_mode;
    Mode param2_mode;
    Mode param3_mode;

    bool operator==(const Instruction& i) const 
    {
        return i.code == code 
            && i.param1_mode == param1_mode
            && i.param2_mode == param2_mode
            && i.param3_mode == param3_mode;
    }
};

Instruction int_to_instruction(Code opcode);

enum class Return_code {
    ok,
    wrong_opcode,
    wrong_index,
    empty_input_queue
};

using Intcode_Program = std::map<Code, Code>;
using Parameter_queue = std::queue<Code>;
using Ouput_callback = std::function<void(Code)>;

struct Computation_result {
    Return_code return_code;
    Intcode_Program program;
    Parameter_queue output_queue;
};

Computation_result compute(
    const Intcode_Program& program
);

Computation_result compute(
    const Intcode_Program& program,
    Parameter_queue& input,
    const Ouput_callback& output_callback = [](Code output){},
    bool wait_for_inputs =  false
);

Intcode_Program parse_intcode_program_file(const std::string& file_path);
Intcode_Program parse_intcode_program_string(const std::string& intcode_program);

#endif