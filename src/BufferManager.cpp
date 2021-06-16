#include <exception>
#include <fstream>
#include "BufferManager.h"
int64 BufferManager::getBlockNum(std::string tableName)
{
	if (blockNum.find(tableName) == blockNum.end()) throw std::exception("no such table");
	return blockNum.find(tableName)->second;
}

DataBlock& BufferManager::refBlockByLabel(std::string tableName, int64 blockSerial)
{
	return buffer[{ tableName, blockSerial }];
}

void BufferManager::insertBlock(std::string tableName, int64 blockSerial, DataBlock d)
{
	buffer.insert(std::map<blockLabel, DataBlock>::value_type({ tableName,blockSerial }, d));
}

int64 BufferManager::getRecordNum(std::string tableName)
{
	if (recordNum.find(tableName) == recordNum.end()) throw std::exception("no such table");
	return recordNum.find(tableName)->second;
}

int BufferManager::test()
{
	return 1;
}

BufferManager::BufferManager(std::shared_ptr<CatalogManager> ptr)
{
	catalogManager = ptr;
}

int64 BufferManager::insertRecordToTable(std::string tableName, anyVec values)
{
	if (tableNames.find(tableName) == tableNames.end()) throw std::exception("no such table");
	int blockSerialToInsert = blockNum[tableName]-1;
	if(blockSerialToInsert==-1|| refBlockByLabel(tableName, blockSerialToInsert).isAbleToAdd()==false) {
		DataBlock d(catalogManager->getCataInAnyVec(tableName));
		d.addRecord(values);
		insertBlock(tableName,blockSerialToInsert + 1, d);
		blockNum[tableName]++;
		recordNum[tableName]++;
		return (blockNum[tableName] - 1) * d.getRecordMax() + d.getRecordNum() - 1;
	}
	else {
		refBlockByLabel(tableName, blockSerialToInsert).addRecord(values);
		auto d = refBlockByLabel(tableName, blockSerialToInsert);
		return (blockNum[tableName] - 1) * d.getRecordMax() + d.getRecordNum() - 1;
	}
}

anyVec BufferManager::getRecordByAddress(std::string tableName, int64 addresses)
{
	if (addresses >= recordNum[tableName]) throw std::exception("address out of bound");
	auto blockTmp = refBlockByLabel(tableName, 0);
	int64 blockSerial = (addresses) / (blockTmp.getRecordMax());
	int64 recordSerialInBlock = (addresses) % (blockTmp.getRecordMax());
	return refBlockByLabel(tableName, blockSerial).getRecord(recordSerialInBlock);
}

void BufferManager::deleteRecordByAddress(std::string tableName, int64 addresses)
{
	if (addresses >= recordNum[tableName]) throw std::exception("address out of bound");
	auto blockTmp = refBlockByLabel(tableName, 0);
	int64 blockSerial = (addresses) / (blockTmp.getRecordMax());
	int64 recordSerialInBlock = (addresses) % (blockTmp.getRecordMax());
	refBlockByLabel(tableName, blockSerial).removeRecord(recordSerialInBlock);
	recordNum[tableName]--;
	return;
}

void BufferManager::createTable(std::string tableName)
{
	std::ofstream fs(tableName + ".bin", std::ofstream::out);
	fs.close();
}

void BufferManager::dropTable(std::string tableName)
{

}
