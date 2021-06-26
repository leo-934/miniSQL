#include "..\include\Writer.h"
#include <cstdio>
#include <vector>
Writer::Writer(std::shared_ptr<CatalogManager> _catalogManager)
{
	catalogManager = _catalogManager;
}

void Writer::writeTime(clock_t execTime)
{
	double res = ((double)execTime) / CLOCKS_PER_SEC;
	std::cout << "Total Time: ";
	printf("%.2f\n", res);
	return;
}

void Writer::writeSelectResult(std::string tableName, std::vector<anyVec> res)
{
	std::vector<int> lens;
	//for
}


