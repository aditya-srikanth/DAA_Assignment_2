#ifndef DATA 
#define DATA

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "node.h"
/**
 * @brief 
 * Data contains all the functionality to deal with the input dataset
 */
class Data{
	private:
	std::string path;
	std::string delim;
	std::fstream file_handle;
	public:
	static const std::string DEFAULT_PATH;
	static const std::string DEFAULT_DELIM;
	static const std::string LINES_LOCATION; 
	Data(std::string path,std::string delim);
	Data();
	std::vector<std::string> split(const char*, char);
	std::vector<Node> read_data();
	void write_tries(std::string);
};

#endif