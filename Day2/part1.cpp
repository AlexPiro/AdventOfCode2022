#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <algorithm>
// #include <type_traits>
#include <sstream>

int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    uint32_t currentScore = 0;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            std::istringstream iss(line);
            std::string currentShape;
            std::string opponentShape = "";
            while(std::getline(iss, currentShape, ' '))
            {
                if(opponentShape == "")
                {
                    opponentShape = currentShape;
                    continue;
                }

                if(opponentShape == "A") //rock
                {
                    if(currentShape == "X")
                    {
                        currentScore += 1; //rock
                        currentScore += 3; //draw

                    }
                    else if(currentShape == "Y")
                    {
                        currentScore += 2; //paper
                        currentScore += 6; //won
                    }
                    else if(currentShape == "Z")
                    {
                        currentScore += 3; //scissors
                        currentScore += 0; //lost
                    }
                    else {
                        std::cout << "Error while parsing the inputs" << std::endl;
                    }
                }
                else if(opponentShape == "B") //paper
                {
                    if(currentShape == "X")
                    {
                        currentScore += 1; //rock
                        currentScore += 0; //lost

                    }
                    else if(currentShape == "Y")
                    {
                        currentScore += 2; //paper
                        currentScore += 3; //draw
                    }
                    else if(currentShape == "Z")
                    {
                        currentScore += 3; //scissors
                        currentScore += 6; //won
                    }
                    else {
                        std::cout << "Error while parsing the inputs" << std::endl;
                    }
                }
                else if(opponentShape == "C") //scissors
                {
                    if(currentShape == "X")
                    {
                        currentScore += 1; //rock
                        currentScore += 6; //won

                    }
                    else if(currentShape == "Y")
                    {
                        currentScore += 2; //paper
                        currentScore += 0; //lost
                    }
                    else if(currentShape == "Z")
                    {
                        currentScore += 3; //scissors
                        currentScore += 3; //draw
                    }
                    else {
                        std::cout << "Error while parsing the inputs" << std::endl;
                    }
                }
                else {
                    std::cout << "Error while parsing the inputs" << std::endl;
                }

            }
        }

        std::cout << currentScore << std::endl;

        f.close();
    }

}