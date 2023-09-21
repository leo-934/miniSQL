#include "sqlscanner.h"
#include <cstdio>
SqlScanner::SqlScanner()
{
	isFromFile = false;
}

SqlScanner::SqlScanner(std::string filename)
{
	isFromFile = true;
	fs.open(filename, std::ifstream::in);
	
}

std::string SqlScanner::getSqlSentence()
{
	std::string sent;
	
	if (isFromFile) {
		char c;
		fs.get(c);
		while (c == '\n' || c == ' ') {
			fs.get(c);
			if (!fs) return std::string("");
		}
		while (!fs.eof() && c != ';') {
			sent.push_back(c);
			fs.get(c);
		}

		if (fs.eof()) {
			return std::string("");
		}
		else {
			return sent;
		}
	}
	else {
		char c;
		c = getchar();
		while (c == '\n' || c == ' ') {
			c = getchar();
			if (c == EOF) return std::string("");
		}
		while (c != EOF && c != ';') {
			sent.push_back(c);
			c = getchar();
		}
		if (c == EOF) {
			return std::string("");
		}
		else {
			return sent;
		}
		
	}
}

SqlScanner::~SqlScanner()
{
	fs.close();
}


