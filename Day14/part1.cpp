#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct Coord {
    int x = 0;
    int y = 0;

    Coord(){};
    Coord(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

std::vector<std::string> splitLine(std::string& line)
{
    std::vector<std::string> instruction;
    std::istringstream iss (line);
    std::string s;
    while(getline(iss, s, ';'))
    {
        instruction.push_back(s);
    }

    return instruction;
}

Coord getCoords(std::string& path)
{
    Coord coords;
    std::istringstream iss (path);
    std::string s;
    int index=0;
    while(getline(iss, s, ','))
    {
        if(index == 0)
        {
            coords.x = stoi(s);
            index++;
        }
        else
        {
            coords.y = stoi(s);
            index = 0;
        }
    }

    return coords;
}

bool findInGrid(std::vector<std::string>& grid, Coord coords)
{
    return grid[coords.y][coords.x] != '.';
}

bool fallAndRoll(std::vector<std::string>& grid, Coord& sandPos)
{
    if(findInGrid(grid, sandPos))
    {
        return false;
    }

    if(!findInGrid(grid, Coord(sandPos.x, sandPos.y+1)))
    {
        sandPos.y += 1;

        return true;
    }
    else
    {
        if(!findInGrid(grid, Coord(sandPos.x-1, sandPos.y+1)))
        {
            sandPos.x -= 1;
            sandPos.y += 1;
            return true;
        }
        else if(!findInGrid(grid, Coord(sandPos.x+1, sandPos.y+1)))
        {
            sandPos.x += 1;
            sandPos.y += 1;
            return true;
        }

        return false;

    }

}


int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    std::vector< std::vector<Coord> > rockPaths;

    std::vector<std::string> grid;

    int maxY = INT_MIN;
    // only to display grid and center results
    // int minX = INT_MAX;
    // int maxX = INT_MIN;

    int result = 0;

    if(f.is_open())
    {
        std::string line;

        while(getline(f, line))
        {
            replaceAll(line, " -> ", ";");
            std::vector<std::string> pathList = splitLine(line);
            std::vector<Coord> rockPath;

            for (int i = 0; i < pathList.size(); i++)
            {
                Coord pathCoords = getCoords(pathList[i]);
                maxY = std::max(maxY, pathCoords.y);
                rockPath.push_back(pathCoords);
            }

            rockPaths.push_back(rockPath);
            
        }

        //create the grid
        for (int i = 0; i < maxY+1; i++)
        {
            grid.push_back(std::string(1000, '.'));
        }    


        for (int i = 0; i < rockPaths.size(); i++)
        {
            std::vector<Coord> rockPath = rockPaths[i];
            for (int j = 0; j < rockPath.size()-1; j++)
            {
                Coord start = rockPath[j];
                Coord end = rockPath[j+1];

                if(start.x == end.x) // move vertically
                {
                    for (int k = std::min(start.y, end.y); k <= std::max(start.y, end.y); k++)
                    {
                        grid[k][start.x] = '#';
                    }
                }
                if(start.y == end.y) // move horizontally
                {
                    for (int k = std::min(start.x, end.x); k <= std::max(start.x, end.x); k++)
                    {
                        grid[start.y][k] = '#';
                    }
                }
            }
        }

        bool sandFallingOver = false;
        int i = 0;
        while(!sandFallingOver)
        {
            Coord sandPos (500, 0);

            while(fallAndRoll(grid, sandPos))
            {
                continue;
            }

            //only to display the grid
            // minX = std::min(minX, sandPos.x);
            // maxX = std::max(maxX, sandPos.x);

            grid[sandPos.y][sandPos.x] = 'o';
            
            if(sandPos.y >= maxY)
            {
                result = i;
                sandFallingOver= true;
                break;
            } 
            
  
            i++;

        }

        // display grid 
        // for (int i = 0; i < grid.size(); i++)
        // {
        //     std::cout << grid[i].substr(minX-1, (maxX-minX)+2) << std::endl;
        // }
               
        std::cout << result << std::endl;

        f.close();
    }

}