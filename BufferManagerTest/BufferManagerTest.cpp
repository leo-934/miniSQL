#include "pch.h"
#include "CppUnitTest.h"
#include "BufferManager.h"
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
	};
}
