#include <iostream>
#include <fstream>
#include <string>
#include <vector>


bool isTreeOnEdge(std::vector<std::string>& grid, int& row, int& col)
{
    return row == 0 || row == grid.size()-1 || col == 0 || col == grid[0].size()-1;
}


bool SearchHorizontal(std::vector<std::string>& grid, int& row, int& col, int direction)
{
    int searchIndexCol = col + (direction);
    
    while(grid[row][col] > grid[row][searchIndexCol])
    {
        searchIndexCol += (direction);

        if(searchIndexCol < 0 || searchIndexCol > grid[0].size()-1)
        {
            return true;
        }
    }

    return false;
}
bool SearchVertical(std::vector<std::string>& grid, int& row, int& col, int direction)
{
    int searchIndexRow = row + (direction);
    
    while(grid[row][col] > grid[searchIndexRow][col])
    {
        searchIndexRow += (direction);

        if(searchIndexRow < 0 || searchIndexRow > grid.size()-1)
        {
            return true;
        }
    }

    return false;
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
                if(isTreeOnEdge(grid, i, j))
                {
                    result += 1;
                }
                else
                {
                    if(SearchHorizontal(grid, i, j, -1) || 
                        SearchHorizontal(grid, i, j, 1) ||
                        SearchVertical(grid, i, j, -1) ||
                        SearchVertical(grid, i, j, 1))
                    {
                        result += 1;
                    }
                }
            }
            
        }
        
        std::cout << result << std::endl;

        f.close();
    }

}