#include <fstream>
#include "RecordManager.h"

bool RecordManager::judgeCondition(std::string tableName, anyVec record, condition cond)
{
	std::string attrName = cond.attrName;
	auto cataVec = catalogManager->getAllAttrByTableName(tableName);
	int index = 0;
	for (; index < cataVec.size(); index++) {
		if (cataVec[index] == attrName) break;
	}
	judger myjudger(cond);
	return myjudger(record[index]);
}

int RecordManager::test()
{
	return 1;
}

RecordManager::RecordManager(std::shared_ptr<BufferManager> ptr1, std::shared_ptr<CatalogManager> ptr2)
{
	bufferManager = ptr1;
	catalogManager = ptr2;
}	

int64 RecordManager::insertRecordToTable(std::string tableName, anyVec values)
{
	bufferManager->insertRecordToTable(tableName, values);
	
}

std::vector<int64> RecordManager::removeRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds)
{
	std::vector<int64> res;
	for (auto i : addresses) {
		auto record=bufferManager->getRecordByAddress(tableName,i);
		bool isSatisfied = true;
		for (auto j : conds) {
			if (judgeCondition(tableName, record, j) == false) {
				isSatisfied = false;
				break;
			}
		}
		if (isSatisfied) res.push_back(i);
	}
	for (auto i : res)
		bufferManager->deleteRecordByAddress(tableName, i);

	return res;
}

std::vector<anyVec> RecordManager::selectRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds)
{
	std::vector<anyVec> res;
	for (auto i : addresses) {
		auto record = bufferManager->getRecordByAddress(tableName, i);
		bool isSatisfied = true;
		for (auto j : conds) {
			if (judgeCondition(tableName, record, j) == false) {
				isSatisfied = false;
				break;
			}
		}
		if (isSatisfied) res.push_back(record);
	}
	return res;
}
