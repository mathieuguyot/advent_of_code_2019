#include <iostream>
#include <chrono>

inline std::chrono::time_point<std::chrono::high_resolution_clock> get_start_time()
{
    return std::chrono::high_resolution_clock::now();
}

inline void log_end_aoc_part(std::chrono::time_point<std::chrono::high_resolution_clock> start_time, std::string res, int number, int part)
{
    auto stop_time = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
    std::cout << "# AOC_" << number << " (PART_" << part << ") (" << duration.count() << " MICROSECONDS) : " << res << std::endl; 
}