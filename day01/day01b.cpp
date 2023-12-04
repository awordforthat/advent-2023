#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

int main()
{
    std::ifstream inputFile("day01_input.txt");
    // Vector to store lines
    std::vector<std::string> lines;

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Read lines from the file
    std::string line;
    while (std::getline(inputFile, line))
    {
        lines.push_back(line);
    }

    inputFile.close();

    std::vector<std::string> codes;
    std::map<std::string, std::string> digits;
    std::string first_digit;
    std::string last_digit;
    digits["one"] = "1";
    digits["two"] = "2";
    digits["three"] = "3";
    digits["four"] = "4";
    digits["five"] = "5";
    digits["six"] = "6";
    digits["seven"] = "7";
    digits["eight"] = "8";
    digits["nine"] = "9";

    for (const auto &line : lines)
    {
        int first_int_index = -1;
        int last_int_index = -1;
        int first_text_index = 99999;
        int last_text_index = -1;
        std::string first_text_value = "";
        std::string last_text_value = "";
        std::string first_int_value = "";
        std::string last_int_value = "";

        for (const auto &digit_pair : digits)
        {
            const int text_digit_index = line.find(digit_pair.first);

            if (text_digit_index >= 0 && text_digit_index < first_text_index)
            {
                first_text_index = text_digit_index;
                first_text_value = digit_pair.second;
            }
        }

        int counter = 0;
        for (const char letter : line)
        {
            if (isdigit(letter))
            {
                first_int_value = letter;
                first_int_index = counter;
                break;
            }
            counter++;
            first_digit = letter;
        }

        if (first_text_index == -1)
        {
            first_digit = first_int_value;
        }
        else if (first_int_index == -1)
        {
            first_digit = first_text_value;
        }
        else if (first_text_index < first_int_index)
        {
            first_digit = first_text_value;
        }
        else
        {
            first_digit = first_int_value;
        }

        std::string reversedLine = line;
        std::reverse(reversedLine.begin(), reversedLine.end());
        counter = 0;
        for (const char letter : reversedLine)
        {
            if (isdigit(letter))
            {
                last_int_value = letter;
                last_int_index = reversedLine.length() - counter - 1;
                break;
            }
            counter++;
        }

        for (const auto &digit_pair : digits)
        {
            const int text_digit_index = line.find(digit_pair.first);

            if (text_digit_index >= 0 && text_digit_index > last_text_index)
            {
                last_text_index = text_digit_index;
                last_text_value = digit_pair.second;
            }
        }

        if (last_text_index == -1)
        {
            last_digit = last_int_value;
        }
        else if (last_int_index == -1)
        {
            last_digit = last_text_value;
        }
        else if (last_text_index > last_int_index)
        {
            last_digit = last_text_value;
        }
        else
        {
            last_digit = last_int_value;
        }

        codes.push_back(first_digit + last_digit);
        std::cout << first_digit << last_digit << std::endl;
    }

    int sum = 0;

    for (const auto &code : codes)
    {
        sum += std::stoi(code);
    }

    std::cout << sum << std::endl;

    return 0;
}
