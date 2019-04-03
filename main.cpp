#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "node.h"
#include "data.h"
#include "line_cost.h"
double calculate_error(double slope,double intercept,Node point){
	double predict = slope * point.getX() + intercept;
	double dev = predict - point.getY();
	return dev*dev;
}

int main(){
	Data data; // default cnstr, so use default locations
	std::vector<Node> values = data.read_data();
	// TODO
	//Algorithm comes here
	double slope_of_best_fit,intercept_of_best_fit,sum_of_x,sum_of_y,sum_of_x_square,sum_of_xy;
	double errors[values.size()][values.size()];

	for(int k = 0; k < values.size() ; k++){
		for(int j = 0; j <= k;j++){
			slope_of_best_fit = 0 ;
			intercept_of_best_fit = 0;
			sum_of_x,sum_of_y = 0;
			sum_of_x_square,sum_of_xy = 0 ;
			if(j != k){
				for(int i=j;i<=k;i++){
					sum_of_y += values[i].getY();
					sum_of_x += values[i].getX();
					sum_of_xy += values[i].getX() * values[i].getY() ;
					sum_of_x_square += values[i].getX() * values[i].getX();
				}
				slope_of_best_fit = ( values.size()*sum_of_xy - sum_of_x*sum_of_y ) / (values.size()*sum_of_x_square - sum_of_x*sum_of_x); 
				for(int m = j; m<=k ; m++){
					errors[j][k] += calculate_error(slope_of_best_fit,intercept_of_best_fit,values[m]);
				}
			}
			else{
				errors[j][j] = 0;
			}
		}
	}

	double answer[values.size()];
	answer[0] = 0;
	for(int i=1;i<values.size();i++){
		answer[i] =  std::numeric_limits<double>::max() ;
	}
	for (int j = 1;j < values.size() ;j++){
		for(int i=1; i <= j; i++ ){
			answer[i]=std::min(errors[i][j] + LINE_COST + answer[i-1],answer[i]);
		}
	}
	std::cout<<"The answer is "<<answer[values.size()-1]<<std::endl;
	return 0;
}


