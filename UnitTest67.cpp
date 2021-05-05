#include "pch.h"
#include "CppUnitTest.h"
#include "../OOP Lab6.7/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest67
{
	TEST_CLASS(UnitTest67)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Array a = { new int[5]{ 10, 7, 5, 4, 1 }, 5 };
			IFilter* f = new FilterEven;
			Array c =ArrayFilter(a, *f);
			Assert::AreEqual(*(c.start+1), 4);
		}
	};
}
