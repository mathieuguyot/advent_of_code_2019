#include "aoc_1.hpp"

#include <fstream>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

int compute_required_fuel_part_1(const module_masses_t& masses)
{
    function<int(int)> mass_computor = [](int mass){ return mass / 3 - 2; };

    auto accumulator = [&mass_computor](int total, int mass) { 
        return total + mass_computor(mass); 
    };

    return accumulate(masses.begin(), masses.end(), 0, accumulator);
}

int compute_required_fuel_part_2(const module_masses_t& masses)
{
    function<int(int)> mass_computor;
    mass_computor = [&mass_computor](int mass) { 
        int res = mass / 3 - 2; 
        return res <= 6 ? res : res + mass_computor(res);
    };

    auto accumulator = [&mass_computor](int total, int mass) { 
        return total + mass_computor(mass); 
    };

    return accumulate(masses.begin(), masses.end(), 0, accumulator);
}

module_masses_t parse_module_masses_file(const string& file_path)
{
    module_masses_t masses;

    ifstream file_stream(file_path);
    if(!file_stream.fail())
    {
        string mass;
        while(!file_stream.eof()) {
            getline(file_stream, mass);
            if(!mass.empty())
            {
                masses.push_back(atoi(mass.c_str()));
            }
        }
    }    

    return masses;
}