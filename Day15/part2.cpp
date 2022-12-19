#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>


struct Coord {
    int x = 0;
    int y = 0;

    Coord(){};
    Coord(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    inline bool operator !=(const Coord &b)
    {
        return x != b.x || y != b.y;
    }

    inline bool operator ==(const Coord &b)
    {
        return x == b.x && y == b.y;
    }
};

int getDistance(Coord a, Coord b)
{
    return std::abs(b.x-a.x) + std::abs(b.y-a.y);
}

struct Sensor {
    Coord s;
    Coord b;
    int dist = 0;
    Sensor(){};
    Sensor(Coord _s, Coord _b)
    {
        s = _s;
        b = _b;

        dist = getDistance(s, b);
    }
};

struct Range {
    int min = 0;
    int max = 0;

    Range(){};
    Range(int _min, int _max)
    {
        min = _min;
        max = _max;
    }
};

bool compareRanges(const Range& a, const Range& b)
{
    return a.min < b.min;
}

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

std::vector<std::string> splitLine(std::string& line, char delimiter)
{
    std::vector<std::string> parts;
    std::istringstream iss (line);
    std::string s;
    while(getline(iss, s, delimiter))
    {
        parts.push_back(s);
    }

    return parts;
}

bool includeInRange(Range& range, int x)
{
    return x >= range.min && x <= range.max;
}


bool isRangesOverlapping(Range& a, Range& b)
{
    return (b.min >= a.min && b.min<= a.max) || (b.max >= a.min && b.max <= a.max) ||
            (a.min >= b.min && a.min<= b.max) || (a.max >= b.min && a.max <= b.max);
}


int main() {

    std::fstream f;
    // f.open("input_ex.txt", std::ios::in);
    f.open("input.txt", std::ios::in);

    std::vector<Sensor> sensorsDic;

    std::vector<std::vector<Range>> grid;

    int minX = INT_MAX;
    int maxX = INT_MIN;

    int minY = INT_MAX;
    int maxY = INT_MIN;

    unsigned long result = 0;


    if(f.is_open())
    {
        std::string line;

        while(getline(f, line))
        {
            line = line.substr(10, line.size()-10);

            replaceAll(line, " closest beacon is at ", "");
            replaceAll(line, "x=", "");
            replaceAll(line, " y=", "");
            
            std::vector<std::string> pairs = splitLine(line, ':');
            std::vector<std::string> sensorCoords = splitLine(pairs[0], ',');
            std::vector<std::string> beaconCoords = splitLine(pairs[1], ',');
            Coord sensor(stoi(sensorCoords[0]), stoi(sensorCoords[1]));
            Coord beacon(stoi(beaconCoords[0]), stoi(beaconCoords[1]));

            minX = std::min(minX, beacon.x);
            maxX = std::max(maxX, beacon.x);

            minY = std::min(minY, beacon.y);
            maxY = std::max(maxY, beacon.y);

            minY = std::min(minY, sensor.y);
            maxY = std::max(maxY, sensor.y);

            Sensor sensorObj(sensor, beacon);

            minX = std::min(minX, sensorObj.s.x - sensorObj.dist);
            maxX = std::max(maxX, sensorObj.s.x + sensorObj.dist);

            sensorsDic.push_back(sensorObj);
        }

        grid.resize(maxY);

        for (int i = 0; i < grid.size(); i++)
        {
            std::vector<Range> range;
            grid[i] = range;
        }
        
        //merge ranges if the row is full we should have only one range
        for (int i = 0; i < sensorsDic.size(); i++)
        {
            Sensor sensor = sensorsDic[i];
            int x = sensor.dist;
            int y = 0;
            while(x >=0)
            {
                int minStrength = sensor.s.x - x;
                int maxStrength = sensor.s.x + x;
                int iD = sensor.s.y + y;
                if(iD < grid.size())
                {
                    grid[iD].push_back(Range(minStrength, maxStrength));
                }
             
                if(y > 0)
                {
                    int iU = sensor.s.y - y;
                    if(iU >= 0)
                    {
                        grid[iU].push_back(Range(minStrength, maxStrength));
                    }
      
                }

                y++;
                x--;
            }
        }

        int min = 0;
        // int max = 20;
        int max = 4000000;


        for (int i = 0; i < grid.size(); i++)
        {
            std::sort(grid[i].begin(), grid[i].end(), compareRanges);
            
            std::vector<Range> optimizedRanges;
            Range r = grid[i][0];
            for (int j = 1; j < grid[i].size(); j++)
            {
                if(isRangesOverlapping(r, grid[i][j]))
                {
                    r.min = std::min(r.min, grid[i][j].min);
                    r.max = std::max(r.max, grid[i][j].max);

                }
                else
                {
                    optimizedRanges.push_back(r);
                    r = grid[i][j];
                }

            }
            optimizedRanges.push_back(r);

            grid[i] = optimizedRanges;

            for (int k = 0; k < optimizedRanges.size() - 1; k++)
            {
                if(optimizedRanges[k+1].min-optimizedRanges[k].max > 1)
                {
                    unsigned long x = optimizedRanges[k].max+1;


                    unsigned long y = i;


                    if(x >= min && x <= max && y>=min && y <=max)
                    {
                        result = x * 4000000 + y;
                        break;
                    }

                }
            }

            if(result > 0) break;
            
        }
        

        std::cout << result << std::endl;

        f.close();
    }

}