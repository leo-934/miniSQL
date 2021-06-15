#pragma once
#include <string>
#include "Def.h"
class RecordManager {
private:

public:
	int test();
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
	std::vector<std::string> selectRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds);
};