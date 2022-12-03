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

int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    uint32_t prioritySum = 0;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            std::cout << "Line size : " << line.size() << std::endl;
            size_t mid = line.size() / 2;

            bool itemFound = false;

            std::string secondPart = line.substr(mid, line.size());

            // std::cout << "Second part: " << secondPart << std::endl;

            for (size_t i = 0; i < mid ; i++)
            {
                char currentChar = line[i];

                std::size_t found = secondPart.find(currentChar);

                if(found != std::string::npos)
                {
                    std::cout << " found char " << currentChar << std::endl;

                    int priority = getPriority(currentChar);

                    std::cout << "Priority " << priority << std::endl;
                    prioritySum += priority;
                    itemFound = true;
                    break;
                }

                if(itemFound) break;
                
            }
            
        }
        
        std::cout << prioritySum << std::endl;

        f.close();
    }

}