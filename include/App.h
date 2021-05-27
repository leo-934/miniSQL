#pragma once
#include <memory>
#include "BufferManager.h"
#include "IndexManager.h"
#include "CatalogManager.h"
#include "API.h"
#include "Interpreter.h"
#include "RecordManager.h"

class App {
private:
	std::shared_ptr<BufferManager> bufferManager;
	std::shared_ptr<BufferManager> recordManager;
	std::shared_ptr<BufferManager> indexManager;
	std::shared_ptr<BufferManager> catalogManager;
	std::shared_ptr<BufferManager> api;
	std::shared_ptr<BufferManager> interpreter;

public:
	App() {
		bufferManager = std::make_shared<BufferManager>();
		recordManager = std::make_shared<RecordManager>();
		indexManager = std::make_shared<IndexManager>();
		catalogManager = std::make_shared<CatalogManager>();
		api = std::make_shared<API>();
		interpreter = std::make_shared<Interpreter>();
	}
	void run() {
		
	}
};