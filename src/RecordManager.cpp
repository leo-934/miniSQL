#include <fstream>
#include "RecordManager.h"
int RecordManager::test()
{
	return 1;
}

RecordManager::RecordManager(std::shared_ptr<BufferManager> ptr1, std::shared_ptr<CatalogManager> ptr2, std::shared_ptr<IndexManager> ptr3)
{
	bufferManager = ptr1;
	catalogManager = ptr2;
	indexManager = ptr3;
}



int64 RecordManager::insertRecordToTable(std::string tableName, anyVec values)
{
	int64 res=bufferManager->insertRecordToTable(tableName, values);
	return res;
}

std::vector<int64> RecordManager::removeRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds)
{
	std::vector<int64> res;
	for (auto addr : addresses) {
		auto record = bufferManager->getRecordByAddress(tableName, addr);
		int flag = 1;
		for (auto c : conds) {
			judger myjudger(c);
			int j = 0;
			for (; j < record.size(); j++) {
				if ((catalogManager->getOriginalAttrNames(tableName))[j] == c.attrName) break;
			}
			if (myjudger(record[j]) == false) flag = 0;
		}
		if (flag) {
			res.push_back(addr);
			bufferManager->deleteRecordByAddress(tableName, addr);
		}
	}
	return res;
}

std::vector<anyVec> RecordManager::selectRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds)
{
	std::vector<anyVec> res;
	for (auto addr : addresses) {
		auto record = bufferManager->getRecordByAddress(tableName, addr);
		int flag = 1;
		for (auto c : conds) {
			judger myjudger(c);
			int j = 0;
			for (; j < record.size(); j++) {
				if ((catalogManager->getOriginalAttrNames(tableName))[j] == c.attrName) break;
			}
			if (myjudger(record[j]) == false) flag = 0;
		} 
		if (flag) res.push_back(record);
		
	}
	return res;
}

void RecordManager::addPastRecordToIndex(std::string tableName)
{
	
	auto recordNum=bufferManager->getTotalInsertNum(tableName);
	auto indexes = indexManager->getAllIndex(tableName);
	auto attrs = catalogManager->getOriginalAttrNames(tableName);
	for (int i = 0; i < recordNum; i++) {
		if (i == 1472) {
			//std::cout << "1472bug";
		}
		if (std::ofstream::failbit) {
			//std::cout << "abc";
		}
		auto record = bufferManager->getRecordByAddress(tableName, i);
		if (record.size() != 0) {
			for (auto index : indexes) {
				int j = 0;
				for (; j < attrs.size(); j++) {
					
					if (indexManager->getIndexNameByAttrName(attrs[j],tableName) == index) {
						break;
					}
				}
				indexManager->insertToIndex(index, tableName, record[j], i);
			}
		}
	}
}
