#pragma once

#include <string>
#include <fstream>
#include <sstream>

static std::string io_load_file(std::string path)
{
	std::ifstream file(path.c_str(), std::fstream::in);

	if (file.is_open())
	{
		std::string line;
		std::stringstream buffer;

		while (std::getline(file, line))
		{
			buffer << line << std::endl;
		}

		file.close();

		return buffer.str();
	}
	else throw 1;
}