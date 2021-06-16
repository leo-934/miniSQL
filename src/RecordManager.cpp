#include <fstream>
#include "RecordManager.h"

int RecordManager::test()
{
	return 1;
}

RecordManager::RecordManager(std::shared_ptr<BufferManager> ptr)
{
	bufferManager = ptr;
}

int64 RecordManager::insertRecordToTable(std::string tableName, anyVec values)
{
	bufferManager->insertRecordToTable(tableName, anyVec);
	
}

std::vector<int64> RecordManager::removeRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds)
{
	return std::vector<int64>();
}

anyVec RecordManager::selectRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds)
{
	return anyVec();
}
