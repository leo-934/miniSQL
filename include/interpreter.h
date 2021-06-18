#pragma once
#include "def.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <sstream> 
using namespace std;

class Interpreter {
public:
	std::string getword(std::string s, int *i);
	std::shared_ptr<Sentence> parseSql(std::string s);			
};
