#include "Agent.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>

// Agent::Agent(mcpp::Coordinate startLoc)
// {
// }

Agent::Agent(bool mode, mcpp::Coordinate basePoint, int xlen, int zlen){
    this->mode = mode;

    std::srand(time(0));
}

Agent::~Agent()
{
}

void Agent::resetAgent(mcpp::Coordinate basePoint, int xlen, int zlen){
    this->basePoint = basePoint;
    this->xlen = xlen;
    this->zlen = zlen;
    this->currentX = 0;
    this->currentZ = 0;
}

//function to place the agent randomly in the maze. 
void Agent::placeRandomly(char** maze){
    std::vector<mcpp::Coordinate> nonWall;
    int currentX = 0;
    int currentZ = 0;
    int baseX = basePoint.x;
    int baseZ = basePoint.z;
    int randomLocationIndex = 0;
    mcpp::Coordinate randomLocation;
     //loop for x coord
    for(int i = 0; i < xlen; i++){
        //loop for z coord
        for (int j = 0; j < zlen; j++){ 
            currentX = baseX + i;
            currentZ = baseZ + j;

            if (maze[i][j] == '.'){
                nonWall.push_back(mcpp::Coordinate(currentX, basePoint.y, currentZ));
            }
        }
    }

    //get random coordinate
    randomLocationIndex = std::rand() % nonWall.size();
    randomLocation = nonWall[randomLocationIndex];

    //randomLocation is now generatedLocation
    generatedLocation = randomLocation;
    //it will place the place the player at the random location
    mc.setPlayerTilePosition(generatedLocation);
}

//function to go south
mcpp::Coordinate Agent::goSouth(int xCoord, int zCoord){
    this->currentX = xCoord;
    this->currentZ = zCoord;
    mcpp::Coordinate direction(currentX, currentLocation.y, currentZ + 1);

    this->currentZ = this->currentZ + 1;

    return direction;
}

//function to go west
mcpp::Coordinate Agent::goWest(int xCoord, int zCoord){
    this->currentX = xCoord;
    this->currentZ = zCoord;
    mcpp::Coordinate direction(currentX + 1, currentLocation.y, currentZ);

    this->currentX = this->currentX + 1;

    return direction;
}

//function to go north
mcpp::Coordinate Agent::goNorth(int xCoord, int zCoord){
    this->currentX = xCoord;
    this->currentZ = zCoord;
    mcpp::Coordinate direction(currentX, currentLocation.y, currentZ - 1);

    this->currentZ = this->currentZ - 1;

    return direction;
}

//function to go east
mcpp::Coordinate Agent::goEast(int xCoord, int zCoord){
    this->currentX = xCoord;
    this->currentZ = zCoord;
    mcpp::Coordinate direction(currentX - 1, currentLocation.y, currentZ);

    this->currentX = this->currentX - 1;

    return direction;
}



//function to initialise the player
bool Agent::initialise(){

    mcpp::Coordinate currentPosition(mc.getPlayerPosition());

    this->currentLocation = currentPosition;
    this->currentLocation.y = this->basePoint.y;

    std::cout<<currentPosition<<std::endl;

    int genX = currentPosition.x;
    int genY = currentPosition.y;
    int genZ = currentPosition.z;
    mcpp::Coordinate genLoc(genX, genY, genZ);

    //---LOGIC----
    //check every tile around the current location in clockwise direction
    //1) check the tile as if looking at it and check the tile to the right side
    //2) if the tile at the front is air and the tile to right is acacia, done
    //--------------------------------------------------------------------------

    // mcpp::BlockType frontBlock;
    // mcpp::BlockType rightBlock;
    bool initialised = false;
    int randomDirection = 0;
    int currX = genX;
    int currZ = genZ;

    //1) Looking at: South (x, y, z+1) / Wall at: West (x+1, y, z)
    //get the block at front
    this->rightBlock = mc.getBlock(mcpp::Coordinate(genX, genY, genZ + 1));
    //get the block at right side
    this->frontBlock = mc.getBlock(mcpp::Coordinate(genX + 1, genY, genZ));

    if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
        initialised = true;
        //save the positions
        this->positionOfRightWall = "West";
        this->coordRightWall = mcpp::Coordinate(currX + 1, genY, currZ);
    }

    //2) Looking at: West (x+1, y, z) / Walll at: North (x, y, z-1)
    //get the block at front
    this->frontBlock = mc.getBlock(mcpp::Coordinate(genX + 1, genY, genZ));
    //get the block at right side
    this->rightBlock = mc.getBlock(mcpp::Coordinate(genX, genY, genZ - 1));

    if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
        initialised = true;
        //save the positions
        this->positionOfRightWall = "North";
        this->coordRightWall = mcpp::Coordinate(currX, genY, currZ - 1);
    }

    //3) Looking at: North (x, y, z-1) / Wall at: East (x-1, y, z)
    //get the block at front
    this->frontBlock = mc.getBlock(mcpp::Coordinate(genX, genY, genZ - 1));
    //get the block at right side
    this->rightBlock = mc.getBlock(mcpp::Coordinate(genX - 1, genY, genZ));

    if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
        initialised = true;
        //save the positions
        this->positionOfRightWall = "East";
        this->coordRightWall = mcpp::Coordinate(currX - 1, genY, currZ);
    }

    //4) Looking at: East (x-1, y, z) / Wall at: South (x, y, z+1)
    //get the block at front
    this->frontBlock = mc.getBlock(mcpp::Coordinate(genX - 1, genY, genZ));
    //get the block at right side
    this->rightBlock = mc.getBlock(mcpp::Coordinate(genX, genY, genZ + 1));

    if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
        initialised = true;
        //save the positions
        this->positionOfRightWall = "South";
        this->coordRightWall = mcpp::Coordinate(currX, genY, currZ + 1);
    }

    //if there are no walls, choose a random direction and move until there is a wall on the right
    else{
        randomDirection = std::rand() % 4;

        while (initialised == false){
            //walk South
            if (randomDirection == 0){
                goSouth(currX, currZ);

                //1) Looking at: South (x, y, z+1) / Wall at: West (x+1, y, z)
                //get the block at front
                this->frontBlock = mc.getBlock(mcpp::Coordinate(currX, genY, currZ + 1));
                //get the block at right side
                this->rightBlock = mc.getBlock(mcpp::Coordinate(currX + 1, genY, currZ));

                if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
                    initialised = true;
                    //save the positions
                    this->positionOfRightWall = "West";
                    this->coordRightWall = mcpp::Coordinate(currX + 1, genY, currZ);
                }
            }

            //walk West
            else if (randomDirection == 1){
                goWest(currX, currZ);

                //2) Looking at: West (x+1, y, z) / Walll at: North (x, y, z-1)
                //get the block at front
                this->frontBlock = mc.getBlock(mcpp::Coordinate(currX + 1, genY, currZ));
                //get the block at right side
                this->rightBlock = mc.getBlock(mcpp::Coordinate(currX, genY, currZ - 1));

                if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
                    initialised = true;
                    //save the positions
                    this->positionOfRightWall = "North";
                    this->coordRightWall = mcpp::Coordinate(currX, genY, currZ - 1);
                }
            }

            //walk North
            else if (randomDirection == 2){
                goNorth(currX, currZ);

                //3) Looking at: North (x, y, z-1) / Wall at: East (x-1, y, z)
                //get the block at front
                this->frontBlock = mc.getBlock(mcpp::Coordinate(currX, genY, currZ - 1));
                //get the block at right side
                this->rightBlock = mc.getBlock(mcpp::Coordinate(currX - 1, genY, currZ));

                if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
                    initialised = true;
                    //save the positions
                    this->positionOfRightWall = "East";
                    this->coordRightWall = mcpp::Coordinate(currX - 1, genY, currZ);
                }
            }

            //walk East
            else if (randomDirection == 3){
                goEast(currX, currZ);

                //4) Looking at: East (x-1, y, z) / Wall at: South (x, y, z+1)
                //get the block at front
                this->frontBlock = mc.getBlock(mcpp::Coordinate(currX - 1, genY, currZ));
                //get the block at right side
                this->rightBlock = mc.getBlock(mcpp::Coordinate(currX, genY, currZ + 1));

                if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
                    initialised = true;
                    //save the positions
                    this->positionOfRightWall = "South";
                    this->coordRightWall = mcpp::Coordinate(currX, genY, currZ + 1);
                }
            }
            else{
                std::cout << "Error, could not intialise." << std::endl;
            }
        }

        this->currentX = currX;
        this->currentZ = currZ;
    }
    return initialised;
}

void Agent::turnRight(){
    //1) Looking at: South (x, y, z+1) / Wall at: West (x+1, y, z) 
    //turning RIGHT -> looking at: West / wall at: North
    if (positionOfRightWall == "West"){
        this->positionOfRightWall = "North";
        this->coordRightWall = mcpp::Coordinate(this->currentX, currentLocation.y, this->currentZ - 1);
    }

    //2) Looking at: West (x+1, y, z) / Walll at: North (x, y, z-1)
    //turning RIGHT -> looking at: North / wall at: East
    else if (positionOfRightWall == "North"){
        this->positionOfRightWall = "East";
        this->coordRightWall = mcpp::Coordinate(this->currentX - 1, currentLocation.y, this->currentZ);
    }

    //3) Looking at: North (x, y, z-1) / Wall at: East (x-1, y, z)
    //turning RIGHT -> looking at: East / wall at: South
    else if (positionOfRightWall == "East"){
        this->positionOfRightWall = "South";
        this->coordRightWall = mcpp::Coordinate(this->currentX, currentLocation.y, this->currentZ + 1);
    }

    //4) Looking at: East (x-1, y, z) / Wall at: South (x, y, z+1)
    //turning RIGHT -> looking at: South / wall at: West
    else if(positionOfRightWall == "South"){
        this->positionOfRightWall = "West";
        this->coordRightWall = mcpp::Coordinate(this->currentX + 1, currentLocation.y, this->currentZ);
    }
}

void Agent::blockedPathAndNoRightWall(){
    // mcpp::BlockType frontBlock;
    // mcpp::BlockType rightBlock;

    //1) Looking at: South (x, y, z+1) / Wall at: West (x+1, y, z) 
    //turning RIGHT -> looking at: West / wall at: North
    if (this->positionOfRightWall == "West"){
        this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX, currentLocation.y, this->currentZ + 1));
        this->rightBlock = mc.getBlock(this->coordRightWall);

        if (this->rightBlock == mcpp::Blocks::AIR){
            turnRight();
        }

        else if (this->frontBlock == mcpp::Blocks::ACACIA_WOOD_PLANK){
            turnRight();
        }
    }

    //2) Looking at: West (x+1, y, z) / Walll at: North (x, y, z-1)
    //turning RIGHT -> looking at: North / wall at: East
    else if (this->positionOfRightWall == "North"){
        this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX + 1,  currentLocation.y, this->currentZ));
        this->rightBlock = mc.getBlock(this->coordRightWall);

        if (this->rightBlock == mcpp::Blocks::AIR){
            turnRight();
        }

        else if (this->frontBlock == mcpp::Blocks::ACACIA_WOOD_PLANK){
            turnRight();
        }
    }

    //3) Looking at: North (x, y, z-1) / Wall at: East (x-1, y, z)
    //turning RIGHT -> looking at: East / wall at: South
    else if (this->positionOfRightWall == "East"){
        this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX,  currentLocation.y, this->currentZ - 1));
        this->rightBlock = mc.getBlock(this->coordRightWall);

        if (this->rightBlock == mcpp::Blocks::AIR){
            turnRight();
        }

        else if (this->frontBlock == mcpp::Blocks::ACACIA_WOOD_PLANK){
            turnRight();
        }
    }

    //4) Looking at: East (x-1, y, z) / Wall at: South (x, y, z+1)
    //turning RIGHT -> looking at: South / wall at: West
    else if(this->positionOfRightWall == "South"){
        this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX - 1,  currentLocation.y, this->currentZ));
        this->rightBlock = mc.getBlock(this->coordRightWall);

        if (this->rightBlock == mcpp::Blocks::AIR){
            turnRight();
        }

        else if (this->frontBlock == mcpp::Blocks::ACACIA_WOOD_PLANK){
            turnRight();
        }
    }
}

//walk forward sensing the right side wall
void Agent::walk(){
    // mcpp::BlockType frontBlock;
    // mcpp::BlockType rightBlock;
    this->currentX = currentLocation.x;
    this->currentZ = currentLocation.z;
    mcpp::Coordinate currLocation(this->currentX, currentLocation.y, this->currentZ);

    //walk straight based on the direction of the wall on the right
    //Check the position of the wall on the right.
    while (mc.getBlock(currLocation) != mcpp::Blocks::BLUE_CARPET){
        //standard wall following
        if (this->positionOfRightWall == "West"){

            //if wall dont put carpet
            if (mc.getBlock(currLocation) != mcpp::Blocks::ACACIA_WOOD_PLANK){
                mc.setBlock(currLocation, mcpp::Blocks::LIME_CARPET);
                // std::this_thread::sleep_for(std::chrono::milliseconds(500)); //500ms delay
                // mc.setBlock(currLocation, mcpp::Blocks::AIR);
            }

            //if it is a wall turn
            this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX, currentLocation.y, this->currentZ + 1));
            this->rightBlock = mc.getBlock(this->coordRightWall);

            if (this->frontBlock == mcpp::Blocks::ACACIA_WOOD_PLANK){
                turnRight();
            }

            else if (this->rightBlock == mcpp::Blocks::AIR){
                turnRight();
            }
            
            //else keep going straight
            else{
                currLocation = goSouth(this->currentX, this->currentZ);
                std::cout << currLocation << std::endl;
            }
        }

        else if (this->positionOfRightWall == "North"){
            if (mc.getBlock(currLocation) != mcpp::Blocks::ACACIA_WOOD_PLANK){
                mc.setBlock(currLocation, mcpp::Blocks::LIME_CARPET);
                // std::this_thread::sleep_for(std::chrono::milliseconds(500)); //500ms delay
                // mc.setBlock(currLocation, mcpp::Blocks::AIR);
            }

            this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX + 1,  currentLocation.y, this->currentZ));
            this->rightBlock = mc.getBlock(this->coordRightWall);

            if (this->frontBlock == mcpp::Blocks::ACACIA_WOOD_PLANK){
                turnRight();
            }

            else if (this->rightBlock == mcpp::Blocks::AIR){
                turnRight();
            }

            else{
                currLocation = goWest(this->currentX, this->currentZ);
                std::cout << currLocation << std::endl;
            }
        }

        else if (this->positionOfRightWall == "East"){
            if (mc.getBlock(currLocation) != mcpp::Blocks::ACACIA_WOOD_PLANK){
                mc.setBlock(currLocation, mcpp::Blocks::LIME_CARPET);
                // std::this_thread::sleep_for(std::chrono::milliseconds(500)); //500ms delay
                // mc.setBlock(currLocation, mcpp::Blocks::AIR);
            }

            this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX,  currentLocation.y, this->currentZ - 1));
            this->rightBlock = mc.getBlock(this->coordRightWall);

            if (this->frontBlock == mcpp::Blocks::ACACIA_WOOD_PLANK){
                turnRight();
            }

            else if (this->rightBlock == mcpp::Blocks::AIR){
                turnRight();
            }
            
            else{
                currLocation = goNorth(this->currentX, this->currentZ);
                std::cout << currLocation << std::endl;
            }
        }

        else if(this->positionOfRightWall == "South"){
            if (mc.getBlock(currLocation) != mcpp::Blocks::ACACIA_WOOD_PLANK){
                mc.setBlock(currLocation, mcpp::Blocks::LIME_CARPET);
                // std::this_thread::sleep_for(std::chrono::milliseconds(500)); //500ms delay
                // mc.setBlock(currLocation, mcpp::Blocks::AIR);
            }

            this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX - 1,  currentLocation.y, this->currentZ));
            this->rightBlock = mc.getBlock(this->coordRightWall);

            if (this->frontBlock == mcpp::Blocks::ACACIA_WOOD_PLANK){
                turnRight();
            }

            else if (this->rightBlock == mcpp::Blocks::AIR){
                turnRight();
            }
            
            else{
                currLocation = goEast(this->currentX, this->currentZ);
                std::cout << currLocation << std::endl;
            }
        }

        //1) Looking at: South (x, y, z+1) / Wall at: West (x+1, y, z)
        //get the block at front
        this->rightBlock = mc.getBlock(mcpp::Coordinate(this->currentX, currentLocation.y, this->currentZ + 1));
        //get the block at right side
        this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX + 1, currentLocation.y, this->currentZ));

        if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
            this->positionOfRightWall = "West";
        }


        //2) Looking at: West (x+1, y, z) / Walll at: North (x, y, z-1)
        //get the block at front
        this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX + 1, currentLocation.y, this->currentZ));
        //get the block at right side
        this->rightBlock = mc.getBlock(mcpp::Coordinate(this->currentX, currentLocation.y, this->currentZ - 1));

        if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
            this->positionOfRightWall = "North";
        }

        //3) Looking at: North (x, y, z-1) / Wall at: East (x-1, y, z)
        //get the block at front
        this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX, currentLocation.y, this->currentZ - 1));
        //get the block at right side
        this->rightBlock = mc.getBlock(mcpp::Coordinate(this->currentX - 1, currentLocation.y, this->currentZ));

        if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
            this->positionOfRightWall = "East";
        }

        //4) Looking at: East (x-1, y, z) / Wall at: South (x, y, z+1)
        //get the block at front
        this->frontBlock = mc.getBlock(mcpp::Coordinate(this->currentX - 1, currentLocation.y, this->currentZ));
        //get the block at right side
        this->rightBlock = mc.getBlock(mcpp::Coordinate(this->currentX, currentLocation.y, this->currentZ + 1));

        if ((this->frontBlock ==  mcpp::Blocks::AIR) && (this->rightBlock == mcpp::Blocks::ACACIA_WOOD_PLANK)){
            this->positionOfRightWall = "South";
        }

        currLocation = mcpp::Coordinate(this->currentX, currentLocation.y, this->currentZ);
    }

    std::cout << "Exit found!" <<std::endl;
}