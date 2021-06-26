#pragma once
#include "Def.h"
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
	std::string getword(std::string s, int *i);
	std::string getlowerword(std::string s);
public:
	std::shared_ptr<Sentence> parseSql(std::string s);	
};

class SyntaxException{};
