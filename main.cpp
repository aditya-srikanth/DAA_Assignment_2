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
			sum_of_x = 0;
			sum_of_y = 0;
			sum_of_x_square = 0;
			sum_of_xy = 0 ;
			if(j != k){
				for(int i=j;i<=k;i++){
					sum_of_y += values[i].getY();
					sum_of_x += values[i].getX();
					sum_of_xy += values[i].getX() * values[i].getY() ;
					sum_of_x_square += values[i].getX() * values[i].getX();
				}
				if((k-j+1)*sum_of_x_square - sum_of_x*sum_of_x == 0){
					if((k-j+1)*sum_of_xy - sum_of_x*sum_of_y > 0){
						slope_of_best_fit = std::numeric_limits<double>::max() ;
					}
					else if ((k-j+1)*sum_of_xy - sum_of_x*sum_of_y < 0){
						slope_of_best_fit = - std::numeric_limits<double>::max() ;
					}// Assuming  no repeated points
					if(values[k].getX()>0){
						intercept_of_best_fit = - std::numeric_limits<double>::max() ;
					}
					else if(values[k].getX()<0){
						intercept_of_best_fit =  std::numeric_limits<double>::max() ;	
					}

				}
				else{
					slope_of_best_fit = ( (k-j+1)*sum_of_xy - sum_of_x*sum_of_y ) / ( (k-j+1)*sum_of_x_square - sum_of_x*sum_of_x); 
					intercept_of_best_fit = (sum_of_y - sum_of_x*slope_of_best_fit)/(k-j+1);
				}
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
		for(int i=0; i <= j; i++ ){
			if(i ==0 ){
				answer[j]=std::min(errors[i][j] + LINE_COST ,answer[j]);
			}
			else{
				answer[j]=std::min(errors[i][j] + LINE_COST + answer[i-1],answer[j]);
			}
		}
	}
	std::cout<<"The answer is "<<answer[values.size()-1]<<std::endl;
	return 0;
}


