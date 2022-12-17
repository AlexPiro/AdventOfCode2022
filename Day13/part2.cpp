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

bool comparePackets(std::string& left, std::string& right)
{
    std::vector<std::string> leftPacket = getPackets(left);
    std::vector<std::string> rightPacket = getPackets(right);
    return compareLeftAndRightSides(leftPacket, rightPacket) > 0;
}


int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    std::vector<std::string> listOfPackets;

    int result = 1;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            if(line != "")
            {
                listOfPackets.push_back(line);
            }
        }

        listOfPackets.push_back("[[2]]");
        listOfPackets.push_back("[[6]]");

        std::sort(listOfPackets.begin(), listOfPackets.end(), comparePackets);

        for (int i = 0; i < listOfPackets.size(); i++)
        {
            if(listOfPackets[i] == "[[2]]" ||
                listOfPackets[i] == "[[6]]")
            {
                result *= (i+1);
            }
        }
              
        std::cout << result << std::endl;

        f.close();
    }

}