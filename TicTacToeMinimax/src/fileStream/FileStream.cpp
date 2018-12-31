#include "FileStream.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::string FileStream::ReadFileIntoString(std::string filepath)
{
	std::fstream ist{ filepath };
	if (!ist)
		std::cout << "cannot open file " << filepath << std::endl;
	ist.open(filepath);

	std::stringstream strStream;
	strStream << ist.rdbuf();
	std::string str = strStream.str();
	return strStream.str();
}
