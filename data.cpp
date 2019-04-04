#include "data.h"
/**
 * @brief 
 * The default file path for the dataset
 */
const std::string Data::DEFAULT_PATH = "./data/DataPoints.txt";
/**
 * @brief 
 * The default delimiter used within the dataset
 */
const std::string Data::DEFAULT_DELIM = ",";
/**
 * @brief 
 * The default location of the attempts used to find the line of best fit.
 */
const std::string Data::LINES_LOCATION = "data/lines.txt";
/**
 * @brief Construct a new Data:: Data object
 * The default constructor which makes use of the default path and the defult delimiter
 */
Data::Data(){
	this->path = DEFAULT_PATH;
	this->delim = DEFAULT_DELIM;
	file_handle.open(LINES_LOCATION,std::ios::out);
}

/**
 * @brief Construct a new Data:: Data object
 * This creates a handle that extracts data from a user defined location.
 * @param path 
 * The path to the dataset
 * @param delim 
 * The delimiter used within the dataset
 */
Data::Data(std::string path,std::string delim){
	this->path = path;
	this->delim = delim; 
	file_handle.open(LINES_LOCATION,std::ios::out);
}
/**
 * @brief 
 * This function helps split a string according  to a delimiter
 * @param str 
 * The input string
 * @param delim 
 * The delimiter used to delimit parts within the string
 * @return std::vector<std::string> 
 */
std::vector<std::string> Data::split(const char *str, char delim )
{
    std::vector<std::string> result;

    do
    {
        const char *begin = str;

        while(*str != delim && *str)
            str++;

        result.push_back(std::string(begin, str));
    } while (0 != *str++); // First check then update

    return result;
}

/**std::fstream file_handle;
	file_handle.open(LINES_LOCATION,std::ios::out);
 * @brief 
 * This function reads the data in the path defined within the constructor
 * @return std::vector<Node> 
 */
std::vector<Node> Data::read_data(){
	std::fstream file_handle;
	file_handle.open(path,std::ios::in);

	std::vector<Node> values;

	if(file_handle.is_open()){
		std::cout<<"File found, extracting the data\n";

		std::string line;
		while(std::getline(file_handle,line)){
			std::vector<std::string> temp = split(line.c_str(),delim.at(0));
			char* term;
			double x = strtod(temp[0].c_str(),&term);
			if(*term!=0){
				std::cout<<"Not a double\n";
				exit(EXIT_FAILURE);
			}
			double y = strtod(temp[1].c_str(),&term);
			if(*term!=0){
				std::cout<<"Not a double\n";
				exit(EXIT_FAILURE);
			}
			Node temp_node = Node(x,y);
			values.push_back(temp_node);
		}
		std::cout<<"Data extracted successfully\n";
	}
	else{
		std::cout<<"The file is not found, check the path name\n";
		exit(EXIT_FAILURE);
	}
	return values;
}

void Data::write_tries(std::string input){
	if(this->file_handle.is_open()){
		this->file_handle << input << '\n' ;
	}
	else{
		std::cout<<"Unable to find the file lines.txt, in the data file. HINT:Define the data folder\n";
		exit(EXIT_FAILURE);
	}
}