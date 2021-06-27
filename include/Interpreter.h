#pragma once
#include "Def.h"
#include "CatalogManager.h"
#include <iostream>
#include <map> 
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <exception>
#include <fstream>

class Interpreter {
private:
	std::shared_ptr<CatalogManager> catalogManager;
	std::string getword(std::string s, int *i);
	std::string getlowerword(std::string s);
public:
	Interpreter(std::shared_ptr<CatalogManager> ptr);
	std::shared_ptr<Sentence> parseSql(std::string s);	
};

class SyntaxException{};
