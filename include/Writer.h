#pragma once
#include <iostream>
#include <any>
#include <memory>
#include <ctime>
#include "CatalogManager.h"
#include "Def.h"

class Writer {
private:
	std::shared_ptr<CatalogManager> catalogManager;
public:
	Writer(std::shared_ptr<CatalogManager> _catalogManager);
	void writeTime(clock_t execTime);
	void writeSelectResult(std::string tableName, std::vector<anyVec> res);
	void writeInsertResult(std::string obj);
	void writeDeleteResult(std::string obj);
	void writeDropResult(std::string obj);
	void writeCreateResult(std::string obj);
	void writeExecResult(std::string fileName);
	void writeSplitLine(std::vector<int> lens);
	void writePromt(std::string userName);
};