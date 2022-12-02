#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>

int main() {

    std::vector<uint32_t> elvesCalories;

    std::fstream f;
    f.open("input.txt", std::ios::in);

    uint32_t sumCalories = 0;
    uint32_t currentElfCalories = 0;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            // std::cout << line << std::endl;
            if(line == "")
            {
                elvesCalories.push_back(currentElfCalories);

                currentElfCalories = 0;
                continue;
            }

            currentElfCalories += std::stoi(line);
        }

        elvesCalories.push_back(currentElfCalories);

        f.close();
    }

    std::sort(elvesCalories.begin(), elvesCalories.end(), std::greater<int>());

    for(int i=0; i < 3; i++ )
    {
        std::cout << elvesCalories[i] << std::endl;
        sumCalories += elvesCalories[i];
    }

    std::cout << sumCalories << std::endl;

}