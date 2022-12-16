#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>

struct Pos {
    int x = 0;
    int y = 0;

    inline bool operator==(const Pos& b)
    {
        return x == b.x && y == b.y;
    }
};

struct Node {
    Pos coord;
    int step = 0;
};

void parseStartAndEnd(std::vector<std::string>& grid, Pos& start, Pos& end)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            char currentChar = grid[i][j];
            if(currentChar == 'S')
            {
                start.x = j;
                start.y = i;

                grid[i][j] = 'a';
            }

            if (currentChar == 'E')
            {
                end.x = j;
                end.y = i;

                grid[i][j] = 'z';
            }
        }
        
    }

}

std::vector<Pos> getPossibleMove(std::vector<std::string>& grid, Pos& currentPos)
{
    std::vector<Pos> possibleMoves;

    if (currentPos.x > 0) //go left
    {
        Pos p;
        p.x = currentPos.x - 1;
        p.y = currentPos.y;

        int currentHeight = grid[currentPos.y][currentPos.x];
        int height = grid[p.y][p.x];
        if (height <= currentHeight || height == currentHeight + 1)
        {
            possibleMoves.push_back(p);
        }
    }
    if (currentPos.x < grid[0].size()-1) //go right
    {
        Pos p;
        p.x = currentPos.x + 1;
        p.y = currentPos.y;

        int currentHeight = grid[currentPos.y][currentPos.x];
        int height = grid[p.y][p.x];
        if (height <= currentHeight || height == currentHeight + 1)
        {
            possibleMoves.push_back(p);
        }
    }

    if (currentPos.y > 0) //go up
    {
        Pos p;
        p.x = currentPos.x;
        p.y = currentPos.y-1;

        int currentHeight = grid[currentPos.y][currentPos.x];
        int height = grid[p.y][p.x];
        if (height <= currentHeight || height == currentHeight + 1)
        {
            possibleMoves.push_back(p);
        }
    }
    if (currentPos.y < grid.size() - 1) //go down
    {
        Pos p;
        p.x = currentPos.x;
        p.y = currentPos.y + 1;

        int currentHeight = grid[currentPos.y][currentPos.x];
        int height = grid[p.y][p.x];
        if (height <= currentHeight || height == currentHeight + 1)
        {
            possibleMoves.push_back(p);
        }
    }

    return possibleMoves;
}

int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    std::vector<std::string> heightmap;
    std::vector<std::string> visited;

    std::queue<Node> nodes;

    int fewestStep = 0;
    int currentElevation;

    Pos start, end;

    if(f.is_open())
    {
        std::string line;

        while(getline(f, line))
        {
            heightmap.push_back(line);
            visited.push_back(std::string(line.size(), '.'));
        }

        parseStartAndEnd(heightmap, start, end);

        Node startNode;
        startNode.coord = start;

        nodes.push(startNode);

        while (nodes.size() > 0)
        {
            Node currentNode = nodes.front();

            std::cout << "Current node height " << heightmap[currentNode.coord.y][currentNode.coord.x] << std::endl;
            nodes.pop(); // remove the element we are dealing with

            if (currentNode.coord == end)
            {
                fewestStep = currentNode.step;
                break;
            }
            std::vector<Pos> moves = getPossibleMove(heightmap, currentNode.coord);

            for (int i = 0; i < moves.size(); i++)
            {
                Pos movePos = moves[i];
                if (visited[movePos.y][movePos.x] == '.')
                {
                    visited[movePos.y][movePos.x] = '#';
                    Node n;
                    n.coord = movePos;
                    n.step = currentNode.step + 1;

                    nodes.push(n);
                }
            }
        }

        
        std::cout << fewestStep << std::endl;

        f.close();
    }

}