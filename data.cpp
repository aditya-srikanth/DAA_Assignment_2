#include "data.h"

const std::string Data::DEFAULT_PATH = "./data/DataPoints.txt";
const std::string Data::DEFAULT_DELIM = ",";

Data::Data(){
	this->path = DEFAULT_PATH;
	this->delim = DEFAULT_DELIM;
}
Data::Data(std::string path,std::delim){
	this->path = path;
	this->delim = delim; 
}
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
vector<Node> Data::read_data(){
	fstream file_handle;
	file_handle.open(path,std::ios::in);

	std::vector<Node> values;

	if(file_handle.is_open()){
		std::cout<<"File found, extracting the data\n";

		std::string line;
		while(std::getline(file,line)){
			std::vector<std::string> temp = split(line.c_str(),delim.at(0));
			// std::cout<<temp[0]<<","<<temp[1]<<"\n";
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
