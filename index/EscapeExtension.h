#ifndef ESCAPEEXTENSION_H
#define ESCAPEEXTENSION_H

#include <iostream>
#include <mcpp/mcpp.h>
#include <string>
#include <vector>
#include <cstdlib>

class EscapeExtension
{

public:
    EscapeExtension(mcpp::Coordinate basePoint);
    ~EscapeExtension();

    void pathBool(int coordX, int coordZ);
    
private:
    /* data */
    bool pathLogic(int beginX, int beginZ);
    mcpp::MinecraftConnection mc;
    mcpp::BlockType checkingBlock;
    mcpp::Coordinate checkingLocation;
    mcpp::Coordinate basePoint;
    int count;
};



#endif //ESCAPEEXTENSION_H