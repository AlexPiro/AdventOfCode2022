#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


std::vector<std::string> getPackets(std::string& pair)
{
    std::vector<std::string> packets;
    std::string data = "";
    int bracketOpen = 0;
    for (int i = 1; i < pair.size()-1; i++) //avoid first and last bracket
    {
        if(pair[i] == '[')
        {
            bracketOpen++;
        }
        if(pair[i] == ']')
        {
            bracketOpen--;
        }
        if(bracketOpen == 0 && pair[i] == ',')
        {
            packets.push_back(data);
            data = "";
        }
        else
        {
            data += pair[i];
        }
    }

    if(data.size() > 0)
    {
        packets.push_back(data);
    }
    

    return packets;
}

int compareLeftAndRightSides(std::vector<std::string>& left, std::vector<std::string>& right)
{
    int max = std::max(left.size(), right.size());
    for (int i = 0; i < max; i++)
    {
        if(i >= left.size())
        {
            return 1; // left out of items -> in right order
        }

        if(i >= right.size())
        {
            return -1; // right out of items -> not in right order
        }

        std::string leftVal = left[i];
        std::string rightVal = right[i];

        if(leftVal == rightVal) continue;

        if(leftVal[0] == '[' || rightVal[0] == '[')
        {
            if(leftVal[0] != '[')
            {
                std::string val = leftVal;
                leftVal = "[";
                leftVal += val;
                leftVal += "]";
            }
            if(rightVal[0] != '[' )
            {
                std::string val = rightVal;
                rightVal = "[";
                rightVal += val;
                rightVal += "]"; 
            } 

            std::vector<std::string> lChildPacket = getPackets(leftVal);
            std::vector<std::string> rChildPacket = getPackets(rightVal);
            int res = compareLeftAndRightSides(lChildPacket, rChildPacket);
            if(res == 0)
            {
                continue;
            }
            else
            {
                return res;
            }
        }
        else
        {
            return stoi(leftVal) < stoi(rightVal) ? 1 : -1;
        }
    }
    
    return 0;
}


int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    std::vector< std::vector<std::string> > listOfPairs;

    int result = 0;

    if(f.is_open())
    {
        std::string line;

        std::vector<std::string> pair;
        while(getline(f, line))
        {
            if(line != "")
            {
                pair.push_back(line);
            }
            else
            {
                listOfPairs.push_back(pair);
                pair.clear();
            }
        }

        listOfPairs.push_back(pair);

        for (int i = 0; i < listOfPairs.size(); i++)
        {
            std::vector<std::string> currentPair = listOfPairs[i];
            std::vector<std::string> leftSidePackets = getPackets(currentPair[0]);
            std::vector<std::string> rightSidePackets = getPackets(currentPair[1]);
            
            if(compareLeftAndRightSides(leftSidePackets, rightSidePackets) > 0)
            {
                result += (i+1);
            }

        }
                
        
        std::cout << result << std::endl;

        f.close();
    }

}