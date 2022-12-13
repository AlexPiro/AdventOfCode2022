#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>


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

    std::string CRTRows[6];

    int spritePosition = 1;
    int currentCycle = 0;

    const int CYCLE_LENGTH = 40;

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
                int rowIndex = (int)floor(currentCycle / CYCLE_LENGTH);
                int pixelPosition = (int)(currentCycle % CYCLE_LENGTH);
                char pixel = '.';
                if(pixelPosition >= spritePosition-1 && pixelPosition <= spritePosition+1)
                {
                    pixel = '#';
                }

                CRTRows[rowIndex] += pixel;               
                currentCycle +=1;
            }

            spritePosition += valueToAdd;
            
        }

        for (int i = 0; i < 6;i++)
        {
            std::cout << CRTRows[i] << std::endl;
        }
        
        
        f.close();
    }

}