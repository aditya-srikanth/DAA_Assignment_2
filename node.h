#ifndef NODE
#define NODE

#include <string>

class Node{
	private:
		double x;
		double y;
	public:
		Node();
		Node(double,double);
		double getX();
		double getY();
		std::pair<double,double> get_point();
		std::string to_string();
};
#endif