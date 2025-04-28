#ifndef RECURSIVEBACKTRACKING_H
#define RECURSIVEBACKTRACKING_H

class Recursive{

    public:
            //constructor
            Recursive();
            Recursive(unsigned int LENGTH, unsigned int WIDTH);
            // function declarations
            void generateMaze(char** structure);
            void desigingMaze(int x0, int y0, char** structure);
            
    private:
            unsigned int LENGTH;
            unsigned int WIDTH;        
};

#endif
