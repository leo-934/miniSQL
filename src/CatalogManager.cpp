#include "..\include\CatalogManager.h"

int CatalogManager::test()
{
	return 1;
}

catalog CatalogManager::getTableAttrCata(std::string tableName, std::string attrName)
{
	return catalog();
}

int CatalogManager::getTableRecordNum(std::string tableName)
{
	return 0;
}

int CatalogManager::getTableBlockNum(std::string tableName)
{
	return 0;
}

void CatalogManager::createTable(CreateTableSentence sent)
{
}
