#include "aoc_7.hpp"

#include <bits/stdc++.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int run_sequence(const Intcode_Program& program, const std::vector<int>& phases)
{
    int output_signal = 0;
    for(int phase : phases)
    {
        Parameter_queue inputs;
        inputs.push(phase);
        inputs.push(output_signal);
        Computation_result res = compute(program, inputs);
        if(res.return_code != Return_code::ok)
        {
            output_signal -1;
            break;
        }
        else
        {
            output_signal = res.output_queue.back();
        }
    }
    return output_signal;
}

int run_sequence_loopback_mode(const Intcode_Program& program, const std::vector<int>& phases)
{
    int output_signal = 0;

    Parameter_queue input_queues_0, input_queues_1, input_queues_2, input_queues_3, input_queues_4;
    input_queues_0.push(phases[0]);
    input_queues_0.push(0);
    input_queues_1.push(phases[1]);
    input_queues_2.push(phases[2]);
    input_queues_3.push(phases[3]);
    input_queues_4.push(phases[4]);

    std::function<void(int)> output_callback_0 = [&](int output) {
        input_queues_1.push(output);
    };

    std::function<void(int)> output_callback_1 = [&](int output) {
        input_queues_2.push(output);
    };

    std::function<void(int)> output_callback_2 = [&](int output) {
        input_queues_3.push(output);
    };

    std::function<void(int)> output_callback_3 = [&](int output) {
        input_queues_4.push(output);
    };

    std::function<void(int)> output_callback_4 = [&](int output) {
        input_queues_0.push(output);
        output_signal = output;
    };

    thread computation_1([&]{compute(program, std::ref(input_queues_1), output_callback_1, true);});
    thread computation_2([&]{compute(program, std::ref(input_queues_2), output_callback_2, true);});
    thread computation_3([&]{compute(program, std::ref(input_queues_3), output_callback_3, true);});
    thread computation_4([&]{compute(program, std::ref(input_queues_4), output_callback_4, true);});
    thread computation_0([&]{compute(program, std::ref(input_queues_0), output_callback_0, true);});

    computation_0.join();
    computation_1.join();
    computation_2.join();
    computation_3.join();
    computation_4.join();

    return output_signal;
}

int find_highest_thruster_signal(const Intcode_Program& program)
{
    int phases[] = {0,1,2,3,4};
    int n = sizeof(phases) / sizeof(phases[0]); 
    int highest_thruster_signal = -1;
    do 
    {
        std::vector<int> current_phases = {phases[0], phases[1], phases[2], phases[3], phases[4]};
        int cur_thruster_signal = run_sequence(program, current_phases);
        if(cur_thruster_signal > highest_thruster_signal)
        {
            highest_thruster_signal = cur_thruster_signal;
        }
    } while (next_permutation(phases, phases + n));

    return highest_thruster_signal;
}

int find_highest_thruster_signal_loopback_mode(const Intcode_Program& program)
{
    int phases[] = {5,6,7,8,9};
    int n = sizeof(phases) / sizeof(phases[0]); 
    int highest_thruster_signal = -1;
    do 
    {
        std::vector<int> current_phases = {phases[0], phases[1], phases[2], phases[3], phases[4]};
        int cur_thruster_signal = run_sequence_loopback_mode(program, current_phases);
        if(cur_thruster_signal > highest_thruster_signal)
        {
            highest_thruster_signal = cur_thruster_signal;
        }
    } while (next_permutation(phases, phases + n));
    return highest_thruster_signal;
}