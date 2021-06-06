#include "APP.h"
#include "SqlScanner.h"
APP::APP()
{
	bufferManager = std::make_shared<BufferManager>();
	recordManager = std::make_shared<RecordManager>();
	indexManager = std::make_shared<IndexManager>();
	catalogManager = std::make_shared<CatalogManager>();
	api = std::make_shared<API>();
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

void APP::execSql(anyVec& parseResult)
{
	if (*parseResult[0]._Cast<operation>() == operation::createTable) {

	}
	else if (*parseResult[0]._Cast<operation>() == operation::dropTable) {

	}
	else if (*parseResult[0]._Cast<operation>() == operation::createIndex) {

	}
	else if (*parseResult[0]._Cast<operation>() == operation::dropIndex) {

	}
	else if (*parseResult[0]._Cast<operation>() == operation::selectRecord) {

	}
	else if (*parseResult[0]._Cast<operation>() == operation::insertRecord) {

	}
	else if (*parseResult[0]._Cast<operation>() == operation::deleteRecord) {

	}
	else if (*parseResult[0]._Cast<operation>() == operation::execFile) {

	}
	else if (*parseResult[0]._Cast<operation>() == operation::quit) {

	}
}
