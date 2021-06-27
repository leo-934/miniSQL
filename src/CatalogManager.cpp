#include <exception>
#include <fstream>
#include <map>
#include <utility>
#include <iostream>
#include "CatalogManager.h"
int CatalogManager::test()
{
	return 1;
}

CatalogManager::CatalogManager()//待测试
{
	std::ifstream fs;
	fs.open("catas.bin", std::ifstream::in);
	if (!fs) {
		//
		return;
	}
	//read catas
	int catasSize;
	fs >> catasSize;
	for(int j=0;j<catasSize;++j) {
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
	//read attrLenForChars
	int aLFCSize;
	fs >> aLFCSize;
	for (int j = 0; j < aLFCSize; ++j) {
		std::string tableName;
		fs >> tableName;
		if (fs.eof()) break;
		int attrForCharNum;
		fs >> attrForCharNum;
		std::map<std::string, int> attrForChars;
		for (int i = 0; i < attrForCharNum; ++i) {
			std::string attrName;
			int len;
			fs >> attrName;
			fs >> len;
			attrForChars.insert(std::map<std::string, int>::value_type(attrName, len));
		}
		attrLenForChars.insert(std::map<std::string, std::map<std::string, int> >::value_type(tableName, attrForChars));
	}
	//read primarykeys
	int primaryKeysSize;
	fs >> primaryKeysSize;
	for (int j = 0; j < primaryKeysSize; ++j) {
		std::string tableName, pKey;
		fs >> tableName >> pKey;
		primaryKeys.insert(std::map<std::string, std::string>::value_type(tableName,pKey));
	}
	//read uniqueKeys
	int uniqueKeysSize;
	fs >> uniqueKeysSize;
	for (int j = 0; j < uniqueKeysSize; ++j) {
		std::string tableName;
		fs >> tableName;
		int uKeyNum;
		fs >> uKeyNum;
		std::vector<std::string> uKeys;
		for (int i = 0; i < uKeyNum; ++i) {
			std::string uKeyName;
			fs >> uKeyName;
			uKeys.push_back(uKeyName);
		}
		uniqueKeys.insert(std::map<std::string, std::vector<std::string> >::value_type(tableName, uKeys));
	}

	int originalAttrNamesSize;
	fs >> originalAttrNamesSize;
	for (int j = 0; j < originalAttrNamesSize; ++j) {
		std::string tableName;
		fs >> tableName;
		int attrNum;
		fs >> attrNum;
		std::vector<std::string> attrs;
		for (int i = 0; i < attrNum; ++i) {
			std::string attrName;
			fs >> attrName;
			attrs.push_back(attrName);
		}
		originalAttrNames.insert(std::map<std::string, std::vector<std::string> >::value_type(tableName, attrs));
	}
	return;
}

void CatalogManager::close()//待测试
{
	std::ofstream fs("catas.bin", std::ofstream::out);
	//write catas
	fs << catas.size() << " ";
	for (auto i : catas) {
		fs << i.first << " " << i.second.size()<<" ";
		for (auto j : i.second) {
			fs << j.first<<" "<< static_cast<std::underlying_type_t<catalog>>(j.second)<<" ";
		}
	}
	//write attrLenForChars
	fs << attrLenForChars.size() << " ";
	for (auto i : attrLenForChars) {
		fs << i.first << " " << i.second.size() << " ";
		for (auto j : i.second) {
			fs << j.first << " " << j.second << " ";
		}
	}
	//write primaryKeys
	fs << primaryKeys.size() << " ";
	for (auto i : primaryKeys) {
		fs << i.first << " " << i.second << " ";
	}
	//write uniqueKeys
	fs << uniqueKeys.size() << " ";
	for (auto i : uniqueKeys) {
		fs << i.first << " " << i.second.size() << " ";
		for (auto j : i.second) {
			fs << j << " ";
		}
	}
	fs << originalAttrNames.size() << " ";
	for (auto i : originalAttrNames) {
		fs << i.first << " " << i.second.size() << " ";
		for (auto j : i.second) {
			fs << j << " ";
		}
	}
}
std::vector<std::string> CatalogManager::getOriginalAttrNames(std::string tableName)
{
	return originalAttrNames[tableName];
}


catalog CatalogManager::getCataByAttrName(std::string tableName, std::string attrName)
{
	auto tmp = catas.find(tableName);
	if (tmp == catas.end()) throw std::exception("no this table");
	auto res = tmp->second.find(attrName);
	if (res == tmp->second.end()) {
		std::cout << "123";
		throw std::exception("no this attr");
	}
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

anyVec CatalogManager::getCataInAnyVec(std::string tableName)
{
	anyVec res;
	for (auto j : originalAttrNames[tableName]) {
		for (auto i : catas[tableName]) {
			if (i.first == j) {
				res.push_back(static_cast<catalog>(i.second));
				if (i.second == catalog::CHAR) res.push_back(static_cast<int>(attrLenForChars[tableName][i.first]));
			}
		}
	}
	/*for (auto i : catas[tableName]) {
		res.push_back(static_cast<catalog>(i.second));
		if (i.second == catalog::CHAR) res.push_back(static_cast<int>(attrLenForChars[tableName][i.first]));
	}*/
	return res;
}


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
	return res;
}

void CatalogManager::createTable(CreateTableSentence sent)
{
	originalAttrNames.insert(std::map < std::string, std::vector < std::string> > ::value_type(sent.tableName, sent.originalAttr));
	catas.insert(std::map< std::string, std::map<std::string, catalog> >::value_type(sent.tableName, sent.attrCata));
	attrLenForChars.insert(std::map<std::string, std::map<std::string, int> >::value_type(sent.tableName, sent.attrLenForChar));
	if(sent.primaryKey!=" ") primaryKeys.insert(std::map<std::string, std::string>::value_type(sent.tableName, sent.primaryKey));
	if(sent.uniqueKeys.size()!=0) uniqueKeys.insert(std::map<std::string, std::vector<std::string> >::value_type(sent.tableName, sent.uniqueKeys));
}

void CatalogManager::dropTable(std::string tableName)
{
	catas.erase(catas.find(tableName));
	attrLenForChars.erase(attrLenForChars.find(tableName));
	if (primaryKeys.find(tableName)!=primaryKeys.end()) primaryKeys.erase(primaryKeys.find(tableName));
	if (uniqueKeys.find(tableName) != uniqueKeys.end()) uniqueKeys.erase(uniqueKeys.find(tableName));
}
