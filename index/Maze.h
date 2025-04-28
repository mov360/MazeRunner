#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <vector>
#include <mcpp/mcpp.h>

#include "Node.h"

class Maze
{

public:
    Maze(mcpp::Coordinate basePoint, unsigned int xlen, unsigned int zlen, bool mode);
    ~Maze();
    void teleportToBasePoint();
    void flattenMazeArea(unsigned int xlen, unsigned int zlen);
    void buildMaze(char** maze, unsigned int xlen, unsigned int zlen);
    void cleanUp();
    void playerBasePoint();
    bool validMaze(char** structure);
    void setBasePoint(mcpp::Coordinate basePoint);
    void resetMaze(mcpp::Coordinate basePoint, unsigned int xlen, unsigned int zlen);
    bool checkLinkedListEmpty();
    char** deleteMaze(char** maze, unsigned int x);
    void cleanUpBuilding();
    void cleanUpFlatten();

private:
    mcpp::MinecraftConnection mc;
    void addChangedBlock(mcpp::Coordinate pos, int type);
    void addChangedBlockBuilding(mcpp::Coordinate pos, int type);
    void clearLinkedList();

    /* data */
    mcpp::Coordinate basePoint; 
    unsigned int xlen;
    unsigned int zlen;
    bool mode;
    Node* firstNode;
    Node* endNode;
    Node* firstNodeBuilding;
    Node* endNodeBuilding;
    
};




#endif //ASSIGN_MAZE_H
