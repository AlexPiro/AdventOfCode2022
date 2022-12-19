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
    int dist;
    Sensor(){};
    Sensor(Coord _s, Coord _b)
    {
        s = _s;
        b = _b;

        dist = getDistance(s, b);
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


bool beaconCloseToPosition(std::vector<Sensor> sensors, Coord currentPosition)
{
    bool test = false;
    for (int i = 0; i < sensors.size(); i++)
    {
        Sensor sensor = sensors[i];
        test += (getDistance(sensor.s, currentPosition) <= sensor.dist) && currentPosition != sensor.b;
    }

    return test;
    
}


int main() {

    std::fstream f;
    // f.open("input_ex.txt", std::ios::in);
    f.open("input.txt", std::ios::in);

    std::vector<Sensor> sensorsDic;

    int result = 0;

    int minX = INT_MAX;
    int maxX = INT_MIN;

    int minY = INT_MAX;
    int maxY = INT_MIN;


    if(f.is_open())
    {
        std::string line;

        while(getline(f, line))
        {
            line = line.substr(10, line.size()-10);

            replaceAll(line, " closest beacon is at ", "");
            replaceAll(line, "x=", "");
            replaceAll(line, " y=", "");

            std::cout << line << std::endl;
            
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

        // int Y=10;
        int Y = 2000000;

        for (int i = minX; i <= maxX; i++)
        {
            if(beaconCloseToPosition(sensorsDic, Coord(i, Y)))
            {
                result +=1;
            }
        }
        

        std::cout << result << std::endl;

        f.close();
    }

}