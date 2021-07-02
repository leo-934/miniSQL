#include "pch.h"
#include "CppUnitTest.h"
#include "IndexManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IndexManagerTest
{
	TEST_CLASS(IndexManagerTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			IndexManager test;
			Assert::AreEqual(1, test.test());
		}
	};
}
