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


struct Node {
    Pos pos;
    struct Node *next = nullptr;
};

const int GRID_SIZE = 2000;

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

Pos getTailPosition(Node* head)
{
    
    Node* currentNode = head;
    while(currentNode->next != nullptr)
    {
        Node* nextNode = currentNode->next;

        if(currentNode->pos.y - nextNode->pos.y == 2)
        {
            if(currentNode->pos.x < nextNode->pos.x)
            {
                nextNode->pos.x -= 1;
            }
            if(currentNode->pos.x > nextNode->pos.x)
            {
                nextNode->pos.x += 1;
            }
            nextNode->pos.y = currentNode->pos.y - 1;
        }

        if(nextNode->pos.y - currentNode->pos.y == 2)
        {
            if(currentNode->pos.x < nextNode->pos.x)
            {
                nextNode->pos.x -= 1;
            }
            if(currentNode->pos.x > nextNode->pos.x)
            {
                nextNode->pos.x += 1;
            }
            nextNode->pos.y = currentNode->pos.y + 1;
        }

        if(nextNode->pos.x - currentNode->pos.x == 2)
        {
            if(currentNode->pos.y < nextNode->pos.y)
            {
                nextNode->pos.y -= 1;
            }
            if(currentNode->pos.y > nextNode->pos.y)
            {
                nextNode->pos.y += 1;
            }
            nextNode->pos.x = currentNode->pos.x + 1;
        }

        if(currentNode->pos.x - nextNode->pos.x == 2)
        {
            if(currentNode->pos.y < nextNode->pos.y)
            {
                nextNode->pos.y -= 1;
            }
            if(currentNode->pos.y > nextNode->pos.y)
            {
                nextNode->pos.y += 1;
            }
            nextNode->pos.x = currentNode->pos.x - 1;
        }

        currentNode = nextNode;
    
    }

    return currentNode->pos;

}


int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    //init the rope
    Node* head = new Node();
    Node* currentNode = head;
    for (int i = 0; i < 9; i++)
    {
        Node* nextNode = new Node();
        currentNode->pos = Pos();
        currentNode->next = nextNode;

        currentNode = nextNode;
    }
    

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
                        head->pos.x -= 1;
                        tailPositions.insert(getTailPosition(head));
                    }
                    break;
                case 'R':
                    for (int i = 0; i < nb; i++)
                    {
                        head->pos.x += 1;
                        tailPositions.insert(getTailPosition(head));
                    }
                    break;
                case 'U':
                    for (int i = 0; i < nb; i++)
                    {
                        head->pos.y -= 1;
                        tailPositions.insert(getTailPosition(head));
                    }
                    break;
                case 'D':
                    for (int i = 0; i < nb; i++)
                    {
                        head->pos.y += 1;
                        tailPositions.insert(getTailPosition(head));
                    }
                    break;
            }
        }

        

        std::cout << tailPositions.size() << std::endl;

        f.close();
    }

}
