#include "pch.h"
#include "Def.h"
#include "CppUnitTest.h"
#include "CatalogManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CatalogManagerTest
{
	TEST_CLASS(CatalogManagerTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			CatalogManager test;
			Assert::AreEqual(1, test.test());
		}
		TEST_METHOD(FileTest) {
			CatalogManager test;
			CreateTableSentence sent;
			sent.attrNum = 3;
			sent.tableName = "testTable";
			sent.attrCata.insert(std::map<std::string, catalog>::value_type("qwe", catalog::FLOAT));
			sent.attrCata.insert(std::map<std::string, catalog>::value_type("asd", catalog::INT));
			sent.attrCata.insert(std::map<std::string, catalog>::value_type("zxc", catalog::CHAR));
			test.createTable(sent);
			test.close();
			CatalogManager result;
			Assert::AreEqual((int)catalog::FLOAT, (int)(result.getCataByAttrName("testTable", "qwe")));
		}
	};
}
