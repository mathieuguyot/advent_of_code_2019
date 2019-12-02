#ifndef DEF_AOC_2_HPP
#define DEF_AOC_2_HPP

#include <vector>
#include <string>

enum return_code {
    EXECUTION_OK,
    EMPTY_PROGRAM,
    WRONG_OPCODE,
    WRONG_INDEX
};

typedef std::vector<int> intcode_program_t;
typedef std::pair<return_code, intcode_program_t> program_execution_result_t;

int find_noun_and_verb(const intcode_program_t& program);
program_execution_result_t execute_program(const intcode_program_t& program);
intcode_program_t parse_intcode_program(const std::string& file_path);

#endif