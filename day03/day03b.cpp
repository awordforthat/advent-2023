#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>
#include <map>

bool specialCharsInEdges(const std::vector<std::string> lines, const std::string &line, const int &line_index, const int &number_start_index, const std::string &number_as_string, std::vector<std::tuple<int, int>> &asterisks);
bool specialCharactersInLine(const std::string &inputString, std::vector<std::tuple<int, int>> &asterisks, const int line_num, const int edge_start_index);

bool specialCharactersInLine(const std::string &inputString, std::vector<std::tuple<int, int>> &asterisks, const int line_num, const int edge_start_index)
{
    int counter = 0;
    bool has_specials = false;
    for (const auto &character : inputString)
    {
        if (!isdigit(character) && character != '.')
        {
            has_specials = true;
        }
        if (character == '*')
        {
            asterisks.push_back(std::make_tuple(line_num, edge_start_index + counter));
        }
        counter++;
    }
    return has_specials;
}

bool specialCharsInEdges(const std::vector<std::string> lines, const std::string &line, const int &line_index, const int &number_start_index, const std::string &number_as_string, std::vector<std::tuple<int, int>> &asterisks)
{
    bool has_special_chars = false;

    if (line_index > 0)
    {
        const std::string &upper_line = lines[line_index - 1];
        const std::string &upper_edge = upper_line.substr(std::max(number_start_index - 1, 0), number_as_string.length() + 2);
        if (specialCharactersInLine(upper_edge, asterisks, line_index - 1, std::max(number_start_index - 1, 0)))
        {
            has_special_chars = true;
        }
    }
    // Check left neighbor
    if (number_start_index > 0)
    {

        if (specialCharactersInLine(line.substr(number_start_index - 1, 1), asterisks, line_index, std::max(number_start_index - 1, 0)))
        {
            has_special_chars = true;
        }
    }
    // Check right neighbor
    if (number_start_index + number_as_string.length() < line.length())
    {
        if (specialCharactersInLine(line.substr(number_start_index + number_as_string.length(), 1), asterisks, line_index, number_start_index + number_as_string.length()))
        {
            has_special_chars = true;
        }
    }
    // Check lower edge
    if (line_index < lines.size() - 1)
    {
        const std::string &lower_line = lines[line_index + 1];
        const std::string &lower_edge = lower_line.substr(std::max(number_start_index - 1, 0), number_as_string.length() + 2);
        if (specialCharactersInLine(lower_edge, asterisks, line_index + 1, std::max(number_start_index - 1, 0)))
        {
            has_special_chars = true;
        }
    }
    return has_special_chars;
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
    std::vector<std::tuple<int, int>> asterisk_locations;
    std::map<std::tuple<int, int>, std::vector<std::string>> asterisk_map;
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
            else if (!isdigit(character))
            {
                if (number_start_index > -1)
                {
                    // this is the end of a number
                    int prior_num_asterisks = asterisk_locations.size();
                    bool has_special = specialCharsInEdges(lines, line, line_index, number_start_index, number_as_string, asterisk_locations);
                    if (has_special && asterisk_locations.size() > prior_num_asterisks)
                    {
                        asterisk_map[asterisk_locations.back()].push_back(number_as_string);
                    }
                    // Reset for the next string
                    number_start_index = -1;
                    number_as_string = "";
                }
            }

            character_index++;
        }

        // Corner case: we might have ended the line on a digit, and so never got the chance to
        // process the number it's part of. Process it now, if that's the case.
        int prior_num_asterisks = asterisk_locations.size();
        bool has_special = specialCharsInEdges(lines, line, line_index, number_start_index, number_as_string, asterisk_locations);

        if (number_start_index > -1 && has_special && asterisk_locations.size() > prior_num_asterisks)
        {
            asterisk_map[asterisk_locations.back()].push_back(number_as_string);
        }
        ++line_index;
    }

    // Now filter the list of asterisks down to only those that have two related numbers
    std::map<std::tuple<int, int>, std::vector<std::string>> filtered_asterisks;

    int sum = 0;
    for (const auto &pair : asterisk_map)
    {
        if (pair.second.size() == 2)
        {
            sum += std::stoi(pair.second.front()) * std::stoi(pair.second.back());
        }
    }

    std::cout << sum << " ";

    return 0;
}
