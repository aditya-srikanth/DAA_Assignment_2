#include <iostream>
#include <vector>
#include "node.h"
#include "line_cost.h"
int main(){
	Data data; // default cnstr, so use default locations
	std::vector<Node> values = data.read_data();
	// TODO
	//Algorithm comes here
	double slope_of_best_fit,intercept_of_best_fit,sum_of_x,sum_of_y,sum_of_x_square,sum_of_xy;

	for(int j = 0; j<values.size();j++){
		slope_of_best_fit = 0 ;
		intercept_of_best_fit = 0;
		sum_of_x,sum_of_y = 0;
		sum_of_x_square,sum_of_xy = 0 ;
		for(int i=0;i<=j;i++){
			sum_of_y += values[i].getY();
			sum_of_x += values[i].getX();
			sum_of_xy += values[i].getX() * values[i].getY() ;
			sum_of_x_square += values[i].getX() * values[i].getX();
 		}
			slope_of_best_fit = ( values.size()*sum_of_xy - sum_of_x*sum_of_y ) / (values.size()*sum_of_x_square - sum_of_x*sum_of_x); 
	}
	return 0;
}

double error(double slope,Node point){
	double predict = slope * point.getX();
	double dev = predict - point.getY();
	return dev*dev;
}
