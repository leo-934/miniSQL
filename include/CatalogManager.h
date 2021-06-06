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

	/// <summary>
	/// Determines whether [has clustered index] [the specified table name].
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <returns>
	///   <c>true</c> if [has clustered index] [the specified table name]; otherwise, <c>false</c>.
	/// </returns>
	bool hasClusteredIndex(std::string tableName);

	/// <summary>
	/// Gets the index of the clustered.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <returns></returns>
	std::string getClusteredIndex(std::string tableName);

	/// <summary>
	/// Determines whether [has non clustered index] [the specified table name].
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <returns>
	///   <c>true</c> if [has non clustered index] [the specified table name]; otherwise, <c>false</c>.
	/// </returns>
	bool hasNonClusteredIndex(std::string tableName);

	/// <summary>
	/// Gets the index of the non clustered.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <returns></returns>
	std::vector<std::string> getNonClusteredIndex(std::string tableName);

	
};
