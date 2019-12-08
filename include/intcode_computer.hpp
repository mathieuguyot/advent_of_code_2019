#ifndef DEF_AOC_6_HPP
#define DEF_AOC_6_HPP

#include <map>
#include <string>
#include <vector>

enum class Opcode {
    unknown = -1,
    add = 1,
    times = 2,
    end = 99,
    input = 3,
    output = 4
};

enum class Mode {
    position = 0,
    immediate = 1
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

Instruction int_to_instruction(int opcode);

enum class Return_code {
    ok,
    wrong_opcode,
    wrong_index,
};

using Intcode_Program = std::map<int, int>;
using Computation_result = std::pair<Return_code, Intcode_Program>;

Computation_result compute(const Intcode_Program& program, const std::vector<int>& input_parameters = std::vector<int>());
Intcode_Program parse_intcode_program_file(const std::string& file_path);

#endif