#include <iostream>
#include <fstream>
#include <string>
#include <vector>


bool isTreeOnEdge(std::vector<std::string>& grid, int& row, int& col)
{
    return row == 0 || row == grid.size()-1 || col == 0 || col == grid[0].size()-1;
}


int GetHorizontalScore(std::vector<std::string>& grid, int& row, int& col, int direction)
{
    int score = 1;
    int searchCol = searchCol = col + direction;
    
    while(grid[row][searchCol] < grid[row][col])
    {
        if(searchCol <= 0 || searchCol >= grid[0].size()-1)
        {
            return score;
        }

        searchCol += direction;
        score += 1;

    }

    return score;
}

int GetVerticalScore(std::vector<std::string>& grid, int& row, int& col, int direction)
{
    int score = 1;
    int searchRow = row + direction;

    while(grid[searchRow][col] < grid[row][col])
    {
        if(searchRow <= 0 || searchRow >= grid.size()-1)
        {
            return score;
        }
        searchRow += direction;
        score += 1;

    }

    return score;
}

int CalculateTreeScenicScore(std::vector<std::string> grid, int& row, int& col)
{
    int score = 1;
    score *= GetHorizontalScore(grid, row, col, -1);
    score *= GetHorizontalScore(grid, row, col, 1);
    score *= GetVerticalScore(grid, row, col, -1);
    score *= GetVerticalScore(grid, row, col, 1);

    return score;
}

int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    std::vector<std::string> grid;

    int result = 0;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            grid.push_back(line);
        }

        for (int i = 0; i < grid.size(); i++)
        {   
            std::string row = grid[i];
            for (int j = 0; j < row.size(); j++)
            {
                if(!isTreeOnEdge(grid, i, j))
                {
                    int foundScore = CalculateTreeScenicScore(grid, i, j);
                    result = std::max(foundScore, result);
                }
            }
            
        }
        
        std::cout << result << std::endl;

        f.close();
    }

}