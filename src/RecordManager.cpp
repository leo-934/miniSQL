#include <fstream>
#include "RecordManager.h"

int RecordManager::test()
{
	return 1;
}

void RecordManager::createFile(std::string filePath)
{
	std::ofstream fs(filePath, std::ofstream::out | std::ofstream::binary);
	fs.close();
}
