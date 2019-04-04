#include "edge.h"
/**
 * @brief Construct a new Edge:: Edge object
 * This is the default constructor, make sure each object is overrriden before use.
 */
Edge::Edge(){
    this->start = Node();
    this->end = Node();
}
/**
 * @brief Construct a new Edge:: Edge object
 * This is a parameterised constructor that takes two points as the input
 * @param first 
 * It is the starting Node
 * @param second 
 * It is the ending Node
 */
Edge::Edge(Node first,Node second):start(first),end(second){
    if(first.getX()==second.getX()){
        slope = std::numeric_limits<double>::max();
        if(first.getX()<0){
            intercept = - std::numeric_limits<double>::max();
        }
        else{
            intercept = std::numeric_limits<double>::max();
        }
    }
}
/**
 * @brief Construct a new Edge:: Edge object
 * This is used for creating lines of best fit based on the already calculated slopes and intercepts and contains the extrema points.
 * @param slope 
 * Slope of the line of best fit, which is calculated in main.cpp
 * @param intercept 
 * It is the intercept of the best fit line which is calcualted  in main.cpp
 * @param first 
 * The first point is used to calculate the point of the line of best fit.
 * @param second 
 * The second point is used 
 */
Edge::Edge(double slope, double intercept, Node first, Node  second){
    double predict = intercept + slope*first.getX();
    this->start = Node(first.getX(),predict);
    predict = intercept + slope*second.getX();
    this->end = Node(second.getX(),predict);
    this->slope = slope;
    this->intercept = intercept;
}
/**
 * @brief Construct a new Edge:: Edge object
 * This is used to create lines for the case in which the slope is infinite. Here we know that the line passes through the average x value
 * @param slope 
 * The slope is either infinity or -infinity
 * @param average_x_value 
 * It is used for the x intercept through which the line passes
 * @param start_y 
 * It is used to refer to the first point of the line
 * @param end_y 
 * It is used for the secod point on the file
 */
Edge::Edge(double slope,double average_x_value,double start_y,double end_y){
    this->start =  Node(average_x_value,start_y);
    this->end = Node(average_x_value,end_y);
    this->slope = slope;
    if(average_x_value>0){
        this->intercept = - std::numeric_limits<double>::max();
    }
    else{
        this->intercept = std::numeric_limits<double>::max();
    }
}
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