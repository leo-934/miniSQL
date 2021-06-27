#include <exception>
#include <climits>
#include <fstream>
#include <iostream>
#include "BufferManager.h"
#include "Def.h"
int64 BufferManager::nextOrder = 0;
int64 BufferManager::getBlockNum(std::string tableName)
{
	if (blockNum.find(tableName) == blockNum.end()) throw std::exception("no such table");
	return blockNum.find(tableName)->second;
}

void BufferManager::removeLRUBlock()
{
	int64 lru = ULLONG_MAX;
	std::map<blockLabel, DataBlock>::iterator lruIter;
	for (auto iter = buffer.begin(); iter != buffer.end(); iter++) {
		if (iter->first.useOrder < lru) {
			lru = iter->first.useOrder;
			lruIter = iter;
		}
	}
	
	
	if (lruIter->first.blockSerial == 64) {
		//std::cout << "64tobug";
	}
	fsMap[lruIter->first.tableName]->seekp(lruIter->first.blockSerial * blockSpace, std::fstream::beg);
	/*if (fs1.failbit) {
		auto word = fs1.rdstate();
	}*/
	/*if (lruIter->first.blockSerial == 0)
		std::cout << "0tobug";*/
	lruIter->second.toFile(*fsMap[lruIter->first.tableName]);
	buffer.erase(lruIter);
	
	//fs1.close();
}

DataBlock& BufferManager::refBlockByLabel(std::string tableName, int64 blockSerial)
{
	if (buffer.find(blockLabel(tableName,blockSerial,0))!=buffer.end())
		return buffer[blockLabel(tableName, blockSerial, 0)];
	else {
		if (buffer.size() >= bufferMaxSize) {
			removeLRUBlock();
		}
		DataBlock d(catalogManager->getCataInAnyVec(tableName));
		//std::ifstream fs(tableName + ".bin", std::ifstream::binary | std::ifstream::in);
		fsMap[tableName]->seekg(blockSerial * blockSpace, std::fstream::beg);
		/*if (blockSerial == 0)
			std::cout << "0frombug";*/
		d.fromFile(*fsMap[tableName]);
		//fs.close();
		buffer.insert(std::map<blockLabel, DataBlock>::value_type(blockLabel(tableName, blockSerial, nextOrder), d));
		nextOrder++;
		return buffer[blockLabel(tableName, blockSerial, 0)];
	}
}
void BufferManager::insertBlock(std::string tableName, int64 blockSerial, DataBlock d)
{
	if (buffer.size() >= bufferMaxSize) removeLRUBlock();
	buffer.insert(std::map<blockLabel, DataBlock>::value_type(blockLabel(tableName, blockSerial, nextOrder), d));
	nextOrder++;

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
	std::ifstream fs("bufferManager.bin", std::ifstream::in);
	int blockNumSize;
	fs >> blockNumSize;
	for (int i = 0; i < blockNumSize; i++) {
		std::string f;
		int64 s;
		fs >> f >> s;
		blockNum.insert(std::map<std::string, int64>::value_type(f, s));
	}
	int recordNumSize;
	fs >> recordNumSize;
	for (int i = 0; i < recordNumSize; i++) {
		std::string f;
		int64 s;
		fs >> f >> s;
		recordNum.insert(std::map<std::string, int64>::value_type(f, s));
	}
	int totalInsertSize;
	fs >> totalInsertSize;
	for (int i = 0; i < totalInsertSize; i++) {
		std::string f;
		int64 s;
		fs >> f >> s;
		totalInsertNum.insert(std::map<std::string, int64>::value_type(f, s));
	}
	int tableNameSize;
	fs >> tableNameSize;
	for (int i = 0; i < tableNameSize; i++) {
		std::string f;
		fs >> f;
		tableNames.insert(f);
	}
	fs.close();
}

void BufferManager::close()
{
	for (auto i : buffer) {
		//std::ofstream fs(i.first.tableName + ".bin", std::ofstream::binary | std::ofstream::out);
		fsMap[i.first.tableName]->seekp(i.first.blockSerial * blockSpace, std::fstream::beg);
		i.second.toFile(*fsMap[i.first.tableName]);
		//fs.close();
	}
	std::ofstream fs("bufferManager.bin", std::ofstream::binary | std::ofstream::out);
	fs << blockNum.size() << " ";
	for (auto i : blockNum) {
		fs << i.first << " " << i.second << " ";
	}
	fs << recordNum.size() << " ";
	for (auto i : recordNum) {
		fs << i.first << " " << i.second << " ";
	}
	fs << totalInsertNum.size() << " ";
	for (auto i : totalInsertNum) {
		fs << i.first << " " << i.second << " ";
	}
	fs << tableNames.size() << " ";
	for (auto i : tableNames) {
		fs << i<<" ";
	}
	fs.close();
}

int64 BufferManager::insertRecordToTable(std::string tableName, anyVec values)
{
	if (tableNames.find(tableName) == tableNames.end()) throw std::exception("no such table");
	int blockSerialToInsert = blockNum[tableName] - 1;
	if (blockSerialToInsert == -1 || refBlockByLabel(tableName, blockSerialToInsert).isAbleToAdd() == false) {
		DataBlock d(catalogManager->getCataInAnyVec(tableName));
		d.addRecord(values);
		insertBlock(tableName, blockSerialToInsert + 1, d);
		blockNum[tableName]++;
		recordNum[tableName]++;
		totalInsertNum[tableName]++;
		return (blockNum[tableName] - 1) * d.getRecordMax() + d.getRecordNum() - 1;
	}
	else {
		refBlockByLabel(tableName, blockSerialToInsert).addRecord(values);
		auto d = refBlockByLabel(tableName, blockSerialToInsert);
		recordNum[tableName]++;
		totalInsertNum[tableName]++;
		return (blockNum[tableName] - 1) * d.getRecordMax() + d.getRecordNum() - 1;
	}
}

anyVec BufferManager::getRecordByAddress(std::string tableName, int64 addresses)
{
	if (addresses >= totalInsertNum[tableName]) throw std::exception("address out of bound");
	auto blockTmp = refBlockByLabel(tableName, 0);
	int64 blockSerial = (addresses) / (blockTmp.getRecordMax());
	int64 recordSerialInBlock = (addresses) % (blockTmp.getRecordMax());
	return refBlockByLabel(tableName, blockSerial).getRecord(recordSerialInBlock);
}

void BufferManager::deleteRecordByAddress(std::string tableName, int64 address)
{
	if (address >= totalInsertNum[tableName]) throw std::exception("address out of bound");
	auto blockTmp = refBlockByLabel(tableName, 0);
	int64 blockSerial = (address) / (blockTmp.getRecordMax());
	int64 recordSerialInBlock = (address) % (blockTmp.getRecordMax());
	refBlockByLabel(tableName, blockSerial).removeRecord(recordSerialInBlock);
	recordNum[tableName]--;
	return;
}

void BufferManager::createTable(std::string tableName)
{
	std::ofstream fstmp(tableName + ".bin",  std::ofstream::out|std::ofstream::binary);
	fstmp.close();
	auto ptr = std::make_shared<std::fstream>(tableName+".bin", std::fstream::in| std::fstream::out | std::fstream::binary);
	fsMap.insert((std::map<std::string, std::shared_ptr<std::fstream> >::value_type(tableName, ptr)));
	tableNames.insert(tableName);
}

void BufferManager::dropTable(std::string tableName)
{
	for (int i = 0; i < totalInsertNum[tableName];i++) {
		deleteRecordByAddress(tableName, i);
	}
	tableNames.erase(tableName);
}

int64 BufferManager::getTotalInsertNum(std::string tableName)
{
	return totalInsertNum[tableName];
}

BufferManager::blockLabel::blockLabel(std::string _tableName, int64 _blockSerial, int64 _useOrder)
{
	tableName = _tableName;
	blockSerial = _blockSerial;
	useOrder = _useOrder;
}

bool BufferManager::blockLabel::operator<(const blockLabel& x) const
{
	if (this->tableName < x.tableName) return true;
	else if (this->tableName > x.tableName) return false;
	else return this->blockSerial < x.blockSerial;
}

//#include <exception>
//#include <fstream>
//#include "BufferManager.h"
//int64 BufferManager::getBlockNum(std::string tableName)
//{
//	if (blockNum.find(tableName) == blockNum.end()) throw std::exception("no such table");
//	return blockNum.find(tableName)->second;
//}
//
//DataBlock& BufferManager::refBlockByLabel(std::string tableName, int64 blockSerial)
//{
//	return buffer[{ tableName, blockSerial }];
//}
//
//void BufferManager::insertBlock(std::string tableName, int64 blockSerial, DataBlock d)
//{
//	buffer.insert(std::map<blockLabel, DataBlock>::value_type({ tableName,blockSerial }, d));
//}
//
//int64 BufferManager::getRecordNum(std::string tableName)
//{
//	if (recordNum.find(tableName) == recordNum.end()) throw std::exception("no such table");
//	return recordNum.find(tableName)->second;
//}
//
//int BufferManager::test()
//{
//	return 1;
//}
//
//BufferManager::BufferManager(std::shared_ptr<CatalogManager> ptr)
//{
//	catalogManager = ptr;
//}
//
//int64 BufferManager::insertRecordToTable(std::string tableName, anyVec values)
//{
//	if (tableNames.find(tableName) == tableNames.end()) throw std::exception("no such table");
//	int blockSerialToInsert = blockNum[tableName]-1;
//	if(blockSerialToInsert==-1|| refBlockByLabel(tableName, blockSerialToInsert).isAbleToAdd()==false) {
//		DataBlock d(catalogManager->getCataInAnyVec(tableName));
//		d.addRecord(values);
//		insertBlock(tableName,blockSerialToInsert + 1, d);
//		blockNum[tableName]++;
//		recordNum[tableName]++;
//		return (blockNum[tableName] - 1) * d.getRecordMax() + d.getRecordNum() - 1;
//	}
//	else {
//		refBlockByLabel(tableName, blockSerialToInsert).addRecord(values);
//		auto d = refBlockByLabel(tableName, blockSerialToInsert);
//		return (blockNum[tableName] - 1) * d.getRecordMax() + d.getRecordNum() - 1;
//	}
//}
//
//anyVec BufferManager::getRecordByAddress(std::string tableName, int64 addresses)
//{
//	if (addresses >= recordNum[tableName]) throw std::exception("address out of bound");
//	auto blockTmp = refBlockByLabel(tableName, 0);
//	int64 blockSerial = (addresses) / (blockTmp.getRecordMax());
//	int64 recordSerialInBlock = (addresses) % (blockTmp.getRecordMax());
//	return refBlockByLabel(tableName, blockSerial).getRecord(recordSerialInBlock);
//}
//
//void BufferManager::deleteRecordByAddress(std::string tableName, int64 addresses)
//{
//	if (addresses >= recordNum[tableName]) throw std::exception("address out of bound");
//	auto blockTmp = refBlockByLabel(tableName, 0);
//	int64 blockSerial = (addresses) / (blockTmp.getRecordMax());
//	int64 recordSerialInBlock = (addresses) % (blockTmp.getRecordMax());
//	refBlockByLabel(tableName, blockSerial).removeRecord(recordSerialInBlock);
//	recordNum[tableName]--;
//	return;
//}
//
//void BufferManager::createTable(std::string tableName)
//{
//	std::ofstream fs(tableName + ".bin", std::ofstream::out);
//	fs.close();
//}
//
//void BufferManager::dropTable(std::string tableName)
//{
//
//}
//
//bool BufferManager::blockLabel::operator<(const blockLabel& x) const
//{
//	if (this->tableName < x.tableName) return true;
//	else if (this->tableName > x.tableName) return false;
//	else return this->blockSerial < x.blockSerial;
//}
