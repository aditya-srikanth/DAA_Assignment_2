#ifdef NODE
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
		pair<double,double> get_point();
		void to_string();
};
#endif