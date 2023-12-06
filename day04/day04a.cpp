#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

int main()
{
    std::ifstream inputFile("day04_input.txt");

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

    int sum = 0;

    for (const auto &line : lines)
    {
        int card_num;
        int colon_index = line.find(":");
        int first_space_index = line.find_first_of(' ');

        std::string game_info = line.substr(colon_index + 1);

        bool recording_winners = true;
        std::string current_num_string = "";
        std::vector<int> winners;
        std::vector<int> selections;
        for (const auto &character : game_info)
        {
            std::string current_num;

            if (character == '|')
            {
                recording_winners = false;
                continue;
            }
            if (current_num_string.length() > 0 && character == ' ')
            {
                // this is the end of a number
                if (recording_winners)
                {
                    winners.push_back(std::stoi(current_num_string));
                }
                else
                {
                    selections.push_back(std::stoi(current_num_string));
                }
                current_num_string = "";
                continue;
            }
            if (isdigit(character))
            {
                current_num_string += character;
            }
        }
        selections.push_back(std::stoi(current_num_string));

        std::sort(winners.begin(), winners.end());
        std::sort(selections.begin(), selections.end());

        std::vector<int> intersectionVector(winners.size() + selections.size());

        auto union_numbers = std::set_intersection(winners.begin(), winners.end(), selections.begin(), selections.end(), intersectionVector.begin());

        // Resize the result vector to fit the actual elements of the union
        intersectionVector.resize(union_numbers - intersectionVector.begin());

        int num_successes = intersectionVector.size();
        if (num_successes > 0)
        {
            sum += std::pow(2, num_successes - 1);
        }
    }
    std::cout << sum << std::endl;

    return 0;
}
