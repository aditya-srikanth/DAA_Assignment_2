#include "edge.h"
/**
 * @brief Construct a new Edge:: Edge object
 * This is a parameterised constructor that takes two points as the input
 * @param first 
 * It is the starting Node
 * @param second 
 * It is the ending Node
 */
Edge::Edge(Node first,Node second):start(first),end(second){}

/**
 * @brief 
 * It returns a string that shows the nodes in the following format x,y:x,y
 * @return std::string 
 */
std::string Edge::to_string(){
    const int length = 50;
    char temp[length];
    sprintf(temp,"%s:%s",this->start.to_string().c_str(),this->end.to_string().c_str());
    std::string val = temp;
    return val;
}

/**
 * @brief 
 * This returns the first Node of the edge
 * @return Node 
 */
Node Edge::get_start(){
    this->start;
}

/**
 * @brief 
 * This returns the second Node of the edge
 * @return Node 
 */
Node Edge::get_end(){
    this->end;
}