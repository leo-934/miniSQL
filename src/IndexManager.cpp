#include "IndexManager.h"

int IndexManager::test()
{
	return 1;
}

IndexManager::IndexManager()
{
}

void IndexManager::close()
{
}

void IndexManager::createIndex(std::string indexName, std::string tableName, std::string attrName)
{
}

void IndexManager::dropIndex(std::string indexName, std::string tableName)
{
}

void IndexManager::dropAllIndex(std::string tableName)
{
}

void IndexManager::insertCharToIndex(std::string indexName, std::string tableName, std::string value, int64 fileAddresses)
{
}

void IndexManager::insertIntToIndex(std::string indexName, std::string tableName, int value, int64 fileAddress)
{
}

void IndexManager::insertFloatToIndex(std::string indexName, std::string tableName, float value, int64 fileAddress)
{
}

//std::string IndexManager::getBestIndex(std::string tableName)
//{
//	std::string indexName;
//	if (this->hasClusteredIndex(tableName)) indexName = this->getClusteredIndex(tableName);
//	else if (this->hasNonClusteredIndex(tableName)) {
//		auto tmp = this->getNonClusteredIndex(tableName);
//		indexName = tmp[0];
//	}
//	else {
//		indexName="";
//	}
//	return indexName;
//}

void IndexManager::insertToIndex(std::string tableName, anyVec values, int64 fileAddresses)
{
	//to be written
}

std::vector<int64> IndexManager::selectIndexsByCondition(std::string TableName, std::string indexName, std::vector<condition> cond)
{
	return std::vector<int64>();
}

void IndexManager::removeAllIndexByAddress(std::string TableName, std::vector<int64> addresses)
{
}

bool IndexManager::hasClusteredIndex(std::string tableName)
{
	return false;
}

std::string IndexManager::getClusteredIndex(std::string tableName)
{
	return std::string();
}

bool IndexManager::hasNonClusteredIndex(std::string tableName)
{
	return false;
}

std::vector<std::string> IndexManager::getNonClusteredIndex(std::string tableName)
{
	return std::vector<std::string>();
}

bool IndexManager::hasAnyIndex(std::string tableName)
{
	return false;
}

std::vector<std::string> IndexManager::getAllIndex(std::string tableName)
{
	return std::vector<std::string>();
}

std::string IndexManager::getAttrNameByIndexName(std::string indexName, std::string tableName)
{
	return std::string();
}

std::string IndexManager::getIndexNameByAttrName(std::string attrName, std::string tableName)
{
	return std::string();
}

indexIterator::indexIterator(std::string tableName, std::string indexName)
{
}

void indexIterator::changePlaceByIndex(int64 i)
{
}

bool indexIterator::next()
{
	return false;
}
