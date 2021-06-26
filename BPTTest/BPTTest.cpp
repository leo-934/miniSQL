#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <map>
#include <any>
#include "bplustree.h"
#include "IndexManager.h"
#include "Def.h"
#include <iostream>
int main() {
	
	std::vector<condition> cond;
	condition conditions;
	auto catalogManager = std::make_shared<CatalogManager>();
	IndexManager indextest(catalogManager);
	cts sent;
	sent.attrNum = 2;
	sent.tableName = "b";
	sent.attrCata.insert(std::pair<std::string, catalog>("c", catalog::INT));
	sent.attrCata.insert(std::pair<std::string, catalog>("f", catalog::INT));
	catalogManager->createTable(sent);
	indextest.createIndex("a", "b", "c");
	indextest.createIndex("d", "b", "f");
	conditions.attrName = "c";
	conditions.cata = catalog::INT;
	conditions.comp = comparison::low;
	conditions.value = 5;
	cond.push_back(conditions);
	for(int i=0;i<20;i++)
		indextest.insertToIndex("a", "b", i, i+10);
	std::vector<int64> a;
	a=indextest.selectIndexsByCondition("b", "a", cond);
	for (auto v : a) std::cout << v<<std::endl;
	//indextest.insertToIndex("a", "b", 2, 5);
	conditions.attrName = "c";
	conditions.cata = catalog::INT;
	conditions.comp = comparison::low;
	conditions.value = 15;
	cond[0] = conditions;
	indextest.removeIndexByAddress("b", a);
	//indextest.insertToIndex("a", "b", 3, 8);
	a=indextest.selectIndexsByCondition("b", "a", cond);
	indextest.dropIndex("a", "b");
	indextest.selectIndexsByCondition("b", "a", cond);
	indextest.dropIndex("d", "b");
	indextest.close();

	system("pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
