#pragma once
#include <string>
#include <vector>
#include "Def.h"
class IndexManager {
private:

public:
	int test();
	void createIndex(std::string indexName, std::string tableName, std::string attrName);
	void dropIndex(std::string indexName, std::string tableName);

	void addToIndex(std::string indexName, std::string tableName, int64 fileAddress);
	void addToIndex(std::string indexName, std::string tableName, std::vector<int64> fileAddresses);
	
	std::vector<int64> selectManyIndexByCondition(std::string TableName, std::string indexName, condition cond);
	std::vector<int64> selectManyIndexByCondition(std::string TableName, std::string indexName, std::vector<condition> cond);

	void removeIndexByCondition(std::string TableName, std::string indexName, condition cond);
	void removeIndexByCondition(std::string TableName, std::string indexName, std::vector<condition> cond);
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
	/// <returns>name of index</returns>
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
	/// <returns>names of indexes</returns>
	std::vector<std::string> getNonClusteredIndex(std::string tableName);

};