#pragma once
#include <string>
#include "Def.h"
#include "bplustree.h"

struct IndexInfo
{
public:
	std::string indexName;
	std::string tableName;
	std::string attrName;
	catalog type = catalog::INT;
	void* Tree;
	bool ifclustered = true;
};
