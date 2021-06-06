#pragma once
#include <string>
#include <vector>
#include "def.h"

class CatalogManager {
private:
	
public:
	int test();
	/// <summary>
	/// Gets the attribute's cata.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="attrName">Name of the attribute.</param>
	/// <returns></returns>
	catalog getTableAttrCata(std::string tableName, std::string attrName);

	/// <summary>
	/// Gets the number of table's record.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <returns></returns>
	int getTableRecordNum(std::string tableName);

	/// <summary>
	/// Gets the number of table's block.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <returns></returns>
	int getTableBlockNum(std::string tableName);

	
	void addTableCata(CreateTableSentence sent);
};
