#include "aoc_2.hpp"

#include <fstream>
#include <sstream>

using namespace std;

int find_noun_and_verb(const Intcode_Program& program)
{
    for(int cur_noun = 0 ; cur_noun <= 99; cur_noun++)
    {
        for(int cur_verb = 0 ; cur_verb <= 99; cur_verb++)
        {
            Intcode_Program cur_program(program);
            cur_program[1] = cur_noun;
            cur_program[2] = cur_verb;
            Computation_result res = compute(cur_program);
            if(res.second[0] == 19690720)
            {
                return 100 * cur_noun + cur_verb;
            }
        }
    }
    return -1;
}
