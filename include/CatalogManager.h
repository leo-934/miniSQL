#pragma once
#include <string>
#include <set>
#include <map>
#include <vector>
#include "def.h"

class CatalogManager {
private:
	std::map<std::string, std::map<std::string, catalog> > catas;
	std::map<std::string,std::map<std::string, int> > attrLenForChars;
	std::map<std::string, std::string> primaryKeys;//若没有，置为空字符串
	std::map<std::string, std::vector<std::string> > uniqueKeys;//若没有，size置为0
public:
	int test();
	/// <summary>
	/// Initializes a new instance of the <see cref="CatalogManager"/> class.
	/// </summary>
	CatalogManager();
	/// <summary>
	/// Closes this instance.
	/// </summary>
	void close();
	/// <summary>
	/// Gets the attribute's cata.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="attrName">Name of the attribute.</param>
	/// <returns></returns>
	catalog getCataByAttrName(std::string tableName, std::string attrName);

	///// <summary>
	///// Gets the number of table's record.
	///// </summary>
	///// <param name="tableName">Name of the table.</param>
	///// <returns></returns>
	//int getTableRecordNum(std::string tableName);

	///// <summary>
	///// Gets the number of table's block.
	///// </summary>
	///// <param name="tableName">Name of the table.</param>
	///// <returns></returns>
	//int getTableBlockNum(std::string tableName);
	
	std::vector<std::string> getAllTableNames();
	std::vector<std::string> getAllAttrByTableName(std::string tableName);
	void createTable(CreateTableSentence sent);
	void dropTable(std::string tableName);
};
