#include <catch2/catch.hpp>

#include "intcode_computer.hpp"
#include "utils.hpp"

#include <iostream>

using namespace std;

TEST_CASE("INTCODE_COMPUTER - good path", "[parse_intcode_program]")
{
    Intcode_Program program = parse_intcode_program_file("../data/aoc_2.txt");
    REQUIRE(program.size() == 153);
    REQUIRE(program[0] == 1);
    REQUIRE(program[1] == 0);
    REQUIRE(program[151] == 14);
    REQUIRE(program[152] == 0);
}

TEST_CASE("INTCODE_COMPUTER - bad path", "[parse_intcode_program]") 
{
    Intcode_Program program = parse_intcode_program_file("foo.txt");
    REQUIRE(program.size() == 0);
}

TEST_CASE("INTCODE_COMPUTER - int_to_instruction", "[int_to_instruction]") 
{
    Instruction i = {Opcode::unknown, Mode::position, Mode::position, Mode::position};
    REQUIRE(int_to_instruction(42) == i);

    i = {Opcode::add, Mode::position, Mode::position, Mode::position};
    REQUIRE(int_to_instruction(1) == i);

    i = {Opcode::times, Mode::position, Mode::position, Mode::position};
    REQUIRE(int_to_instruction(2) == i);

    i = {Opcode::input, Mode::position, Mode::position, Mode::position};
    REQUIRE(int_to_instruction(3) == i);

    i = {Opcode::output, Mode::position, Mode::position, Mode::position};
    REQUIRE(int_to_instruction(4) == i);

    i = {Opcode::end, Mode::position, Mode::position, Mode::position};
    REQUIRE(int_to_instruction(99) == i);

    i = {Opcode::end, Mode::position, Mode::position, Mode::immediate};
    REQUIRE(int_to_instruction(10099) == i);

    i = {Opcode::add, Mode::immediate, Mode::immediate, Mode::position};
    REQUIRE(int_to_instruction(1101) == i);
    
    i = {Opcode::add, Mode::immediate, Mode::position, Mode::position};
    REQUIRE(int_to_instruction(101) == i);

    i = {Opcode::times, Mode::immediate, Mode::position, Mode::position};
    REQUIRE(int_to_instruction(102) == i);

    i = {Opcode::unknown, Mode::position, Mode::position, Mode::position};
    REQUIRE(int_to_instruction(110) == i);

    i = {Opcode::unknown, Mode::position, Mode::position, Mode::position};
    REQUIRE(int_to_instruction(10142) == i);
}
