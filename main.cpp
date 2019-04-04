/*! \mainpage Finding Multiple Lines of Best Fit
 *
 * \section intro Introduction
 *
 * The objective of this code is to run a dynamic programming algorithm so as to find multiple lines of best fit so as to find the number of lines of best fit.
 * 
 * Here we have made use of three algorithms:
 * 	- Graham Scan
 * 	- Jarvis March
 * 	- Kirk-Patrick Sidele Algorithm
 * \section install Installation
 *	There are two folders
 *   - Refactored Code
 *   - Vizard_Vizon
 *
 * The first contains the optimized code for testing the run time of each the second contains the additional code for visualization
 * \subsection step1 Testing the performance:
 * Navigate to the Refactored code folder.<br>
 * To test the performance run the command-<br>
 * <b>bash script</b><br>
 * Take user input from the terminal.
 * The performace for each will be displayed on the terminal output.<br>
 * <b>Note: This currently supports up to 10^7 data points</b>
 * \subsection step2 Testing the Visualization:
 * Navigate to the Vizard_Vizon folder.<br>
 * To test the performance run the command-<br>
 * <b>bash script</b><br>
 * Take user input from the terminal.<br>
 * After the execution is complete, there will be an animated plot of the working depending on the option that has been taken.<br>
 * In addition, there will be gifs generated, so that we do not have to run the algorithm one more time.<br>
 * \subsection step3 Conclusions:
 * Jarvis march performs better on an average, however, the difference between them is not significant, in the sense that they both run in the same order of time.<br>
 * However, Kirkpartik-Sidel does not seem to scale up to that factor due to the fact that the use of vectors is not efficient due to the large number of memory operations.
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "node.h"
#include "data.h"
#include "edge.h"
#include "line_cost.h"
#define LINES_LOCATION "data/lines.txt"
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

	std::fstream file_handle;
	file_handle.open(LINES_LOCATION,std::ios::out);
	if(file_handle.is_open()){
		Edge temp = Edge(values[0],values[1]); // default line
		for (int j = 1;j < values.size() ;j++){
			for(int i=0; i <= j; i++ ){
				if(i ==0 ){
					answer[j]=std::min(errors[i][j] + LINE_COST ,answer[j]); // As we try from the starting point, the line goes from the start to the current point
					temp = Edge(values[i],values[j]);
				}
				else{
					if(answer[j]>std::min(errors[i][j] + LINE_COST + answer[i-1],answer[j])){
						answer[j]= errors[i][j] + LINE_COST + answer[i-1];
						temp = Edge(values[i],values[j]);
					}
				} // The minimum of all the points up to now, so that we take the minimum of drawing a new line vs adding it to an existing line
			}
			file_handle << temp.to_string()<< std::endl;
		}
		std::cout<<"The answer is "<<answer[values.size()-1]<<std::endl;
	}
	else{
		std::cout << "the location for storing the lines is not found\n";
	}
	return 0;
}


