#include "Maze.h"
#include <random>
#include <thread>
#include <chrono>

//CONSTRUCTOR
Maze::Maze(mcpp::Coordinate basePoint, unsigned int xlen, unsigned int zlen, bool mode){
    this->basePoint = basePoint;
    this->xlen = xlen;
    this->zlen = zlen;
    this->mode = mode;

    //nodes for the flattening
    firstNode = nullptr;
    endNode = nullptr;

    //nodes for the building maze
    firstNodeBuilding = nullptr;
    endNodeBuilding = nullptr;
}

//DESTRUCTOR
Maze::~Maze(){
}

//RESET MAZE FUNCTION
void Maze::resetMaze(mcpp::Coordinate basePoint, unsigned int xlen, unsigned int zlen){
    this->basePoint = basePoint;
    this->xlen = xlen;
    this->zlen = zlen;
}

//FUNCTION TO TELEPORT THE PLAYER TO THE BASE POINT
void Maze::teleportToBasePoint(){
    mc.setPlayerTilePosition(basePoint);
}

//BASE POINT SETTER FUNCTION
void Maze::setBasePoint(mcpp::Coordinate basePoint){
    this->basePoint = basePoint;
}

//FUNCTION TO FLATTEN THE MAZE AREA
void Maze::flattenMazeArea(unsigned int xlen, unsigned int zlen){
    this->xlen = xlen;
    this->zlen = zlen;

    int basePointYMinusOne = basePoint.y - 1;
    //int basePointYPlusOne = basePoint.y + 1;
    int basePointY = basePoint.y;
    int basePointX = basePoint.x;
    int basePointZ = basePoint.z;

    //get the block at base point
    mcpp::BlockType basePointBlockType = mc.getBlock(mcpp::Coordinate(basePointX, basePointY - 1, basePointZ));

    if (basePointBlockType == mcpp::Blocks::AIR){
        basePointBlockType = mcpp::Blocks::ACACIA_WOOD_PLANK;
    }
    
    /*
    to account for gravity: check if there is a block below the 
    position to fill in (at basepoint y height, so need to check 
    basepoint y height-1)
    */
   
    int blockUnderHeight;
    blockUnderHeight = basePointY - 2;

    for (unsigned int i = basePointX; i < basePointX + xlen; i++){
         for (unsigned int j = basePointZ; j < basePointZ + zlen; j++){
            int currentBlockHeight;
            currentBlockHeight = mc.getHeight(i, j);
            mcpp::Coordinate currentPositionAtMax(i, basePointY, j);
            mcpp::Coordinate currentBlockPositionMaxMinusOne(i, basePointY - 1, j);

            //CASE 1
            //if the current block height is bigger than the base 
            //point height, remove the blocks until y
            if (basePointY - 1 < currentBlockHeight){
                for (int k = currentBlockHeight; k >= basePointY; k--){
                    mcpp::Coordinate locationBlockRemoved(i, k, j);
                    mcpp::BlockType currentBlockType = mc.getBlock(mcpp::Coordinate(i, k, j));
                     //save the type of block 
                    addChangedBlock(locationBlockRemoved, currentBlockType.id);
                    mc.setBlock(mcpp::Coordinate(i, k, j), mcpp::Blocks::AIR);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
                }
            }
         }
    }

    for (unsigned int i = basePointX; i < basePointX + xlen; i++){
         for (unsigned int j = basePointZ; j < basePointZ + zlen; j++){
            int currentBlockHeight;
            currentBlockHeight = mc.getHeight(i, j);
            mcpp::Coordinate currentPositionAtMax(i, basePointYMinusOne, j);
            mcpp::Coordinate currentBlockPositionMaxMinusOne(i, basePointYMinusOne - 1, j);

            //CASE 2
            //if currrent block height is smaller than base point height, fill it in with the block at base point
            if (currentBlockHeight < basePointY - 1){
                
                //gravity check
                //if there is a block at blockUnderHeight, then CASE1, else, CASE2.
                mcpp::Coordinate blockUnderCoordinate(i, blockUnderHeight, j);
                mcpp::BlockType underBlock = mc.getBlock(blockUnderCoordinate);
                //CASE 1: YES, JUST PLACE THE BLOCK
                if (underBlock.id != mcpp::Blocks::AIR.id){
                    //save the position and block at the level of basepoint y
                    addChangedBlock(currentPositionAtMax, 0); 
                    /*save the position 
                    of the empty space but do not save the air block. if 0, it is an air block.
                    */
                    //place the new type of block
                    mc.setBlock(mcpp::Coordinate(i, basePointYMinusOne, j), basePointBlockType);
                     //50ms delay
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                //CASE 2: NO, THEREFORE WE NEED TO ADD A BLOCK UNDERNEATH
                else if (underBlock.id == mcpp::Blocks::AIR.id){
                    mc.setBlock(mcpp::Coordinate(i, basePointYMinusOne - 1, j), basePointBlockType);
                    //50ms delay
                    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
                    //save the position 
                    addChangedBlock(currentPositionAtMax, 0); 
                    //of the empty space but do not save the air block.if 0, it is an air block.
                    mc.setBlock(mcpp::Coordinate(i, basePointYMinusOne, j), basePointBlockType);
                    //50ms delay
                    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
                     //save the position 
                    addChangedBlock(currentBlockPositionMaxMinusOne, 0);
                    //of the empty space but do not save the air block.if 0, it is an air block.
                }
            }
         }
    }
}


//FUNCTION TO BUILD THE MAZE
void Maze::buildMaze(char** maze, unsigned int xlen, unsigned int zlen){
    for (unsigned int i = 0; i < xlen; i++){
        for (unsigned int j = 0; j < zlen; j++){
            unsigned int flipHorizontallyJ  = zlen-1-j;
            mcpp::Coordinate currentPosition(basePoint.x+i, basePoint.y, basePoint.z+flipHorizontallyJ);

            char currentBlockInMap = maze[i][j];

            if (currentBlockInMap == 'x'){
                mc.setBlock(currentPosition, mcpp::Blocks::ACACIA_WOOD_PLANK);
                //50ms delay
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
                //save the position 
                addChangedBlockBuilding(currentPosition, 0); 
                mc.setBlock(mcpp::Coordinate(currentPosition.x, currentPosition.y+1, currentPosition.z), mcpp::Blocks::ACACIA_WOOD_PLANK);
                 //50ms delay
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                //save the position 
                addChangedBlockBuilding(mcpp::Coordinate(currentPosition.x, currentPosition.y+1, currentPosition.z), 0); 
                mc.setBlock(mcpp::Coordinate(currentPosition.x, currentPosition.y+2, currentPosition.z), mcpp::Blocks::ACACIA_WOOD_PLANK);
                 //50ms delay
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                //save the position 
                addChangedBlockBuilding(mcpp::Coordinate(currentPosition.x, currentPosition.y+2, currentPosition.z), 0); 
                //of the empty space but do not save the air block.if 0, it is an air block.
            }
            else if (currentBlockInMap == 'C'){
                mc.setBlock(currentPosition, mcpp::Blocks::BLUE_CARPET);
                 //50ms delay
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                //save the position 
                addChangedBlockBuilding(currentPosition, 0); 
                //of the empty space but do not save the air block.if 0, it is an air block.
            }
        }
    }
}

//FUNCTION TO CLEAN UP AFTER DONE
void Maze::cleanUpBuilding(){
    Node* currNode = firstNodeBuilding;

    while (currNode != nullptr){
        mcpp::Coordinate position = currNode->getBlockPos();
        int type = currNode->getType();

        if (type == 0){
            mcpp::BlockType blockType = mcpp::Blocks::AIR;
            mc.setBlock(position, blockType);
        }
        else{
            mcpp::BlockType blockType = type;
            mc.setBlock(position, blockType);
        }

        currNode = currNode->getNextNode();
    }
}

void Maze::cleanUpFlatten(){
    Node* currNode = firstNode;

    while (currNode != nullptr){
        mcpp::Coordinate position = currNode->getBlockPos();
        int type = currNode->getType();

        if (type == 0){
            mcpp::BlockType blockType = mcpp::Blocks::AIR;
            mc.setBlock(position, blockType);
        }
        else{
            mcpp::BlockType blockType = type;
            mc.setBlock(position, blockType);
        }

        currNode = currNode->getNextNode();
    }
}

void Maze::cleanUp(){
    cleanUpBuilding();
    cleanUpFlatten();
    clearLinkedList();
}

//FUNCTION TO ADD A CHANGED BLOCK TO THE LINKED LIST (flattening)
void Maze::addChangedBlock(mcpp::Coordinate pos, int type){

    Node *node = new Node(pos, type);

    if(firstNode == nullptr){
        firstNode = node;
        endNode = node;
    }
    else{
        endNode->insertNode(node);
        endNode = node;
    }
}

//FUNCTION TO ADD A CHANGED BLOCK TO THE LINKED LIST (building)
void Maze::addChangedBlockBuilding(mcpp::Coordinate pos, int type){

    Node *node = new Node(pos, type);

    if(firstNodeBuilding == nullptr){
        firstNodeBuilding = node;
        endNodeBuilding = node;
    }
    else{
        endNodeBuilding->insertNode(node);
        endNodeBuilding = node;
    }
}

//FUNCTION TO CLEAR THE LINKED LIST
void Maze::clearLinkedList(){
    Node* currNode = firstNode;
    while (currNode != nullptr){
        Node* nodeToDelete = currNode;
        currNode = currNode->getNextNode();
        delete nodeToDelete;
    }
    firstNode = nullptr;
    endNode = nullptr;

    currNode = firstNodeBuilding;
    while (currNode != nullptr){
        Node* nodeToDelete = currNode;
        currNode = currNode->getNextNode();
        delete nodeToDelete;
    }
    firstNodeBuilding = nullptr;
    endNodeBuilding = nullptr;
}

//function to check if the linked list is empty or not
bool Maze::checkLinkedListEmpty(){
    bool check = false;

    if ((firstNode == nullptr) && (firstNodeBuilding == nullptr)){
        check = true;
    }

    return check;
}

char** Maze::deleteMaze(char** maze, unsigned int x){
    if(maze != nullptr){
            for (unsigned int i = 0; i < x; i++) {
                delete[] maze[i];
            }
        }
        
        delete[] maze;
        maze = nullptr;
        
    return maze;                
}

