#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>


std::string* getAssignmentPair(std::string& line)
{
    std::string* assignment = new std::string[2];
    std::istringstream iss(line);
    std::string currentPair;
    int i = 0;
    while(std::getline(iss, currentPair, ','))
    {
        assignment[i] = currentPair;
        i++;
    }

    return assignment;
}

int* getSections(std::string& pair)
{
    int* sections = new int[2];
    std::istringstream iss(pair);
    std::string currentSection;
    int i = 0;
    while(std::getline(iss, currentSection, '-'))
    {
        sections[i] = std::stoi(currentSection);
        i++;
    }

    return sections;
}

int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    int overlappedAssignments = 0;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            std::string* assignment = getAssignmentPair(line);
            int* sectionsOne = getSections(assignment[0]);
            int* sectionsTwo = getSections(assignment[1]);
            if(sectionsOne[0] <= sectionsTwo[0] && sectionsOne[1] >= sectionsTwo[1])
            {
                //sectionsOne fully overlapp sectionsTwo 
                overlappedAssignments += 1;
            } 
            else if(sectionsOne[0] >= sectionsTwo[0] && sectionsOne[1] <= sectionsTwo[1])
            {
                //sectionsTwo fully overlapp sectionsOne 
                overlappedAssignments += 1;
            }
            else if((sectionsTwo[0] >= sectionsOne[0] && sectionsTwo[0] <= sectionsOne[1]) ||
                    (sectionsTwo[1] >= sectionsOne[0] && sectionsTwo[0] <= sectionsOne[1]))
            {
                //overlapp on one side
                overlappedAssignments += 1;
            }
            
        }
        
        std::cout << overlappedAssignments << std::endl;

        f.close();
    }

}