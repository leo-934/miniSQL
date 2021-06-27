#pragma once
#include <memory>
#include "BufferManager.h"
#include "IndexManager.h"
#include "CatalogManager.h"
#include "Interpreter.h"
#include "RecordManager.h"
#include "Writer.h"

class APP {
private:
	std::shared_ptr<Writer> writer;
	std::shared_ptr<BufferManager> bufferManager;
	std::shared_ptr<RecordManager> recordManager;
	std::shared_ptr<IndexManager> indexManager;
	std::shared_ptr<CatalogManager> catalogManager;
	std::shared_ptr<Interpreter> interpreter;
	bool fileMode;
public:
	APP();
	/// <summary>
	/// 开始运行数据库，包括登录，调用interpreter解析语句，调用API模块执行语句.
	/// </summary>
	void run();
	/// <summary>
	/// Executes the SQL.
	/// </summary>
	/// <param name="parseResult">The parse result.</param>
	void execSql(std::shared_ptr<Sentence> parseResult);
	bool login();
};