#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct Monkey {
    std::vector<int> items;
    std::string operation;
    int value;
    int test;
    int ifTrue;
    int ifFalse;
    int inspectedItems = 0;
};


std::vector<std::string> splitLine(std::string& line, char delimiter)
{
    std::vector<std::string> splittedLine;
    std::istringstream iss (line);
    std::string s;
    while(getline(iss, s, delimiter))
    {
        if(s != "")
        {
            splittedLine.push_back(s);
        }
    }

    return splittedLine;
}

bool compareByInspectedElements(const Monkey &a, const Monkey &b)
{
    return a.inspectedItems > b.inspectedItems;
}


int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    int monkeyBusiness = 0;

    int worryLevel = 0;

    int worryLevelDiviser = 1;
    const int MAX_ROUND = 20;
    int round = 1;

    std::vector<Monkey> monkeys;

    if(f.is_open())
    {
        std::string line;
        int currentMonkeyIndex = -1;
        while(getline(f, line))
        {
            if(line != "")
            {
                std::vector<std::string> splitColon = splitLine(line, ':');
                std::vector<std::string> leftPart = splitLine(splitColon[0], ' ');
                if(leftPart[0] == "Monkey")
                {
                    Monkey m;
                    monkeys.push_back(m);
                    currentMonkeyIndex = stoi(leftPart[1]);
                }
                
                if(leftPart[0] == "Starting")
                {
                    std::vector<std::string> rightPart = splitLine(splitColon[1], ',');
                    for (int i = 0; i < rightPart.size(); i++)
                    {
                        monkeys[currentMonkeyIndex].items.push_back(stoi(rightPart[i]));
                    }
                }
                
                if(leftPart[0] == "Operation")
                {
                    std::vector<std::string> rightPart = splitLine(splitColon[1], ' ');

                    monkeys[currentMonkeyIndex].operation = rightPart[3];

                    int value = -1;
                    if(rightPart[4] != "old")
                    {
                        value = std::stoi(rightPart[4]); 
                    }

                    monkeys[currentMonkeyIndex].value = value;
                }

                if(leftPart[0] == "Test")
                {
                    std::vector<std::string> rightPart = splitLine(splitColon[1], ' ');

                    monkeys[currentMonkeyIndex].test = stoi(rightPart[2]);
                }

                if(leftPart[0] == "If")
                {
                    std::vector<std::string> rightPart = splitLine(splitColon[1], ' ');
                    if(leftPart[1] == "true")
                    {
                        monkeys[currentMonkeyIndex].ifTrue = stoi(rightPart[3]);
                    }

                    if(leftPart[1] == "false")
                    {
                        monkeys[currentMonkeyIndex].ifFalse = stoi(rightPart[3]);
                    }

                }
            }
      
        }

        while(round <= MAX_ROUND)
        {
            for (int i = 0; i < monkeys.size(); i++)
            {
                Monkey* m = &monkeys[i];
                while(m->items.size() > 0)
                {
                    int itemWorryLevel = m->items[0];
                    int worryFactor = m->value != -1 ? m->value : itemWorryLevel; 
                    if(m->operation == "*")
                    {
                        itemWorryLevel *= worryFactor;
                    }
                    if(m->operation == "+")
                    {
                        itemWorryLevel += worryFactor;
                    }

                    itemWorryLevel /= worryLevelDiviser;

                    if(itemWorryLevel % m->test == 0)
                    {
                        monkeys[m->ifTrue].items.push_back(itemWorryLevel);
                    }
                    else
                    {
                        monkeys[m->ifFalse].items.push_back(itemWorryLevel);
                    }

                    m->inspectedItems ++;

                    m->items.erase(m->items.begin());
                }
                
            }
            
            round ++;
        }

        std::sort(monkeys.begin(), monkeys.end(), compareByInspectedElements);

        monkeyBusiness = monkeys[0].inspectedItems * monkeys[1].inspectedItems;
        
        std::cout << monkeyBusiness << std::endl;

        f.close();
    }

}