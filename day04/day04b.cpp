#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <map>

class Winnings
{
public:
    Winnings() : card_num(0), num_copies(1) {}
    // Constructor
    Winnings(int card_num) : card_num(card_num) {}

    // Member variables
    int card_num;
    int num_copies = 1;

    void add_copies(int copies_to_add)
    {
        num_copies += copies_to_add;
    }

    int get_num_copies() const
    {
        return num_copies;
    }
};

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
    std::map<int, Winnings> winnings;
    winnings[1] = Winnings(1);

    // Read lines from the file
    std::string line;
    while (std::getline(inputFile, line))
    {
        lines.push_back(line);
    }

    inputFile.close();

    for (const auto &line : lines)
    {

        int colon_index = line.find(":");
        int first_space_index = line.find_first_of(' ');
        int card_num = stoi(line.substr(first_space_index + 1, colon_index - first_space_index));

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

        std::vector<int> win_targets;
        for (int i = 1; i <= num_successes; ++i)
        {
            win_targets.push_back(card_num + i);
        }

        auto current_card = winnings[card_num];
        for (const int win_target : win_targets)
        {
            if (winnings.count(win_target) == 0)
            {
                winnings[win_target] = Winnings(win_target);
            }
            winnings[win_target].add_copies(1 * current_card.get_num_copies());
        }
    }

    int sum = 0;
    for (const auto &pair : winnings)
    {
        // pair.first is the key, pair.second is the value
        std::cout << "Key: " << pair.first << ", Value: " << pair.second.get_num_copies() << std::endl;
        sum += pair.second.get_num_copies();
    }

    std::cout << sum << std::endl;

    return 0;
}
