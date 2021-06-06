#include <fstream>
#include "pch.h"
#include "CppUnitTest.h"
#include "BufferManager.h"
#include "DataBlock.h"
#include "Def.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BufferManagerTest
{
	TEST_CLASS(BufferManagerTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BufferManager test;
			Assert::AreEqual(1, test.test());
		}
		TEST_METHOD(DataBlockTest)
		{
			anyVec cata;
			cata.push_back(catalog::INT);
			cata.push_back(catalog::FLOAT);
			cata.push_back(catalog::CHAR);
			cata.push_back(20);
			DataBlock b(cata);
			std::ofstream fs1("./test.txt", std::fstream::out | std::fstream::binary);
			anyVec record1 = { 5,(float)3.1,std::string("qweewq") };
			anyVec record2 = { 10,(float)2.333,std::string("wjn123wjn123wjn123") };
			b.addRecord(record1);
			b.addRecord(record2);
			b.toFile(fs1);
			fs1.close();
			DataBlock b2(cata);
			std::ifstream fs2("./test.txt", std::fstream::in | std::fstream::binary);
			b2.fromFile(fs2);
			b2.removeRecord(0);
			fs2.close();
			Assert::AreEqual((size_t)0,b2.at(0).size());
			Assert::AreEqual(10 ,*(b2.at(1)[0])._Cast<int>());
		}

	};
}
