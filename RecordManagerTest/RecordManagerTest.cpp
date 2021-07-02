#include "pch.h"
#include "CppUnitTest.h"
#include "RecordManager.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecordManagerTest
{
	TEST_CLASS(RecordManagerTest)
	{
	public: 
		
		TEST_METHOD(TestMethod1)
		{
			RecordManager test;
			Assert::AreEqual(1,test.test());
		}
	};
}
