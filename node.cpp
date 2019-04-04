#include "node.h"

		Node::Node(){
			this->x = 0;
			this->y = 0;
		}
		Node::Node(double x,double y){
			this->x = x;
			this->y = y;
		}
		double Node::getX(){
			return this->x;
		}
		double Node::getY(){
			return this->y;
		}
		std::pair<double,double> Node::get_point(){
			return std::make_pair(this->x,this->y);
		}
		std::string Node::to_string(){
			const int length = 30;
			char format_string[length];
			sprintf(format_string,"%lf,%lf",this->x,this->y);
			std::string temp = format_string;
			return temp;
		}