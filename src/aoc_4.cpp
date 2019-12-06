#include "aoc_4.hpp"

using namespace std;

vector<int> find_correct_passwords_part_two()
{
    vector<int> valid_passwords;

    for(int i = MIN_PASSWORD; i <= MAX_PASSWORD; i++)
    {
        bool same_adjacent_digit_exists = false;
        bool never_decrease = true;
        bool not_part_of_larger_group = true;
        bool two_digit_group_exists = false;

        int password = i;
        int same_digit_count = 0;

        int prev_digit = -1;
        do {
            int cur_digit = password%10;
            if(cur_digit == prev_digit && same_digit_count >= 1)
            {
                not_part_of_larger_group = false;
                same_digit_count += 1;
            }
            else if(cur_digit == prev_digit)
            {
                same_adjacent_digit_exists = true;
                same_digit_count += 1;
                if(not_part_of_larger_group == false)
                {
                    not_part_of_larger_group = true;
                }
            }
            else
            {
                if(same_digit_count == 1)
                {
                    two_digit_group_exists = true;
                }
                same_digit_count = 0;
            }
            if(prev_digit != -1 && cur_digit > prev_digit)
            {
                never_decrease = false;
            }
            prev_digit = cur_digit;
        }
        while (password/=10);

        if(same_adjacent_digit_exists && never_decrease && (not_part_of_larger_group || two_digit_group_exists))
        {
            valid_passwords.push_back(i);
        }
    }

    return valid_passwords;
}

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