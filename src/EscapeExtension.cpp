#include "EscapeExtension.h"
#include <queue>
#include <iostream>
#include <queue>
#include <iostream>

EscapeExtension::EscapeExtension(mcpp::Coordinate basePoint){
    this->basePoint = basePoint;
    this->count = 0;
    std::srand(time(0));
}

EscapeExtension::~EscapeExtension()
{
}

//function to do the pathLogic, if no path found indicate that
void EscapeExtension::pathBool(int coordX, int coordZ){
    if (!pathLogic(coordX, coordZ)){
        std::cout << "Path not found." << std::endl;
    }

    count = 0;

}

//the pathLogic function
bool EscapeExtension::pathLogic(int beginX, int beginZ){
    std::queue<mcpp::Coordinate> coordQueue;
    coordQueue.push(mcpp::Coordinate(beginX, basePoint.y, beginZ));

    // this->count++;
    int xCoordArray[4] = {1, -1, 0, 0};
    int zCoordArray[4] = {0, 0, 1, -1};
    bool isFound = false;

    while(!coordQueue.empty() && (isFound == false)){
        //get next coord
        mcpp::Coordinate currentCoord = coordQueue.front();
        //remove the coord from the queue
        coordQueue.pop();

        int currentX = currentCoord.x;
        int currentZ = currentCoord.z; 

        //check on the current block
        checkingLocation = mcpp::Coordinate (currentX, basePoint.y, currentZ);
        checkingBlock = mc.getBlock(checkingLocation);

        //exit indicator
        if (checkingBlock == mcpp::Blocks::BLUE_CARPET){
            isFound = true;
        }
        else{
            mc.setBlock(checkingLocation, mcpp::Blocks::LIME_CARPET);

            //check the next blocks around
            for (int i = 0; i < 4; i++){
                int newX = currentX + xCoordArray[i];
                int newZ = currentZ + zCoordArray[i];

                checkingBlock = mc.getBlock(mcpp::Coordinate(newX, basePoint.y, newZ));

                if(checkingBlock != mcpp::Blocks::ACACIA_WOOD_PLANK && checkingBlock != mcpp::Blocks::LIME_CARPET){
                    coordQueue.push(mcpp::Coordinate(newX, basePoint.y, newZ));
                }
            }
        }

    }

    if(isFound == true){
        std::cout << "Exit has been found!" << std::endl;
    }

   return isFound;
}