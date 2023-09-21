#ifndef RECORDMANAGER
#define RECORDMANAGER

#include <string>
#include <memory>
#include "buffermanager.h"
#include "indexmanager.h"
class RecordManager
{
private:
	std::shared_ptr<BufferManager> bufferManager;
	std::shared_ptr<CatalogManager> catalogManager;
	std::shared_ptr<IndexManager> indexManager;

public:
	int test();

	RecordManager(std::shared_ptr<BufferManager> ptr1, std::shared_ptr<CatalogManager> ptr2, std::shared_ptr<IndexManager> ptr3);
	/// <summary>
	/// Inserts the record to table.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="values">The values.</param>
	/// <returns></returns>
	int64 insertRecordToTable(std::string tableName, anyVec values);
	/// <summary>
	/// Removes the record from table.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="addresses">The addresses.</param>
	/// <param name="conds">The conds.</param>
	/// <returns></returns>
	std::vector<int64> removeRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds);
	/// <summary>
	/// <summary>
	/// Selects the records by address and condition.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="addresses">The addresses.</param>
	/// <param name="conds">The conds.</param>
	/// <returns></returns>
	std::vector<anyVec> selectRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds);
	std::vector<int64> removeRecordsByCondition(std::string tableName, std::vector<condition> conds);
	std::vector<anyVec> selectRecordsByCondition(std::string tableName, std::vector<condition> conds);

	void addPastRecordToIndex(std::string tableName);
};

#endif