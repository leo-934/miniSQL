#include <exception>
#include <fstream>
#include <map>
#include "Def.h"
#include "CatalogManager.h"
int CatalogManager::test()
{
	return 1;
}

CatalogManager::CatalogManager()//待测试
{
	std::ifstream fs;
	fs.open("catas.bin", std::fstream::in);
	if (!fs) {
		//
		return;
	}
	while (1) {
		std::string tableName;
		fs >> tableName;
		if (fs.eof()) break;
		int attrNum;
		fs >> attrNum;
		std::map<std::string, catalog> attrs;
		for (int i = 0; i < attrNum; ++i) {
			std::string attrName;
			int cata;
			fs >> attrName;
			fs >> cata;
			attrs.insert(std::map<std::string, catalog>::value_type(attrName, static_cast<catalog>(cata)));
		}
		catas.insert(std::map< std::string, std::map<std::string, catalog> >::value_type(tableName, attrs));
	}
}

void CatalogManager::close()//待测试
{
	std::ofstream fs("catas.bin", std::fstream::out);
	for (auto i : catas) {
		fs << i.first << " " << i.second.size()<<" ";
		for (auto j : i.second) {
			fs << j.first<<" "<< static_cast<std::underlying_type_t<catalog>>(j.second)<<" ";
		}
	}
}

catalog CatalogManager::getCataByAttrName(std::string tableName, std::string attrName)
{
	auto tmp = catas.find(tableName);
	if (tmp == catas.end()) throw std::exception("no this table");
	auto res = tmp->second.find(attrName);
	if(res==tmp->second.end()) throw std::exception("no this attr");
	return res->second;
}

//int CatalogManager::getTableRecordNum(std::string tableName)
//{
//	return 0;
//}
//
//int CatalogManager::getTableBlockNum(std::string tableName)
//{
//	return 0;
//}

std::vector<std::string> CatalogManager::getAllTableNames()
{
	std::vector<std::string> res;
	for (auto i : catas) res.push_back(i.first);
	return res;
}

std::vector<std::string> CatalogManager::getAllAttrByTableName(std::string tableName)
{
	std::vector<std::string> res;
	if(catas.find(tableName)==catas.end()) throw std::exception("no this table");
	for (auto i : catas[tableName]) res.push_back(i.first);
}

void CatalogManager::createTable(CreateTableSentence sent)
{
	catas.insert(std::map< std::string, std::map<std::string, catalog> >::value_type(sent.tableName, sent.attrCata));
	attrLenForChars.insert(std::map<std::string, std::map<std::string, int> >::value_type(sent.tableName, sent.attrLenForChar));
	primaryKeys.insert(std::map<std::string, std::string>::value_type(sent.tableName, sent.primaryKey));
	uniqueKeys.insert(std::map<std::string, std::vector<std::string> >::value_type(sent.tableName, sent.uniqueKeys));
}

void CatalogManager::dropTable(std::string tableName)
{
	catas.erase(catas.find(tableName));
	attrLenForChars.erase(attrLenForChars.find(tableName));
	primaryKeys.erase(primaryKeys.find(tableName));
	uniqueKeys.erase(uniqueKeys.find(tableName));
}
