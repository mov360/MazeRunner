#include "Node.h"

Node::Node(){
    position = mcpp::Coordinate();
    blockType = mcpp::BlockType();
    nextNode = nullptr;
}

Node::Node(mcpp::Coordinate position, int type){
    this->position = position;
    this->type = type;

    nextNode = nullptr;
}

// void Node::setNextNode(Node* nextNode){
//     this->nextNode = nextNode;
// }

Node* Node::getNextNode(){
    return nextNode;
}

void Node::insertNode(Node* node){
    node->nextNode = nextNode;
    nextNode = node;
}

int Node::getType(){
    return type;
}

mcpp::Coordinate Node::getBlockPos(){
    return position;

}
mcpp::BlockType Node::getBlockType(){
    return blockType;
}