#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>



std::vector<std::string> getInstruction(std::string& line)
{
    std::vector<std::string> instruction;
    std::istringstream iss (line);
    std::string s;
    while(getline(iss, s, ' '))
    {
        instruction.push_back(s);
    }

    return instruction;
}


int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    std::vector<int> main_cycles { 20, 60, 100, 140, 180, 220 };

    int X = 1;
    int currentCycle = 0;
    int result = 0;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            std::vector<std::string> instruction = getInstruction(line);

            int cyclesNumber = 0;
            int valueToAdd = 0;

            if(instruction[0] == "noop")
            {
                cyclesNumber = 1;
            }
            else if(instruction[0] == "addx")
            {
                cyclesNumber = 2;
                valueToAdd = stoi(instruction[1]);
            }   
            else
            {
                std::cout << "Unknown instruction" << std::endl;
            }

            for (int i = 0; i < cyclesNumber; i++)
            {
                currentCycle +=1;

                if(std::find(main_cycles.begin(), main_cycles.end(), currentCycle) != main_cycles.end())
                {
                    result += currentCycle * X;
                }
            }

            X += valueToAdd;
            
        }      
        
        std::cout << result << std::endl;

        f.close();
    }

}