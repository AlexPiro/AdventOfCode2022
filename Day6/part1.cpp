#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

const int SOP_LENGTH = 4;

bool checkIfDuplicatedChar(std::string& msg, int& startIndex)
{
    int endIndex = startIndex + SOP_LENGTH;
    for (int i = startIndex; i < endIndex; i++)
    {
        char currentChar = msg[i];
        for (int j = i+1; j < endIndex; j++)
        {
            if(currentChar == msg[j])
            {
                return true;
            }
        }
        
    }
    
    return false;
}

int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    int charBeforeFirstSOP = 0;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            for (int i = 0; i < line.size(); i++)
            {
                bool duplicateChar = checkIfDuplicatedChar(line, i);

                if(!duplicateChar)
                {
                    charBeforeFirstSOP = i + SOP_LENGTH;
                    break;
                }
            }

            std::cout << charBeforeFirstSOP << std::endl;
            
        }

       


        f.close();
    }

}