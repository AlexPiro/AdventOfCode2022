#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
// #include <type_traits>
#include <sstream>
// #include <iterator>

int getPriority(char& letter)
{
    char alphabet[53] = { '#','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    
    int n = sizeof(alphabet) / sizeof(alphabet[0]);

    return std::find(alphabet, alphabet + n, letter) - alphabet;

}

int findBadgeInGroup(std::vector<std::string>& group)
{

    int priority = -1;
    for (size_t i = 0; i < group[0].size(); i++)
    {
        char currentChar = group[0][i];
        bool itemFound = false;

        for (size_t j = 1; j < group.size(); j++)
        {
            /* code */
            std::size_t found = group[j].find(currentChar);

            if(found != std::string::npos)
            {
                if(j == group.size()-1)
                {
                    priority = getPriority(currentChar);
                    itemFound = true;
                    break;
                }
                continue;
            }
            else
            {
                break;
            }
        }

        if(itemFound) break;
        
    }

    std::cout << "Priority : " << priority << std::endl;

    return priority;
}

int main() {

    std::fstream f;
    f.open("input_ex.txt", std::ios::in);

    uint32_t prioritySum = 0;

    std::vector<std::string> lines;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            //put all lines into an array            
            lines.push_back(line);
            if(lines.size() == 3)
            {
                // create a group every 3 lines
                // findBadge in group and add to prioritysum
                prioritySum += findBadgeInGroup(lines);

                lines.clear();
            }
        }
        
        std::cout << prioritySum << std::endl;

        f.close();
    }

}