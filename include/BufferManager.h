#pragma once
#include <string>
#include <vector>
#include <set>
#include <memory>
#include "DataBlock.h"
#include "CatalogManager.h"
#include "Def.h"
class BufferManager {
private:
	std::shared_ptr<CatalogManager> catalogManager;

	struct blockLabel{
		std::string tableName;
		int64 blockSerial;//从0开始
		bool operator <(blockLabel x) {
			if (this->tableName < x.tableName) return true;
			else if (this->tableName > x.tableName) return false;
			else return this->blockSerial < x.blockSerial;
		}
	};
	std::map<blockLabel, DataBlock> buffer;
	std::map<std::string, int64> blockNum;
	std::map<std::string, int64> recordNum;
	std::set<std::string> tableNames;
	int64 getBlockNum(std::string tableName);
	
	/// <summary>
	/// 代理引用buffer,通过修改这个函数可以管理缓冲区
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="blockSerial">The block serial.</param>
	/// <returns></returns>
	DataBlock& refBlockByLabel(std::string tableName, int64 blockSerial);

	/// <summary>
	/// 代理插入buffer,通过修改这个函数可以管理缓冲区
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="blockSerial">The block serial.</param>
	/// <param name="d">The d.</param>
	void insertBlock(std::string tableName, int64 blockSerial, DataBlock d);

public:
	int test();
	/// <summary>
	/// Initializes a new instance of the <see cref="BufferManager"/> class.
	/// </summary>
	/// <param name="ptr">The PTR.</param>
	BufferManager(std::shared_ptr<CatalogManager> ptr);
	/// <summary>
	/// Gets the record number.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <returns></returns>
	int64 getRecordNum(std::string tableName);
	/// <summary>
	/// Inserts the record to table.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="values">The values.</param>
	/// <returns></returns>
	int64 insertRecordToTable(std::string tableName, anyVec values);
	/// <summary>
	/// Gets the record by address.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="addresses">The addresses.</param>
	/// <returns></returns>
	anyVec getRecordByAddress(std::string tableName, int64 addresses);
	/// <summary>
	/// Deletes the record by address.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="addresses">The addresses.</param>
	void deleteRecordByAddress(std::string tableName, int64 addresses);
	/// <summary>
	/// Creates the table.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	void createTable(std::string tableName);
	/// <summary>
	/// Drops the table.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	void dropTable(std::string tableName);
};