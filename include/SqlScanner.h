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
	/// <summary>
	/// 返回一条语句，若返回值为空说明已经这个流已经结束。
	/// </summary>
	/// <returns></returns>
	std::string getSqlSentence();
	~SqlScanner();
};