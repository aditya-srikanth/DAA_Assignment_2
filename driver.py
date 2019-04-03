import hardcode_params
import numpy as np
import os
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
	#TODO code for visualizer and the value for the slider to be used
	pass

def driver():
	# run the c++ code
	# get the data
	# run the visualization
	pass
def main():
	data = read_data()
	show_fig()
	driver()
if __name__ == "__main__":
	main()