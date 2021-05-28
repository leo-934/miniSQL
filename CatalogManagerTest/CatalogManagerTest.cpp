#include "pch.h"
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
	};
}
