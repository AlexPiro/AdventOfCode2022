#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <math.h>
#include <regex>

std::string ReplaceInString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

std::vector<char>* parseCrateStacks(std::vector<std::string>& rawCrateInput, int& stackNb)
{
    //every column is a vector of char
    stackNb = (rawCrateInput[0].size() + 1 ) / 4;

    std::vector<char>* crateStacks = new std::vector<char>[stackNb];

    for (int i = rawCrateInput.size()-2; i >= 0; i--)
    {
        std::string lineToParse = rawCrateInput[i];
        for (int j = 0; j < lineToParse.size(); j++)
        {
            char currentChar = lineToParse[j];
            if(currentChar != '[' && 
                currentChar != ']' &&
                currentChar != ' ')
            {
                int col = j / 4;
                crateStacks[col].push_back(currentChar);
            }
        }
    }

    return crateStacks;
    
}

int* getInstruction(std::string& rawInstruction)
{
    int* instruction = new int[3];
    int foundInst = 0;

    rawInstruction = ReplaceInString(rawInstruction, "move ", "");
    rawInstruction = ReplaceInString(rawInstruction, " from ", ",");
    rawInstruction = ReplaceInString(rawInstruction, " to ", ",");

    std::cout << rawInstruction << std::endl;
    std::stringstream iss (rawInstruction);
    std::string instruction_nb;
    while(getline(iss, instruction_nb, ','))
    {
        instruction[foundInst] = std::stoi(instruction_nb);
        foundInst += 1;
    }  


    return instruction;
    
}


void displayCrateStacks(std::vector<char>* crateStacks, int& stackNb)
{
    for (int i = 0; i < stackNb; i++)
    {
        std::vector<char> col = crateStacks[i];
        for (int j = 0; j < col.size(); j++)
        {
            std::cout << col[j] << ' ';
        }

        std::cout << std::endl;
        
    }
}

std::string getMessageFromStacks(std::vector<char>* crateStacks, int& stackNb)
{
    std::string message = "";
    for (int i = 0; i < stackNb; i++)
    {
        std::vector<char> col = crateStacks[i];
        char lastChar = ' ';
        if(col.size() > 0)
        {
            lastChar = col[col.size()-1];
        }

        message += lastChar;

        std::cout << std::endl;
        
    }

    return message;
}

int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    std::vector<std::string> rawCrateInput;
    std::vector<char>* crateStacks;
    bool instructionsFound = false;
    int stackNb = 0;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            if(!instructionsFound)
            {
                if(line != "") // separation from crate map and instructions
                {
                    rawCrateInput.push_back(line);
                }
                else
                {
                    //parse input
                    crateStacks = parseCrateStacks(rawCrateInput, stackNb);

                    displayCrateStacks(crateStacks, stackNb);

                    instructionsFound = true;
                }
            }
            else
            {
                // do every instructions
                int* instruction = getInstruction(line);

                int moveNb = instruction[0];
                int fromStackNb = instruction[1]-1;
                int toStackNb = instruction[2]-1;
   
                std::vector<char> tempStack;

                for (int i = 0; i < moveNb; i++)
                {
                    int stackSize = crateStacks[fromStackNb].size();
                    if(stackSize <= 0)
                    {
                        break;
                    }

                    char charToMove = crateStacks[fromStackNb][stackSize-1];
                    
                    tempStack.push_back(charToMove);
                    crateStacks[fromStackNb].pop_back();
                }

                while(tempStack.size() > 0)
                {
                    char charToMove = tempStack[tempStack.size()-1];
                    crateStacks[toStackNb].push_back(charToMove);
                    tempStack.pop_back();
                }

                displayCrateStacks(crateStacks, stackNb);
                    
            }
      
        }

        //parse the result;
        std::string message = getMessageFromStacks(crateStacks, stackNb);
        
        std::cout << message << std::endl;

        f.close();
    }

}