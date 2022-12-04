#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>


std::vector<std::string> getAssignmentPair(std::string& line)
{
    std::vector<std::string> assignment;
    std::istringstream iss(line);
    std::string currentPair;

    while(std::getline(iss, currentPair, ','))
    {
        assignment.push_back(currentPair);
    }

    return assignment;
}

std::vector<int> getSections(std::string& pair)
{
    std::vector<int> sections;
    std::istringstream iss(pair);
    std::string currentSection;

    while(std::getline(iss, currentSection, '-'))
    {
        sections.push_back(std::stoi(currentSection));
    }

    return sections;
}

int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    int fullyContainedAssignments = 0;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            std::vector<std::string> assignment = getAssignmentPair(line);
            std::vector<int> sectionsOne = getSections(assignment[0]);
            std::vector<int> sectionsTwo = getSections(assignment[1]);
            if(sectionsOne[0] <= sectionsTwo[0] &&
                sectionsOne[1] >= sectionsTwo[1])
            {
                //sectionsOne overlapp sectionsTwo 
                fullyContainedAssignments += 1;
            } else if (sectionsOne[0] >= sectionsTwo[0] &&
                sectionsOne[1] <= sectionsTwo[1])
            {
                //sectionsTwo overlapp sectionsOne 
                fullyContainedAssignments += 1;
            }
            
        }
        
        std::cout << fullyContainedAssignments << std::endl;

        f.close();
    }

}