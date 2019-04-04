#include "node.h"
		/**
		 * @brief Construct a new Node:: Node object
		 * Default constructor that creates a Node at the origin
		 */
		Node::Node(){
			this->x = 0;
			this->y = 0;
		}
		/**
		 * @brief Construct a new Node:: Node object
		 * It creates a Node at a user defined location.
		 * @param x
		 * This is the x coordinate of the Node 
		 * @param y 
		 * This is the y coordinate of the Node
		 */
		Node::Node(double x,double y){
			this->x = x;
			this->y = y;
		}
		/**
		 * @brief 
		 * Getter to obtain the x coordinate of the node
		 * @return double 
		 */
		double Node::getX(){
			return this->x;
		}
		/**
		 * @brief 
		 * Getter to obtain the y coordinate of the node
		 * @return double 
		 */
		double Node::getY(){
			return this->y;
		}
		/**
		 * @brief 
		 * Getter to obtain the node as a pair
		 * @return std::pair<double,double> 
		 * The first element is the x coordinate and the second is the y cooredinate
		 */
		std::pair<double,double> Node::get_point(){
			return std::make_pair(this->x,this->y);
		}
		/**
		 * @brief 
		 * This returns a string containing the point in the format x,y
		 * @return std::string 
		 */
		std::string Node::to_string(){
			const int length = 30;
			char format_string[length];
			sprintf(format_string,"%lf,%lf",this->x,this->y);
			std::string temp = format_string;
			return temp;
		}