#ifndef INDEXINFO
#define INDEXINFO

#include <string>
#include "def.h"
#include "bplustree.h"

struct IndexInfo
{
public:
	std::string indexName;
	std::string tableName;
	std::string attrName;
	catalog type = catalog::INT;
	void *Tree;
	bool ifclustered = true;
};

#endif