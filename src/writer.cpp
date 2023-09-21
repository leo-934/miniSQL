#include "writer.h"
#include <cstdio>
#include <vector>
Writer::Writer(std::shared_ptr<CatalogManager> _catalogManager)
{
	catalogManager = _catalogManager;
}

void Writer::writeTime(clock_t execTime)
{
	double res = ((double)execTime);
	std::cout << "Total Time: ";
	printf("%.2f seconds\n", res);
	return;
}

void Writer::writeSelectResult(std::string tableName, std::vector<anyVec> res)
{
	std::cout << std::endl;
	if (res.size() == 0)
	{
		std::cout << "empty set" << std::endl;
		return;
	}
	std::vector<int> lens;
	auto attrNames = catalogManager->getOriginalAttrNames(tableName);
	for (int i = 0; i < attrNames.size(); i++)
		lens.push_back(attrNames[i].size());
	std::vector<catalog> catas;
	for (auto attr : attrNames)
	{
		auto cata = catalogManager->getCataByAttrName(tableName, attr);
		catas.push_back(cata);
	}
	for (auto record : res)
		for (int i = 0; i < record.size(); i++)
			if (record[i].type() == typeid(int))
			{
				int val = std::any_cast<int>(record[i]);
				if (std::to_string(val).size() > lens[i])
					lens[i] = std::to_string(val).size();
			}
			else if (record[i].type() == typeid(float))
			{
				float val = std::any_cast<float>(record[i]);
				if (std::to_string(val).size() > lens[i])
					lens[i] = std::to_string(val).size();
			}
			else
			{
				std::string val = std::any_cast<std::string>(record[i]);
				if (val.size() > lens[i])
					lens[i] = val.size();
			}

	writeSplitLine(lens);

	putchar('|');
	for (int i = 0; i < lens.size(); i++)
	{
		for (int j = 0; j < lens[i]; j++)
		{
			if (j < attrNames[i].size())
				putchar(attrNames[i][j]);
			else
				putchar(' ');
		}
		putchar('|');
	}
	putchar('\n');

	writeSplitLine(lens);

	for (auto record : res)
	{
		putchar('|');
		for (int i = 0; i < lens.size(); i++)
		{
			for (int j = 0; j < lens[i]; j++)
			{
				std::string stringToWrite;
				if (record[i].type() == typeid(int))
				{
					int val = std::any_cast<int>(record[i]);
					stringToWrite = std::to_string(val);
				}
				else if (record[i].type() == typeid(float))
				{
					float val = std::any_cast<float>(record[i]);
					stringToWrite = std::to_string(val);
				}
				else
				{
					std::string val = std::any_cast<std::string>(record[i]);
					stringToWrite = val;
				}
				if (j < stringToWrite.size())
					putchar(stringToWrite[j]);
				else
					putchar(' ');
			}
			putchar('|');
		}
		putchar('\n');
	}
	writeSplitLine(lens);
	std::cout << res.size() << " rows in set" << std::endl;
}

void Writer::writeInsertResult(std::string obj)
{
	std::cout << std::endl;

	std::cout << "insert " << obj << " success" << std::endl;
}

void Writer::writeDeleteResult(std::string obj)
{
	std::cout << std::endl;

	std::cout << "delete " << obj << " success" << std::endl;
}

void Writer::writeDropResult(std::string obj)
{
	std::cout << std::endl;

	std::cout << "drop " << obj << " success" << std::endl;
}

void Writer::writeCreateResult(std::string obj)
{
	std::cout << std::endl;

	std::cout << "create " << obj << " success" << std::endl;
}

void Writer::writeExecResult(std::string fileName)
{
	std::cout << std::endl;

	std::cout << "execute file " << fileName << " success" << std::endl;
}

void Writer::writeSplitLine(std::vector<int> lens)
{
	putchar('+');
	for (auto i : lens)
	{
		for (int j = 0; j < i; j++)
		{
			putchar('-');
		}
		putchar('+');
	}
	putchar('\n');
}

void Writer::writePromt(std::string userName)
{
	std::cout << "minisql > ";
}
