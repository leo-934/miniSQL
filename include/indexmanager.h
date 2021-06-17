#pragma once
#include <string>
#include <vector>
#include <map>
#include "bplustree.h"
#include "indexinfo.h"
using namespace std;
/// <summary>
/// 返回值为vector的函数，如果没有什么可以返回的，就返回一个size为0的vector
/// 返回值为string的函数，如果没有什么可以返回的，就返回空字符串""。
/// </summary>
class IndexManager {
public:
	
	int static const FLOAT = 0;
	int static const INT = -1;
	
	struct keytmp {
		int inttmp;
		float floattmp;
		string stringtmp;
	}tmp;
	
	map<int, IndexInfo*> indexmap;
	
	int getdegree(int type);
	int getkeysize(int type);
		
public:


	int test();

	/// <summary>
	/// 开启数据库时调用，将所有index读入
	/// </summary>
	IndexManager(std::string tableName);
	/// <summary>
	///	关闭数据库时候调用，将所有index写入文件
	/// </summary>
	void close();
	
	int writeintoBuffer();
	
	void setkey(int type, string key);
	
	int getkeysize(int type);
	
	void* getindex(string indexName);

	/// <summary>
	/// 为指定表的指定属性创建一个名为indexName的索引。若这个表已经有索引，则为聚集索引，若没有，则为辅助索引。
	/// </summary>
	/// <param name="indexName">Name of the index.</param>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="attrName">Name of the attribute.</param>
    void* createIndex(std::string indexName, std::string tableName, std::string attrName, int type);
	/// <summary>
	/// 删除掉指定表的叫做指定索引名的索引
	/// </summary>
	/// <param name="indexName">Name of the index.</param>
	/// <param name="tableName">Name of the table.</param>
	void dropIndex(std::string indexName);
	/// <summary>
	/// 删除掉指定表的所有索引
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	void dropAllIndex();

	void insertToIndex(std::string indexName,std::string key, int64 fileAddresses, int type);
	
	std::vector<int64> selectIndexsByCondition(std::string TableName, std::string indexName, std::vector<condition> cond);

	/// <summary>
	/// Removes all index by address.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="addresses">The addresses.</param>
	void removeAllIndexByAddress(std::string tableName, std::vector<int64> addresses);
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
