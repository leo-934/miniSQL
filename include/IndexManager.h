#pragma once
#include <string>
#include <vector>
#include "Def.h"
/// <summary>
/// 返回值为vector的函数，如果没有什么可以返回的，就返回一个size为0的vector
/// 返回值为string的函数，如果没有什么可以返回的，就返回空字符串""。
/// </summary>
class IndexManager {
private:

public:


	int test();

	/// <summary>
	/// 开启数据库时调用，将所有index读入文件
	/// </summary>
	IndexManager();
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
	void createIndex(std::string indexName, std::string tableName, std::string attrName);
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

	void insertCharToIndex(std::string indexName,std::string tableName,std::string value, int64 fileAddresses);
	void insertIntToIndex(std::string indexName, std::string tableName, int value, int64 fileAddress);
	void insertFloatToIndex(std::string indexName, std::string tableName, float value, int64 fileAddress);
	
	/// <summary>
	/// Inserts to index.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="values">The values.</param>
	/// <param name="fileAddresses">The file addresses.</param>
	void insertToIndex(std::string tableName, anyVec values, int64 fileAddresses);

	/// <summary>
	/// Selects the indexs by condition.
	/// </summary>
	/// <param name="TableName">Name of the table.</param>
	/// <param name="indexName">Name of the index.</param>
	/// <param name="cond">The cond.</param>
	/// <returns></returns>
	std::vector<int64> selectIndexsByCondition(std::string TableName, std::string indexName, std::vector<condition> cond);
	
	/// <summary>
	/// 删除一个表的所有索引中指向给定地址的索引项
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="addresses">The addresses.</param>
	void removeAllIndexByAddress(std::string tableName, std::vector<int64> addresses);
	//void removeIndexByCondition(std::string TableName, std::string indexName, condition cond);
	//void removeIndexByCondition(std::string TableName, std::string indexName, std::vector<condition> cond);
 
	

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
/// <summary>
/// 实现一个b+树叶节点中fileAddress的迭代器
/// </summary>
class indexIterator {

public:
	/// <summary>
	/// Initializes a new instance of the <see cref="indexIterator"/> class.
	/// </summary>
	/// <param name="tableName">Name of the table.</param>
	/// <param name="indexName">Name of the index.</param>
	indexIterator(std::string tableName, std::string indexName);
	/// <summary>
	/// 将迭代器的位置改为第i个地址的位置，下标从0开始。
	/// 比如changePlaceByIndex(0)则为第一个地址
	/// </summary>
	/// <param name="index">The index.</param>
	/// <returns></returns>
	void changePlaceByIndex(int64 i);
	/// <summary>
	/// 将迭代器的位置改为下一个元素
	/// </summary>
	/// <returns>若存在下一个元素，返回true,不存在则返回false</returns>
	bool next();

};