#pragma once

#include <string>
#include <fstream>
#include <sstream>

class FileHelper
{
public:
	static std::string loadFile(std::string path)
	{
		std::ifstream file(path.c_str(), std::fstream::in);

		if (file.is_open())
		{
			std::stringstream buffer;
			buffer << file.rdbuf();
			file.close();

			return buffer.str();
		}
		else throw std::runtime_error("File at " + path + " coult not be opened.");
	}

private:
	FileHelper()
	{

	}
};