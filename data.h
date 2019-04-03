#ifdef DATA 
#define DATA

#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "node.h"
class Data{
	private:
	std::string path;
	std::string delim;
	public:
	static const std::string DEFAULT_PATH;
	static const std::string DEFAULT_DELIM;
	Data(std::string path,std::delim);
	Data();
	std::vector<std::string> split(const char*, char);
	std::vector<Node> read_data();
};

#endif