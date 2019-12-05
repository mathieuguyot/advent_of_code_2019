#include "aoc_4.hpp"

#include <iostream>

using namespace std;

vector<int> find_correct_passwords()
{
    vector<int> valid_passwords;

    for(int i = MIN_PASSWORD; i <= MAX_PASSWORD; i++)
    {
        bool same_adjacent_digit_exists = false;
        bool never_decrease = true;

        int password = i;
        int prev_digit = -1;
        do {
            int cur_digit = password%10;
            if(cur_digit == prev_digit)
            {
                same_adjacent_digit_exists = true;
            }
            if(prev_digit != -1 && cur_digit > prev_digit)
            {
                never_decrease = false;
            }
            prev_digit = cur_digit;
        }
        while (password/=10);

        if(same_adjacent_digit_exists && never_decrease)
        {
            valid_passwords.push_back(i);
        }
    }

    return valid_passwords;
}