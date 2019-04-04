#ifndef EDGE
#define EDGE
#include <string>
#include <limits>
#include "node.h"
/**
 * @brief 
 * Edge is used to represent a line of best fit that is used for a particular set of points.
 */
class Edge{
    private:
        Node start;
        Node end;
        double intercept;
        double slope;
    public:
        Edge();
        Edge(Node start,Node end);
        Edge(double slope,double intercept,Node first,Node second);
        Edge(double slope,double average_x_value,double start_y,double end_y);
        std::string to_string();
        Node get_start();
        Node get_end();
};

#endif