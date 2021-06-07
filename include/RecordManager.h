#pragma once
#include <string>
class RecordManager {
private:

public:
	int test();
	int64 insertRecordToTable(std::string tableName, anyVec values);
	std::vector<std::string> selectRecordsByAddressAndCondition(std::string tableName, std::vector<int64> addresses, std::vector<condition> conds);
};