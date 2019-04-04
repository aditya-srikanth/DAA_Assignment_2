#ifndef EDGE
#define EDGE
#include <string>
#include "node.h"
/**
 * @brief 
 * Edge is used to represent a line of best fit that is used for a particular set of points.
 */
class Edge{
    private:
        Node start;
        Node end;
    public:
        Edge(Node start,Node end);
        std::string to_string();
        Node get_start();
        Node get_end();
};

#endif