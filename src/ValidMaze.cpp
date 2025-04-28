#include "ValidMaze.h"
#include <iostream>

Valid::Valid(){
    this->xlen = 0;
    this->zlen = 0;
}

Valid::Valid(unsigned int xLen, unsigned int zLen){
    this->xlen = xLen;
    this->zlen = zLen;
}

Valid::Valid(char** structure, unsigned int xLen, unsigned int zLen){
    this->xlen = xLen;
    this->zlen = zLen;
    this->structure = structure;

    structure = new char*[xLen];
    for (unsigned int i = 0; i < xLen; i++){
        structure[i] = new char[zLen];
    }
}


int  Valid::numGate(char** structure3){
    int count = 0;

    /**
     * It shall check the number of gates in every border in the maze
     * Everytime the border is checked , it shall look for gate and increase count
     * Expected gate should be 1
     * if there is more, the main function will decide the rest validate it or not
    
    */

    for(unsigned int i = 0; i < xlen; i++){
        if(structure3[i][0]!='x'){count++;}
        if(structure3[i][zlen-1]!='x'){count++;}
    }

    for(unsigned int i = 0; i < zlen; i++){
        if(structure3[0][i]!='x'){count++;}
        if(structure3[xlen-1][i]!='x'){count++;}
    }

return count;
}

    

bool Valid::loopDetection1(char** structure4) {
    /**
    
     * 'hasLoop' proves the existance of the loop. flase = No Loop, true = Loop exist
     * The for loop would look thru every point('.') 
     * loopDetection2 function will look from the point to find a loop
     * Looking for the loop shall start from initial point(x0,y0). Here it has to be (x0,y0)=
       (-1,-1). The logic behind  (x0,y0) is not let the loopDetection2 function to not let it come back to 
       prrevious point. The loop shall start from (0,0) and there is no cell before that. Only (-1,-1) can be
       considered as previous point of (0,0). The maze starts from (x,z)=(0,0). If (0,0) is not considered, 
       it can't detect the loop(s) properly.
    */
    
   bool hasLoop = false;
    
    for (unsigned int i = 0; i < xlen && !hasLoop; i++) {
        for (unsigned int j = 0; j < zlen && !hasLoop; j++) {
            if (structure4[i][j] == '.') {
                /*
                'hasLoop' will become true once it finds a loop in the maze and
                 trigers it to make it false in order to stop the searching. 
                */
                hasLoop = loopDetection2(structure4, i, j, -1, -1);
            }
        }
    }

    return hasLoop;
}

bool Valid::loopDetection2( char** structure5,unsigned int x,unsigned int y,unsigned int x0,unsigned int y0) {
    /**
     * Maze cell x,y shall be the current cell and it starts looking for 
       the loop from here.
     * 'isLoop' initiated with false since there is no loop yet.
     * Current cell will be marked as 'v' to identify as visited.
     * The for loop will iterate by 4 directions of the map so that it doesn't miss any loop in maze.
     *  xCod and yCod are responsible to change the direction for current cell.
     * X and Y are the next cell those shall be checked after x and y.
    */

    bool isLoop = false;
    // Mark current cell as visited
    structure5[x][y] = 'v';  
     // Right, Down, Left, Up
    int xCod[4] = {0, 1, 0, -1}; 
    int yCod[4] = {1, 0, -1, 0};

    for (int i = 0; i < 4; i++) {
        unsigned int X = x + xCod[i];
        unsigned int Y = y + yCod[i];

        if (X >= 0 && X < xlen && Y >= 0 && Y < zlen && structure5[X][Y] != 'x') {
             // Check for a loop
            if (structure5[X][Y] == 'v') { 
                if (!(X == x0 && Y == y0)) {
                    isLoop = true;
                    mazeTrans(x,y);
                }
            } else if (structure5[X][Y] == '.') {
                if (loopDetection2( structure5, X, Y, x, y)) {
                    isLoop = true;
                }
            }
        }
    }

    /*
    Reseting the current cell to the '.' path again so that loop can later use the maze again 
    every single paths and keeping it visited doesn't make any kind confusion.
    */
    // Reset cell to unvisited
    structure5[x][y] = '.'; 
    return isLoop;
}

void Valid::mazeTrans(unsigned int x, unsigned z){

    this->structure[x][z] = 'x';
}


bool Valid::isolatedCells1(char** structure1) {
    /**
    * Starting variable statess the detection of founding the maze's gate or entry
    * The loop iterates until it finds the entry point 
    * Once it finds the entry point, it will terminate and call the isolatedCells2() to connect the path
    * from the entry point 
    */ 
    bool starting = false;

    for (unsigned int i = 0; i < xlen && !starting; i++) {
        for (unsigned int j = 0; j < zlen && !starting; j++) {
             // Found the entry point
            if (structure1[i][j] == '.') {
                isolatedCells2(structure1, i, j); 
                // Entry point found
                starting = true; 
            }
        }
    }

    bool ok = false;
    /**
    * This loop enquires further unconnected paths.
    * If there are any unconnected path with the entry, it shall return the function with true
    * It shall look if there's/'re any '.' which are/is not v 
    */
    for (unsigned int i = 0; i < xlen; i++) {
        for (unsigned int j = 0; j < zlen; j++) {
            if (structure1[i][j] == '.') {
                // Found an unconnected path
                ok = true;
                mazeTrans(i,j); 
            }
        }
    }
    
    return ok;
}

void Valid::isolatedCells2(char** structure2, unsigned int x, unsigned int y) {
    /*
    This counter ensures that the value of x and y do not go out of the bounds/range of the maze. 
    If it goes out of the range it will immediately terminate the recursive function by making the flag to 1. 
    Also, if the cell is wall or visited (e.g., 'X', '.'), then it shall terminate. 
    If it is in the range then, the counter won't terminate the function and it keeps calling itself and the flag doesn't change.
    */
   

    if (x < 0 || x >= xlen || y < 0 || y >= zlen || structure2[x][y] != '.') {
        return;
    }
    

        // every time it visits '.' or goes through the path, it makes it 'v'
        // the function only goes through the connected path from the first point 
        structure2[x][y] = 'v';
    

    /**
     * This will recursively call the function itself according to the value of x and y
     * Every time if the value of structure[x][y] is '.', it will change it to v to keep track that it has visited it
     * This path is all connected to the starting point determined from isolatedCells1() function
    */

        
            // up
            isolatedCells2(structure2, x - 1, y); 
            // down
            isolatedCells2(structure2, x + 1, y);
            // left
            isolatedCells2(structure2, x, y - 1);
            // right
            isolatedCells2(structure2, x, y + 1); 

         
        
        
}




char** Valid::getArr(){
    return this->structure;
}