#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H

#include <iostream>
#include <mcpp/mcpp.h>
#include <string>

#define MOVE_XPLUS mcpp::Coordinate(1,0,0)
#define MOVE_XMINUS mcpp::Coordinate(-1,0,0)
#define MOVE_ZPLUS mcpp::Coordinate(0,0,1)
#define MOVE_ZMINUS mcpp::Coordinate(0,0,-1)

enum solveAlgorithm{
        RIGHT_HAND_FOLLOW,
        BREATH_FIRST_SEARCH,
};

enum AgentOrientation{
    X_PLUS,
    Z_PLUS,
    X_MINUS,
    Z_MINUS
};

class Agent
{

public:
    //Agent(mcpp::Coordinate startLoc);
    Agent(bool mode, mcpp::Coordinate basePoint, int xlen, int zlen);
    ~Agent();
    void resetAgent(mcpp::Coordinate basePoint, int xlen, int zlen);
    void placeRandomly(char** maze);

    mcpp::Coordinate goSouth(int xCoord, int zCoord);
    mcpp::Coordinate goWest(int xCoord, int zCoord);
    mcpp::Coordinate goNorth(int xCoord, int zCoord);
    mcpp::Coordinate goEast(int xCoord, int zCoord);
    bool initialise();
    void turnRight();
    void blockedPathAndNoRightWall();
    void walk();
    
private:
    /* data */
    mcpp::MinecraftConnection mc;
    bool mode;
    mcpp::Coordinate basePoint;
    int xlen = 0;
    int zlen = 0;
    //the location where the agent is randomly placed
    mcpp::Coordinate generatedLocation;
    mcpp::Coordinate currentLocation;
    std::string positionOfRightWall;
    mcpp::Coordinate coordRightWall;
    mcpp::BlockType rightBlock;
    mcpp::BlockType frontBlock;
    int currentX = 0;
    int currentZ = 0;
};



#endif //ASSIGN3_AGENT_H