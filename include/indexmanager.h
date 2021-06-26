#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <map>
#include <any>
#include "indexinfo.h"
#include "CatalogManager.h"
#include "Def.h"
/// <summary>
/// 返回值为vector的函数，如果没有什么可以返回的，就返回一个size为0的vector
/// 返回值为string的函数，如果没有什么可以返回的，就返回空字符串""。
/// </summary>
class IndexManager {
private:
	
	std::map<int, IndexInfo*> indexmap;
	std::shared_ptr<CatalogManager> catalogManager;
	int getdegree(catalog type);
	int getkeysize(catalog type);


	void writeintoBuffer();

	void readfromBuffer();

	void* getindex(std::string tableName, std::string indexName);
		
public:


	int test();

	/// <summary>
	/// 开启数据库时调用，将所有index读入文件
	/// </summary>
	IndexManager(std::shared_ptr<CatalogManager> _catalogManager);
	/// <summary>
	///	关闭数据库时候调用，将所有index写入文件
	/// </summary>
	void close();

	/// <summary>
	/// 为指定表的指定属性创建一个名为indexName的索引。若这个表已经有索引，则为聚集索引，若没有，则为辅助索引。
	/// </summary>
	/// <param name="indexName">Name of the index.</param>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="attrName">Name of the attribute.</param>
    void* createIndex(std::string indexName, std::string tableName, std::string attrName);
	/// <summary>
	/// 删除掉指定表的叫做指定索引名的索引
	/// </summary>
	/// <param name="indexName">Name of the index.</param>
	/// <param name="tableName">Name of the table.</param>
	void dropIndex(std::string indexName, std::string tableName);
	/// <summary>
	/// 删除掉指定表的所有索引
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	void dropAllIndex(std::string tableName);

	void insertToIndex(std::string indexName, std::string tableName, std::any key, int64 value);
	
	std::vector<int64> selectIndexsByCondition(std::string tableName, std::string indexName, std::vector<condition> cond);

	void removeIndexByAddress(std::string tableName, std::vector<int64> addresses);
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
	/// <summary>
	/// Determines whether [has any index] [the specified table name].
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <returns>
	///   <c>true</c> if [has any index] [the specified table name]; otherwise, <c>false</c>.
	/// </returns>
	bool hasAnyIndex(std::string tableName);
	/// <summary>
	/// Gets all index.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <returns></returns>
	std::vector<std::string> getAllIndex(std::string tableName);
	
	/// <summary>
	/// Gets the name of the attribute name by index name and table name.
	/// </summary>
	/// <param name="indexName">Name of the index.</param>
	/// <param name="tableName">Name of the table.</param>
	/// <returns></returns>
	std::string getAttrNameByIndexName(std::string indexName, std::string tableName);
	/// <summary>
	/// Gets the name of the index name by attribute.
	/// </summary>
	/// <param name="attrName">Name of the attribute.</param>
	/// <param name="tableName">Name of the table.</param>
	/// <returns></returns>
	std::string getIndexNameByAttrName(std::string attrName, std::string tableName);

	//std::string getBestIndex(std::string tableName);
};
