#ifndef INTERPRETER
#define INTERPRETER

#include "def.h"
#include "catalogmanager.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <exception>
#include <fstream>

class Interpreter
{
private:
	std::shared_ptr<CatalogManager> catalogManager;
	std::string getword(std::string s, int *i);
	std::string getlowerword(std::string s);

public:
	Interpreter(std::shared_ptr<CatalogManager> ptr);
	std::shared_ptr<Sentence> parseSql(std::string s);
};

class SyntaxException
{
};

#endif