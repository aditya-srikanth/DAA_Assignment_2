#include <iostream>
#include <vector>
#include "node.h"
#include "line_cost.h"
int main(){
	Data data; // default cnstr, so use default locations
	std::vector<Node> values = data.read_data();
	// TODO
	//Algorithm comes here
	return 0;
}

double error(double slope,Node point){
	double predict = slope * point.getX();
	double dev = predict - point.getY();
	return dev*dev;
}