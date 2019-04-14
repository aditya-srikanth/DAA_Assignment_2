/*! \mainpage Finding Multiple Lines of Best Fit
 *
 * \section intro Introduction
 *
 * The objective of this code is to run a dynamic programming algorithm so as to find multiple lines of best fit so as to find the number of lines of best fit.
 * 
 * The driver.py python file is responsible for running the entire execution. On invoking this function, it in turn invokes the C++ executable through a bash script.
 * The bash file in turn is responsible for recompilation and invoking the newly created executable after compilation.
 * \section install Installation
 * 
 * There are two python dependencies for the visualization
 * 	- matplotlib for graphing
 * 	- numpy for the dataprocessing<br/><br/>
 *
 * <strong> Run the requirements.sh file to install all dependencies </strong>
 * \subsection step1 Running the Program:
 * 	- python3 driver.py
 * 	- enter the number of data points for the graph <strong> Not more than 386 due to memory constrains on large arrays </strong>
 * 	- enter the cost of each line.<br/><br/> 
 * 
 * <strong> Each input is given in the Comman Line Interface </strong>
 * 
 * \subsection step3 Conclusions:
 * We are able to run the algorithm in <strong> O(n^3) </strong>. However, we cannot run very large values due to the fact that the array of edges required for the visualization occupies too much memory.
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "node.h"
#include "data.h"
#include "edge.h"
#include <string.h>

double calculate_error(double slope,double intercept,Node point){
	double predict = slope * point.getX() + intercept;
	double dev = predict - point.getY();
	return dev*dev;
}
double calculate_error_for_special_cases(double start_x,Node point){
	double dev = start_x - point.getX();
	return dev*dev;
}

int main(int argc,char** argv){
	double LINE_COST;
	if(argc == 2){
		char* term;
		LINE_COST = strtod(argv[1],&term);
		if(*term!=0){
			std::cout<<"Not a double\n";
			exit(EXIT_FAILURE);
		}
	}
	else{
		std::cout<<"Incorrect number of arguments\n";
		exit(EXIT_FAILURE);
	}
	
	
	Data data; // default cnstr, so use default locations
	std::vector<Node> values = data.read_data();
	// TODO
	//Algorithm comes here
	double slope_of_best_fit,intercept_of_best_fit,sum_of_x,sum_of_y,sum_of_x_square,sum_of_xy;
	double errors[values.size()][values.size()];
	memset(errors,0,sizeof(errors));
	Edge edges[values.size()][values.size()];
	
	for(int k = 0; k < values.size() ; k++){ //Loop for the end point
		for(int j = 0; j <= k;j++){ // loop for the start
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
					double average_x = sum_of_x/(k-j+1); 
					for(int m = j; m<=k ; m++){
						errors[j][k] += calculate_error_for_special_cases(average_x,values[m]);
					}
					
					std::cout<<"The error is "<<j<<' '<<k<<' '<<errors[j][k]<<"\n";
					edges[j][k]=Edge(slope_of_best_fit,average_x,values[j].getY(),values[k].getY());
				}
				else{
					slope_of_best_fit = ( (k-j+1)*sum_of_xy - sum_of_x*sum_of_y ) / ( (k-j+1)*sum_of_x_square - sum_of_x*sum_of_x); 
					intercept_of_best_fit = (sum_of_y - sum_of_x*slope_of_best_fit)/(k-j+1);
					for(int m = j; m<=k ; m++){
						errors[j][k] += calculate_error(slope_of_best_fit,intercept_of_best_fit,values[m]);
					}
					std::cout<<"The error is "<<j<<' '<<k<<' '<<errors[j][k]<<"\n";
					edges[j][k]=Edge(slope_of_best_fit,intercept_of_best_fit,values[j],values[k]);
				}
			}
			else{
				errors[j][j] = 0;
				std::cout<<"The error is "<<j<<' '<<j<<' '<<errors[j][j]<<"\n";
			}
		}
	}

	double answer[values.size()];
	answer[0] = LINE_COST;
	for(int i=1;i<values.size();i++){
		answer[i] =  std::numeric_limits<double>::max() ;
	}

	int previous = 0;

	for (int j = 1;j < values.size() ;j++){
		for(int i=0; i < j; i++ ){
			if(i == 0 ){
				answer[j]=std::min(errors[i][j] + LINE_COST ,answer[j]); // As we try from the starting point, the line goes from the start to the current point
				previous = 0;
				std::cout<<"starting with "<<i<<" "<<j<<" "<<answer[j]<<"\n";
			}
			else{//TODO handle intersection of the lines.
				if(answer[j] > errors[i][j] + LINE_COST + answer[i-1]){
					answer[j]= errors[i][j] + LINE_COST + answer[i-1];
					previous = i;
					std::cout<<"updated to "<<i<<" "<<j<<" "<<answer[j]<<"\n";
				}
			} // The minimum of all the points up to now, so that we take the minimum of drawing a new line vs adding it to an existing line
		}	
		data.write_tries(edges[previous][j].to_string(j,previous));
	}
	char temp[30];
	sprintf(temp,"lim;%lf:%lf",data.get_extrema().first,data.get_extrema().second);
	std::string limits = temp;
	data.write_tries(temp);

	std::cout<<"The answer is "<<answer[values.size()-1]<<std::endl;
	return 0;
}


