#pragma once
#include <string>
#include <vector>
#include "Def.h"
class IndexManager {
private:

public:
	int test();
	void dropIndex(std::string tableName, std::string attrName);

	void addIndex(std::string tableName, std::string attrName, int64 fileAddress);
	void addIndex(std::string tableName, std::string attrName, std::vector<int64> fileAddresses);
	
	std::vector<int64> selectManyIndexByCondition(std::string TableName, condition cond);
	std::vector<int64> selectManyIndexByCondition(std::string TableName, std::vector<condition> cond);

	void removeIndexByCondition(std::string TableName, condition cond);
	void removeIndexByCondition(std::string TableName, std::vector<condition> cond);
};