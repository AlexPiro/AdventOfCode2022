#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>

struct Pos {
    int x = 0;
    int y = 0;

    bool operator==(const Pos &other) const{
        return (x == other.x) && (y == other.y);
    }

};

struct PosHasher
{
    size_t operator()(const Pos& point) const
    {
    size_t xHash = std::hash<int>()(point.x);
    size_t yHash = std::hash<int>()(point.y) << 1;
    return xHash ^ yHash;
    }
};

struct PosComparator
{
    bool operator()(const Pos& comp, const Pos &other) const{
        return (comp.x == other.x) && (comp.y == other.y);
    }
};

std::vector<std::string> getMotion(std::string& line)
{
    std::vector<std::string> motion;
    std::istringstream iss (line);
    std::string s;
    while(getline(iss, s, ' '))
    {
        motion.push_back(s);
    }

    return motion;
}


void setTailPosition(Pos& H, Pos& T, int dir)
{

    if( abs(T.y-H.y) > 1)
    {
        if(abs(T.x-H.x) > 0)
        {
            T.x = H.x;
        }

        T.y += dir;
    }

    if( abs(T.x-H.x) > 1)
    {
        if(abs(T.y-H.y) > 0)
        {
            T.y = H.y;
        }

        T.x += dir;
    }

}


int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);


    Pos H, T;

    std::unordered_set<Pos, PosHasher, PosComparator> tailPositions;

    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {
            std::vector<std::string> motion = getMotion(line);
            char dir = motion[0][0];
            int nb = stoi(motion[1]);
            switch(dir)
            {
                case 'L':
                     for (int i = 0; i < nb; i++)
                    {
                        H.x -= 1;
                        setTailPosition(H, T, -1);
                        tailPositions.insert(T);
                    }              

                    break;
                case 'R':
              for (int i = 0; i < nb; i++)
                    {
                        H.x += 1;
                        setTailPosition(H, T, 1);
                        tailPositions.insert(T);
                    }
                    break;
                case 'U':
                for (int i = 0; i < nb; i++)
                    {
                        H.y -= 1;
                        setTailPosition(H, T, -1);
                        tailPositions.insert(T);
                    }
                    break;
                case 'D':
                   for (int i = 0; i < nb; i++)
                    {
                        H.y += 1;
                        setTailPosition(H, T, 1);
                        tailPositions.insert(T);
                    }
                    break;
            }
        }      
        
        std::cout << tailPositions.size() << std::endl;

        f.close();
    }

}