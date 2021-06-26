#include "APP.h"
#include "SqlScanner.h"
#include <ctime>
#include <exception>
APP::APP()
{
	catalogManager = std::make_shared<CatalogManager>();
	indexManager = std::make_shared<IndexManager>(catalogManager);
	writer = std::make_shared<Writer>(catalogManager);
	bufferManager = std::make_shared<BufferManager>(catalogManager);
	recordManager = std::make_shared<RecordManager>(bufferManager,catalogManager,indexManager);
	interpreter = std::make_shared<Interpreter>(catalogManager);
}
void APP::run()
{
	while (1) {
		if (login()) break;
	}
	SqlScanner in = SqlScanner();
	while (1) {
		//static int a = 0;
		//a++;
		//if (a==10001) {
		//	//std::cout << a << std::endl;
		//}
		//if (std::ofstream::failbit) {
		//	//std::cout << "abc";
		//}
		try {
			writer->writePromt("root");
			auto parseResult = interpreter->parseSql(in.getSqlSentence());
			execSql(parseResult);
		}
		catch (std::exception& a) {
			std::cout << "invalid input"<<std::endl;
		}
	}
}

void APP::execSql(std::shared_ptr<Sentence> parseResult)
{
	if (parseResult->op == Operation::createTable) {
		auto startExec = time(0);
		auto res = std::dynamic_pointer_cast<CreateTableSentence>(parseResult);
		catalogManager->createTable(*res);
		if (res->primaryKey != "") indexManager->createIndex(res->primaryKey, res->tableName, res->primaryKey);
		bufferManager->createTable(res->tableName);
		auto endExec = time(0);
		writer->writeCreateResult();
		writer->writeTime(endExec - startExec);
	}
	else if (parseResult->op == Operation::dropTable) {
		auto startExec = time(0);
		auto res = std::dynamic_pointer_cast<DropTableSentence>(parseResult);
		catalogManager->dropTable(res->tableName);
		indexManager->dropAllIndex(res->tableName);
		bufferManager->dropTable(res->tableName);
		auto endExec = time(0);
		writer->writeDropResult();
		writer->writeTime(endExec - startExec);
	}
	else if (parseResult->op == Operation::createIndex) {
		auto startExec = time(0);
		auto res = std::dynamic_pointer_cast<CreateIndexSentence>(parseResult);
		indexManager->createIndex(res->indexName,res->tableName,res->attrName);
		recordManager->addPastRecordToIndex(res->tableName);
		auto endExec = time(0);
		writer->writeCreateResult();
		writer->writeTime(endExec - startExec);
	}
	else if (parseResult->op == Operation::dropIndex) {
		auto startExec = time(0);
		auto res = std::dynamic_pointer_cast<DropIndexSentence>(parseResult);
		indexManager->dropIndex(res->indexName);
		auto endExec = time(0);
		writer->writeDropResult();
		writer->writeTime(endExec - startExec);
	}
	else if (parseResult->op == Operation::selectRecord) {
		auto startExec = time(0);
		auto res = std::dynamic_pointer_cast<SelectRecordSentence>(parseResult);
		std::vector<std::string> attrNamesForIndex;
		if (indexManager->hasClusteredIndex(res->tableName)) attrNamesForIndex.push_back(indexManager->getAttrNameByIndexName(indexManager->getClusteredIndex(res->tableName), res->tableName));
		//if (indexManager->hasNonClusteredIndex(res->tableName)) attrNamesForIndex.push_back(indexManager->getAttrNameByIndexName(indexManager->getNonClusteredIndex(res->tableName)[0], res->tableName));
		if (indexManager->hasNonClusteredIndex(res->tableName)) {
			auto nonClusteredIndexes = indexManager->getNonClusteredIndex(res->tableName);
			for(auto i:nonClusteredIndexes)
				attrNamesForIndex.push_back(indexManager->getAttrNameByIndexName(i, res->tableName));
		}
		if (attrNamesForIndex.size() > 0) {


			auto i = attrNamesForIndex[0];
			std::vector<condition> conditionsForIndex;
			std::vector<condition> conditionsNotForIndex;
			for (auto k : res->conditions) {
				if (i == k.attrName) conditionsForIndex.push_back(k);
				else conditionsNotForIndex.push_back(k);
			}

			auto addresses = indexManager->selectIndexsByCondition(res->tableName, indexManager->getIndexNameByAttrName(i, res->tableName), conditionsForIndex);
			auto selectRes = recordManager->selectRecordsByAddressAndCondition(res->tableName, addresses, conditionsNotForIndex);
			auto endExec = time(0);
			writer->writeSelectResult(res->tableName, selectRes);
			writer->writeTime(endExec - startExec);

			
			//auto addresses = indexManager->selectIndexsByCondition(res->tableName, indexManager->getIndexNameByAttrName(i, res->tableName), conditionsForIndex);
			//auto actualRemovedAddresses = recordManager->removeRecordsByAddressAndCondition(res->tableName, addresses, conditionsNotForIndex);
			//indexManager->removeIndexByAddress(res->tableName, actualRemovedAddresses);
			//auto endExec = time(0);
			//writer->writeDeleteResult();
			//writer->writeTime(endExec - startExec);
			
			//writer
			return;


			//for (auto i : attrNamesForIndex) {
			//	for (auto j : res->conditions) {
			//		if (j.attrName == i) {
			//			std::vector<condition> conditionsForIndex;
			//			std::vector<condition> conditionsNotForIndex;
			//			for (auto k : res->conditions) {
			//				if (i == k.attrName) conditionsForIndex.push_back(k);
			//				else conditionsNotForIndex.push_back(k);
			//			}
			//			auto addresses=indexManager->selectIndexsByCondition(res->tableName, indexManager->getIndexNameByAttrName(i,res->tableName), conditionsForIndex);
			//			auto selectRes=recordManager->selectRecordsByAddressAndCondition(res->tableName, addresses, conditionsNotForIndex);
			//			auto endExec = time(0);
			//			writer->writeSelectResult(res->tableName,selectRes);
			//			writer->writeTime(endExec - startExec);
			//			//writer
			//			return;
			//		}
			//	}
			//}
		}
	}
	else if (parseResult->op == Operation::insertRecord) {
		//auto startExec = time(0);
		auto res = std::dynamic_pointer_cast<InsertRecordSentence>(parseResult);
		//std::cout << 1;
		if (std::ofstream::failbit) {
			//std::cout << "abc";
		}
		auto address=recordManager->insertRecordToTable(res->tableName, res->values);
		auto indexes = indexManager->getAllIndex(res->tableName);
		for (auto i : indexes) {
			auto attrNameForThisIndex = indexManager->getAttrNameByIndexName(i, res->tableName);
			auto originalAttrNames = catalogManager->getOriginalAttrNames(res->tableName);
			int j = 0;
			for (; j < originalAttrNames.size();j++) {
				if (originalAttrNames[j] == attrNameForThisIndex) break;
			}
			//int a = *(res->values[1]._Cast<int>());
			indexManager->insertToIndex(i, res->tableName, res->values[j],address);
		}

		//auto endExec = time(0);
		//writer->writeInsertResult();
		//writer->writeTime(endExec - startExec);

	}
	else if (parseResult->op == Operation::deleteRecord) {
		auto startExec = time(0);
		auto res = std::dynamic_pointer_cast<DeleteRecordSentence>(parseResult);
		std::vector<std::string> attrNamesForIndex;
		if (indexManager->hasClusteredIndex(res->tableName)) attrNamesForIndex.push_back(indexManager->getAttrNameByIndexName(indexManager->getClusteredIndex(res->tableName), res->tableName));
		//if (indexManager->hasNonClusteredIndex(res->tableName)) attrNamesForIndex.push_back(indexManager->getAttrNameByIndexName(indexManager->getNonClusteredIndex(res->tableName)[0], res->tableName));
		if (indexManager->hasNonClusteredIndex(res->tableName)) {
			auto nonClusteredIndexes = indexManager->getNonClusteredIndex(res->tableName);
			for (auto i : nonClusteredIndexes)
				attrNamesForIndex.push_back(indexManager->getAttrNameByIndexName(i, res->tableName));
		}
		if (attrNamesForIndex.size() > 0) {
			auto i = attrNamesForIndex[0];
			std::vector<condition> conditionsForIndex;
			std::vector<condition> conditionsNotForIndex;
			for (auto k : res->conditions) {
				if (i == k.attrName) conditionsForIndex.push_back(k);
				else conditionsNotForIndex.push_back(k);
			}
			auto addresses = indexManager->selectIndexsByCondition(res->tableName, indexManager->getIndexNameByAttrName(i, res->tableName), conditionsForIndex);
			auto actualRemovedAddresses = recordManager->removeRecordsByAddressAndCondition(res->tableName, addresses, conditionsNotForIndex);
			indexManager->removeIndexByAddress(res->tableName, actualRemovedAddresses);
			auto endExec = time(0);
			writer->writeDeleteResult();
			writer->writeTime(endExec - startExec);
			//writer
			return;
		}
	}
	else if (parseResult->op == Operation::execFile) {
		auto res = std::dynamic_pointer_cast<ExecFileSentence>(parseResult);
		SqlScanner in(res->filePath);
		while (1) {
			auto filesent = in.getSqlSentence();
			if (filesent == "") break;//可以把getSqlSentence改成抛出异常，可以改成try catch而不是接收返回值。具体使用哪一种其实我没有明确的决定
			std::shared_ptr<Sentence> fileParseResult = interpreter->parseSql(filesent);
			/*if (fileParseResult->op == Operation::dropTable) {
				std::cout << "bug";
			}*/
			execSql(fileParseResult);
		}
	}
	else if (parseResult->op == Operation::quit) {
		catalogManager->close();
		bufferManager->close();
		indexManager->close();
	}
	return;
}

bool APP::login()
{
	while (1) {
		std::cout << "username: ";
		std::string username, password;
		std::cin >> username;
		std::cout << "password: ";
		std::cin >> password;
		if (username == "root" && password == "root") {
			std::cout << "log in success\n";
			return true;
		}
		else std::cout << "wrong password\n";
	}
}
