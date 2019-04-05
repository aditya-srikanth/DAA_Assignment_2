import hardcode_params
import numpy as np
import os
import matplotlib.pyplot as plt

def read_data():
	'''
		Code to read the data from the file
	'''
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
		x_min = 0.0
		x_max = 0.0
		for line in lines:
			data = line.strip()
			if data.split(hardcode_params.index_and_slope_delim)[0] == 'lim':
				coordinates = data.split(hardcode_params.index_and_slope_delim)[1]
				coordinates = coordinates.split(hardcode_params.slope_and_intercept_delim)
				x_min = float(coordinates[0])
				x_max = float(coordinates[1])
			else:
				indices = data.split(hardcode_params.index_and_slope_delim)[0]
				slope_and_intercept = data.split(hardcode_params.index_and_slope_delim)[1].split(hardcode_params.slope_and_intercept_delim)
				indices = [int(indices.split(hardcode_params.delim)[0]),int(indices.split(hardcode_params.delim)[1])]
				slopes.append(float(slope_and_intercept[0]))
				intercepts.append(float(slope_and_intercept[1]))
				table[indices[0]] = indices[1] 
		
		# calculate interseciton points
		solution_lines = []
		index = len(table) -1

		while index >= 0:
			solution_lines.append((slopes[index],intercepts[index]))
			index = table[index + 1] - 1 

		solution_lines.reverse()

		intital_y = solution_lines[0][0]*x_min + solution_lines[0][1]
		intersections.append(np.array([x_min,intital_y]))


		for solution_lines_index in range(len(solution_lines)-1):
			slope_1 = solution_lines[solution_lines_index][0]
			slope_2 = solution_lines[solution_lines_index+1][0]
			intercept_1 = solution_lines[solution_lines_index][1]
			intercept_2 = solution_lines[solution_lines_index+1][1]

			if 	slope_1 != slope_2:
			 	A = np.array([[-slope_1,1],[-slope_2,1]])
			 	D = np.array([[intercept_1],[intercept_2]])
			 	x = np.linalg.inv(A).dot(D)
			 	intersections.append(x.flatten())

		final_y = solution_lines[-1][0]*x_max + solution_lines[-1][1]
		intersections.append(np.array([x_max,final_y]))

		plt.plot([intersection[0] for intersection in intersections],[intersection[1] for intersection in intersections],color='red')

	x_coordinates = []
	y_coordinates = []
	with open(hardcode_params.path,'r') as f:
		for line in f.readlines():
			coordinates = line.strip()
			coordinates = coordinates.split(hardcode_params.delim)
			x = float(coordinates[0])
			y = float(coordinates[1])
			x_coordinates.append(x)
			y_coordinates.append(y)
		
		plt.scatter(np.array(x_coordinates),np.array(y_coordinates))
		plt.show()

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