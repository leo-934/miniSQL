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
		catalogManager->createTable(*res);
		if (res->primaryKey != "") indexManager->createIndex(res->primaryKey, res->tableName, res->primaryKey);
		//bufferManager->createTable(res->tableName);
	}
	else if (parseResult->op == Operation::dropTable) {
		auto res = std::dynamic_pointer_cast<DropTableSentence>(parseResult);
		catalogManager->dropTable(res->tableName);
		indexManager->dropAllIndex(res->tableName);
		//bufferManager->dropTable(res->tableName);
	}
	else if (parseResult->op == Operation::createIndex) {
		auto res = std::dynamic_pointer_cast<CreateIndexSentence>(parseResult);
		indexManager->createIndex(res->indexName,res->tableName,res->attrName);
	}
	else if (parseResult->op == Operation::dropIndex) {
		auto res = std::dynamic_pointer_cast<DropIndexSentence>(parseResult);
		indexManager->dropIndex(res->indexName,res->tableName);
	}
	else if (parseResult->op == Operation::selectRecord) {
		auto res = std::dynamic_pointer_cast<SelectRecordSentence>(parseResult);
		std::vector<std::string> attrNamesForIndex;
		if (indexManager->hasClusteredIndex(res->tableName)) attrNamesForIndex.push_back(indexManager->getAttrNameByIndexName(indexManager->getClusteredIndex(res->tableName), res->tableName));
		if (indexManager->hasNonClusteredIndex(res->tableName)) attrNamesForIndex.push_back(indexManager->getAttrNameByIndexName(indexManager->getNonClusteredIndex(res->tableName)[0], res->tableName));
		if (attrNamesForIndex.size() > 0) {
			for (auto i : attrNamesForIndex) {
				for (auto j : res->conditions) {
					if (j.attrName == i) {
						std::vector<condition> conditionsForIndex;
						std::vector<condition> conditionsNotForIndex;
						for (auto k : res->conditions) {
							if (i == k.attrName) conditionsForIndex.push_back(k);
							else conditionsNotForIndex.push_back(k);
						}
						auto addresses=indexManager->selectIndexsByCondition(res->tableName, indexManager->getIndexNameByAttrName(i,res->tableName), conditionsForIndex);
						auto selectRes=recordManager->selectRecordsByAddressAndCondition(res->tableName, addresses, conditionsNotForIndex);
						//writer
						return;
					}
				}
			}
		}
	}
	else if (parseResult->op == Operation::insertRecord) {
		auto res = std::dynamic_pointer_cast<InsertRecordSentence>(parseResult);
		auto address=recordManager->insertRecordToTable(res->tableName, res->values);
		indexManager->insertToIndex(res->tableName, res->values, address);

	}
	else if (parseResult->op == Operation::deleteRecord) {

	}
	else if (parseResult->op == Operation::execFile) {

	}
	else if (parseResult->op == Operation::quit) {

	}
	return;
}
