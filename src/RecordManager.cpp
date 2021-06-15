#include <fstream>
#include "RecordManager.h"

int RecordManager::test()
{
	return 1;
}

int64 RecordManager::insertRecordToTable(std::string tableName, anyVec values)
{
	return int64();
}

std::vector<int64> RecordManager::removeRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds)
{
	return std::vector<int64>();
}

std::vector<std::string> RecordManager::selectRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds)
{
	return std::vector<std::string>();
}
