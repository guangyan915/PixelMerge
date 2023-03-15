#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
#include <io.h>

#include <iterator> // std::ostream_iterator
#include <sstream>	// std::istringstream
#include <cctype>	// std::isdigit


using namespace std;

class File {
private:
	fstream file_name;
	vector<string> file_name_res;
	string file_path;
	
public:
	File();
	File(string s)
		: file_path(s)
	{}
	void setFileNameRes();
	void setBatchName();
	void setFilePath(string path);
	void sortFile();
	size_t size();
	string operator [] (size_t);
	bool openDirctory(string);
	bool openDirctory();
};