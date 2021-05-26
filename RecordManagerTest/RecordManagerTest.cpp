#include "pch.h"
#include "CppUnitTest.h"
#include "BufferManager.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecordManagerTest
{
	TEST_CLASS(RecordManagerTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BufferManager test;
			Assert::AreEqual(2,test.test());
		}
	};
}
