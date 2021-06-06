#include "IndexManager.h"

int IndexManager::test()
{
	return 1;
}

void IndexManager::dropIndex(std::string tableName, std::string attrName)
{
}

void IndexManager::addIndex(std::string tableName, std::string attrName, int64 fileAddress)
{
}

void IndexManager::addIndex(std::string tableName, std::string attrName, std::vector<int64> fileAddresses)
{
}

std::vector<int64> IndexManager::selectManyIndexByCondition(std::string TableName, condition cond)
{
	return std::vector<int64>();
}

std::vector<int64> IndexManager::selectManyIndexByCondition(std::string TableName, std::vector<condition> cond)
{
	return std::vector<int64>();
}

void IndexManager::removeIndexByCondition(std::string TableName, condition cond)
{
}

void IndexManager::removeIndexByCondition(std::string TableName, std::vector<condition> cond)
{
}
