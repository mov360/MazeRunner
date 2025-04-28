#ifndef NODE_H
#define NODE_H

#include <mcpp/mcpp.h>

class Node{
    private:
         //position of block
        mcpp::Coordinate position;
        int type;
        mcpp::BlockType blockType;
        //pointer to next node in linked list
        Node* nextNode; 
        mcpp::MinecraftConnection mc;
    public:
        Node(); 
        Node(mcpp::Coordinate position, int type);
        //get next node function
        Node* getNextNode(); 
        //insert a new node after the current node
        void insertNode(Node* node); 
        int getType();
        mcpp::Coordinate getBlockPos();
        mcpp::BlockType getBlockType();
        // void setNextNode(Node* nextNode);

};

#endif //NODE_H