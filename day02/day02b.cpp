#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

int main()
{
    std::ifstream inputFile("day02_input.txt");

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

    int sum = 0;
    for (const auto &line : lines)
    {

        const int first_space_index = line.find_first_of(" ");
        const int colon_index = line.find(":");
        std::string game_id = line.substr(first_space_index, colon_index - first_space_index);

        std::string color_info = line.substr(colon_index + 2);
        color_info.erase(std::remove_if(color_info.begin(), color_info.end(), ::isspace), color_info.end());
        std::istringstream iss(color_info);
        std::vector<std::string> draw_instances;

        std::string draw_instance;
        // Split into samples
        while (std::getline(iss, draw_instance, ';'))
        {
            draw_instances.push_back(draw_instance);
        }

        std::vector<std::string> color_data_points;
        // Now split each sample into colors
        for (const std::string &draw_instance : draw_instances)
        {
            std::istringstream iss(draw_instance);

            std::string color_item;
            while (std::getline(iss, color_item, ','))
            {
                color_data_points.push_back(color_item);
            }
        }

        int max_red = 0;
        int max_green = 0;
        int max_blue = 0;

        for (const std::string &color_item : color_data_points)
        {
            size_t splitPosition = 0;
            for (; splitPosition < color_item.size(); ++splitPosition)
            {
                if (!std::isdigit(color_item[splitPosition]))
                {
                    break;
                }
            }

            std::string count_str = color_item.substr(0, splitPosition);
            int count = std::stoi(count_str);
            std::string color = color_item.substr(splitPosition);

            if (color == "red" && count > max_red)
            {
                max_red = count;
            }

            if (color == "green" && count > max_green)
            {
                max_green = count;
            }

            if (color == "blue" && count > max_blue)
            {
                max_blue = count;
            }
        }

        int power = max_red * max_green * max_blue;
        std::cout << "Game " << game_id << ": power= " << power << std::endl;
        sum += power;
        std::cout << sum << std::endl;
    }

    return 0;
}
