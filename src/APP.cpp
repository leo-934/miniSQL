#include "APP.h"
#include "SqlScanner.h"
APP::APP()
{
	bufferManager = std::make_shared<BufferManager>();
	recordManager = std::make_shared<RecordManager>();
	indexManager = std::make_shared<IndexManager>();
	catalogManager = std::make_shared<CatalogManager>();
	interpreter = std::make_shared<Interpreter>();
}

void APP::run()
{
	SqlScanner in = SqlScanner();
	while (1) {
		auto parseResult = interpreter->parseSql(in.getSqlSentence());
		execSql(parseResult);
	}
}

void APP::execSql(std::shared_ptr<Sentence> parseResult)
{
	if (parseResult->op == Operation::createTable) {
		auto res = std::dynamic_pointer_cast<CreateTableSentence>(parseResult);
		catalogManager->addTableCata(*res);
		if (res->primaryKey != "") indexManager->createIndex(res->primaryKey, res->tableName, res->primaryKey);
		recordManager->createFile(res->tableName+".txt");
	}
	else if (parseResult->op == Operation::dropTable) {

	}
	else if (parseResult->op == Operation::createIndex) {

	}
	else if (parseResult->op == Operation::dropIndex) {

	}
	else if (parseResult->op == Operation::selectRecord) {

	}
	else if (parseResult->op == Operation::insertRecord) {

	}
	else if (parseResult->op == Operation::deleteRecord) {

	}
	else if (parseResult->op == Operation::execFile) {

	}
	else if (parseResult->op == Operation::quit) {

	}
}
