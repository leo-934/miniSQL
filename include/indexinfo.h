#pragma once
#include <string>
using namespace std;

struct IndexInfo
{
public:
	string indexName;
	string tableName;
	string attrname;
	int type;//-1:int 0:float 1-255:length of str
	void* Tree;
	bool ifclustered = true;
};
