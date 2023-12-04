#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

bool edgesContainSpecialCharacter(const std::vector<std::string> lines, const std::string &line, const int &line_index, const int &number_start_index, const std::string &number_as_string);
bool containsSpecialCharacter(const std::string &inputString);

bool containsSpecialCharacter(const std::string &inputString)
{
    int counter = 0;
    for (const auto &character : inputString)
    {
        if (!isdigit(character) && character != '.')
        {
            return true;
        }
    }
    return false;
}

bool edgesContainSpecialCharacter(const std::vector<std::string> lines, const std::string &line, const int &line_index, const int &number_start_index, const std::string &number_as_string)
{
    if (line_index > 0)
    {
        const std::string &upper_line = lines[line_index - 1];
        const std::string &upper_edge = upper_line.substr(std::max(number_start_index - 1, 0), number_as_string.length() + 2);
        if (containsSpecialCharacter(upper_edge))
        {
            return true;
        }
    }
    // Check left neighbor
    if (number_start_index > 0)
    {

        if (containsSpecialCharacter(line.substr(number_start_index - 1, 1)))
        {
            return true;
        }
    }
    // Check right neighbor
    if (number_start_index + number_as_string.length() < line.length() - 1)
    {
        if (containsSpecialCharacter(line.substr(number_start_index + number_as_string.length(), 1)))
        {
            return true;
        }
    }
    // Check lower edge
    if (line_index < lines.size() - 1)
    {
        const std::string &lower_line = lines[line_index + 1];
        const std::string &lower_edge = lower_line.substr(std::max(number_start_index - 1, 0), number_as_string.length() + 2);
        if (containsSpecialCharacter(lower_edge))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    std::ifstream inputFile("day03_input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Vector to store lines
    std::vector<std::string> lines;

    // Read lines from the file
    std::string line;
    while (std::getline(inputFile, line))
    {
        lines.push_back(line);
    }

    inputFile.close();

    std::vector<std::string> config_numbers;

    int line_index = 0;
    for (const std::string &line : lines)
    {
        int number_start_index = -1;
        std::string number_as_string = "";

        int character_index = 0;
        for (const char &character : line)
        {

            if (isdigit(character) && number_start_index == -1)
            {
                // this is the start of a number
                number_as_string += character;
                number_start_index = character_index;
            }
            else if (isdigit(character))
            {
                // this is the continuation of a number
                number_as_string += character;
            }
            else if (number_start_index > -1 && !isdigit(character))
            {

                // std::cout << "Found a number: " << line.substr(number_start_index, number_as_string.length()) << std::endl;
                bool has_special = edgesContainSpecialCharacter(lines, line, line_index, number_start_index, number_as_string);
                if (has_special)
                {

                    config_numbers.push_back(number_as_string);
                }
                // Reset for the next string
                number_start_index = -1;
                number_as_string = "";
            }
            ++character_index;
        }
        if (number_start_index > -1 && edgesContainSpecialCharacter(lines, line, line_index, number_start_index, number_as_string))
        {
            config_numbers.push_back(number_as_string);
        }
        ++line_index;
    }
    std::cout << "Vector elements: ";
    int sum = 0;
    for (const std::string &element : config_numbers)
    {
        std::cout << element << " ";
        sum += stoi(element);
    }
    std::cout << std::endl
              << sum;

    return 0;
}

// too low: 503281