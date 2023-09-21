#ifndef APP
#define APP

#include <memory>
#include "buffermanager.h"
#include "indexmanager.h"
#include "catalogmanager.h"
#include "interpreter.h"
#include "recordmanager.h"
#include "writer.h"

class app
{
private:
	std::shared_ptr<Writer> writer;
	std::shared_ptr<BufferManager> bufferManager;
	std::shared_ptr<RecordManager> recordManager;
	std::shared_ptr<IndexManager> indexManager;
	std::shared_ptr<CatalogManager> catalogManager;
	std::shared_ptr<Interpreter> interpreter;
	bool fileMode;

public:
	app();
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

#endif