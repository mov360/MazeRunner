#include "RecursiveBackTracking.h"
#include <cstdlib>
#include <ctime> 
#include <algorithm>

Recursive::Recursive(){
    this->LENGTH = 0;
    this->WIDTH = 0;
}

Recursive::Recursive(unsigned int LENGTH, unsigned int WIDTH){
    this->LENGTH = LENGTH;
    this->WIDTH = WIDTH;
}

void Recursive::generateMaze(char** structure){
    unsigned int i,j;

    //initialize the map with only blocks 'X'. It helps to create and keep the borders intact
    for(i =0; i < LENGTH; i++){
        for(j = 0; j < WIDTH; j++){
            structure[i][j] = 'x';
        }
    }

    int a = 1;
    int b = 1;
     //Starting point of the path (1,1)
    desigingMaze(a, b, structure);


    //Gate
    structure[0][1] = '.';
}
void Recursive::desigingMaze(int x0, int y0, char** structure){
   
     unsigned int i;

    structure[x0][y0] = '.';

    int xCod[] = {1,-1,0,0};
    int yCod[] = {0,0,1,-1};

    int turn[] = {0,1,2,3};
    for(i = 0; i < 4; i++){
        int shuffler = rand() % 4;
         //randomize the element of turn[→,←,↑,↓] array
        std::swap(turn[i],turn[shuffler]);
    }

   for(i  = 0; i < 4; i++){
    //X , Y are new chosen direction from current position(distance 2 tiles)
    unsigned int X = x0 + xCod[turn[i]]*2;
    unsigned int Y = y0 + yCod[turn[i]]*2;


        if(X >0 && X < LENGTH-1){
            if(Y > 0 && Y < WIDTH-1){
                if(structure[X][Y]!= '.'){
                    structure[x0 + xCod[turn[i]]][y0 + yCod[turn[i]]] = '.';

                    desigingMaze(X,Y,structure);
                }
            }
        }
   } 


}