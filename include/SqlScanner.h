#pragma once
#include <iostream>
#include <fstream>
class SqlScanner {
private:
	bool isFromFile;
	std::ifstream fs;
public:
	SqlScanner();
	SqlScanner(std::string filename);
	std::string getSqlSentence();
};