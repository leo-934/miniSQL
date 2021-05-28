#include "..\include\APP.h"

APP::APP()
{
	bufferManager = std::make_shared<BufferManager>();
	recordManager = std::make_shared<RecordManager>();
	indexManager = std::make_shared<IndexManager>();
	catalogManager = std::make_shared<CatalogManager>();
	api = std::make_shared<API>();
	interpreter = std::make_shared<Interpreter>();
}
