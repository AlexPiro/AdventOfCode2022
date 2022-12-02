#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <algorithm>
// #include <type_traits>
#include <sstream>

int main() {

    std::fstream f;
    f.open("input_ex.txt", std::ios::in);

    uint32_t currentScore = 0;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            std::istringstream iss(line);
            std::string currentShape;
            std::string opponentShape = "";
            while(getline(iss, currentShape, ' '))
            {
                if(opponentShape == "")
                {
                    opponentShape = currentShape;
                    continue;
                }

                if(opponentShape == "A") //rock
                {
                    if(currentShape == "X") // loose
                    {
                        currentScore += 3; //scissors
                        currentScore += 0; 

                    }
                    else if(currentShape == "Y") // draw
                    {
                        currentScore += 1; //rock
                        currentScore += 3;
                    }
                    else if(currentShape == "Z") //win
                    {
                        currentScore += 2; //paper
                        currentScore += 6;
                    }
                    else {
                        std::cout << "Error while parsing the inputs" << std::endl;
                    }
                }
                else if(opponentShape == "B") //paper
                {
                    if(currentShape == "X") // loose
                    {
                        currentScore += 1; //rock
                        currentScore += 0; 

                    }
                    else if(currentShape == "Y") // draw
                    {
                        currentScore += 2; //paper
                        currentScore += 3;
                    }
                    else if(currentShape == "Z") //win
                    {
                        currentScore += 3; //scissors
                        currentScore += 6;
                    }
                    else {
                        std::cout << "Error while parsing the inputs" << std::endl;
                    }
                }
                else if(opponentShape == "C") //scissors
                {
                    if(currentShape == "X") // loose
                    {
                        currentScore += 2; //paper
                        currentScore += 0; 

                    }
                    else if(currentShape == "Y") // draw
                    {
                        currentScore += 3; //scissors
                        currentScore += 3;
                    }
                    else if(currentShape == "Z") //win
                    {
                        currentScore += 1; //rock
                        currentScore += 6;
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