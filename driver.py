import hardcode_params
import numpy as np
import os
import matplotlib.pyplot as plt

def read_data():
	data = []
	with open(hardcode_params.path,"r") as file_handle:
		for line in file_handle:
			line = line.strip() # remove trailing whitespaces
			parts = line.split(hardcode_params.delim)
			if(len(parts)==2):
				x = float(parts[0])
				y = float(parts[1])
				row = np.array([x,y])
			else:
				raise ValueError('coordinates can only have two parts!!')
			data += [row]
	
	data = np.array(data)
	return data

def show_fig():
	with open(hardcode_params.lines_path,"r") as f:
		slopes = []
		intercepts = []
		table = {}
		intersections = []
		lines = f.readlines()
		for line in lines:
			data = line.strip()
			
			indices = data.split(hardcode_params.index_and_slope_delim)[0]
			slope_and_intercept = data.split(hardcode_params.index_and_slope_delim)[1].split(hardcode_params.slope_and_intercept_delim)
			indices = [int(indices.split(hardcode_params.delim)[0]),int(indices.split(hardcode_params.delim)[1])]
			slopes.append(float(slope_and_intercept[0]))
			intercepts.append(float(slope_and_intercept[1]))
			table[indices[0]] = indices[1] 
		
		# calculate interseciton points
		intersections.append(np.array([0,intercepts[0]]))
		solution_lines = []
		index = len(table) -1 
		while index >= 0:
			print(index)
			solution_lines.append((slopes[index],intercepts[index]))
			index = table[index] - 1 
		print(solution_lines)

	# pass

def driver():
	# run the c++ code
	# get the data
	# run the visualization
	line_error = float(input("Enter the value for the line cost to be used\n"))
	os.system(str('bash script.sh '+str(line_error)))
	show_fig()

def main():
	data = read_data()
	driver()

if __name__ == "__main__":
	main()