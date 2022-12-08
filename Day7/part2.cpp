#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <utility>
#include <numeric>

struct Folder {
    std::string name;
    int size;
    Folder* parent;
    std::vector<Folder> childs;
};

std::vector<std::string> parseLine(std::string& line)
{
    std::vector<std::string> parsedString;
    std::istringstream iss(line);
    std::string commandPart;
    while(std::getline(iss, commandPart, ' '))
    {
        parsedString.push_back(commandPart);
    }

    return parsedString;
}


void PropagateSizeInHierarchy(Folder* currentDir, int sizeToAdd)
{
    currentDir->size += sizeToAdd;

    Folder* ptr = currentDir;
    while(ptr->name != "/")
    {
        ptr = ptr->parent;
        ptr->size += sizeToAdd;
    }
}

void sumSmallDirectories(std::vector<Folder>& root, const int& maxFileSize, int& result)
{
    for (int i = 0; i < root.size(); i++)   
    {
        if(root[i].size <= maxFileSize)
        {
            result += root[i].size;
        }
        
        if(root[i].childs.size() > 0)
        {
            sumSmallDirectories(root[i].childs, maxFileSize, result);
        }
    }

}



void findAllDirCandidates(std::vector<Folder>& root, int& spaceToFree, std::vector<int>& candidates)
{
    for (int i = 0; i < root.size(); i++)   
    {
        if(root[i].size >= spaceToFree)
        {
            candidates.push_back(root[i].size);
        }
        
        if(root[i].childs.size() > 0)
        {
            findAllDirCandidates(root[i].childs, spaceToFree, candidates);
        }
    }

}



Folder* getChild(Folder* currentFolder, std::string& childName)
{
    for (int i = 0; i < currentFolder->childs.size(); i++)
    {
        Folder* element = &currentFolder->childs[i];

        if(element->name == childName)
        {
            return element;
        }
    }

    return nullptr;
    
}

int main() {

    std::fstream f;
    f.open("input.txt", std::ios::in);

    const int DISK_SPACE = 70000000;
    const int UPDATE_SPACE = 30000000;

    std::vector<Folder> dirStructure;
    Folder* currentDir;

    Folder rootFolder;
    rootFolder.name = "/";
    rootFolder.size = 0;
    rootFolder.parent = nullptr;
    dirStructure.push_back(rootFolder);
    
    if(f.is_open())
    {
        std::string line;
        while(getline(f, line))
        {

            std::vector<std::string> pString = parseLine(line);
            if(pString[0] == "$") // this is a command
            {
                if(pString[1] == "cd")
                {
                    if(pString[2] == "..")
                    {
                        currentDir = currentDir->parent;
                    }
                    else
                    {

                        if(pString[2] == "/")
                        {
                            currentDir = &dirStructure[0];
                        }
                        else
                        {
                            currentDir = getChild(currentDir, pString[2]);
                        }
                         

                    }
                } 
            }
            else if(pString[0] == "dir")
            {
                Folder newFolder;
                newFolder.name = pString[1];
                newFolder.size = 0;
                newFolder.parent = currentDir;

                currentDir->childs.push_back(newFolder);

            }
            else
            {
                int fileSize = stoi(pString[0]);
                PropagateSizeInHierarchy(currentDir, fileSize);

            }
            
        }

        int unusedSpace = DISK_SPACE - dirStructure[0].size;
        int spaceToFree = UPDATE_SPACE - unusedSpace;

        std::vector<int> listOfCandidateFolders;
        findAllDirCandidates(dirStructure, spaceToFree, listOfCandidateFolders);

        auto minValue = std::min_element(listOfCandidateFolders.begin(), listOfCandidateFolders.end());

        std::cout << *minValue << std::endl;       


        f.close();
    }

}