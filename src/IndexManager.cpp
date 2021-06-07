#include "IndexManager.h"

int IndexManager::test()
{
	return 1;
}

void IndexManager::createIndex(std::string indexName, std::string tableName, std::string attrName)
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
