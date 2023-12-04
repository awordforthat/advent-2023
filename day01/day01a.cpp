#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
    std::ifstream inputFile("day01a_input.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    // Vector to store lines
    std::vector<std::string> lines;
    std::vector<std::string> codes;

    // Read lines from the file
    std::string line;
    while (std::getline(inputFile, line))
    {
        lines.push_back(line);
    }

    inputFile.close();

    std::string first_digit;
    std::string last_digit;

    for (const auto &l : lines)
    {

        for (const char letter : l)
        {
            if (isdigit(letter))
            {
                first_digit = letter;
                break;
            }
        }

        std::string reversedLine = l;
        std::reverse(reversedLine.begin(), reversedLine.end());
        for (const char letter : reversedLine)
        {
            if (isdigit(letter))
            {
                last_digit = letter;
                break;
            }
        }

        codes.push_back(first_digit + last_digit);
    }

    int sum = 0;

    for (const auto &code : codes)
    {
        sum += std::stoi(code);
        std::cout << sum << std::endl;
    }

    std::cout << sum << std::endl;

    return 0;
}
