#include "../../external/catch2/catch.hpp"
#include "../task1/tree.h"
#include "CoutBufferFixture.h"

TEST_CASE_METHOD(CoutBufferFixture, "Easy test")
{
	std::istringstream input("9\n7 1\n1 4\n4 7\n9 7\n6 9\n9 3\n3 6\n8 6\n2 8\n8 5\n5 2");
	FindStrongComponents(input);
	CHECK(GetBufferValue() == "2 5 8 \n6 3 9 \n1 7 4 \n");
	ClearBuffer();
}

TEST_CASE_METHOD(CoutBufferFixture, "Default test")
{
	std::istringstream input("8\n1 2\n2 3\n3 4\n4 3\n5 1\n2 5\n5 6\n2 6\n6 7\n7 6\n3 7\n8 7\n4 8\n8 4");
	FindStrongComponents(input);
	CHECK(GetBufferValue() == "1 5 2 \n3 4 8 \n7 6 \n");
}

TEST_CASE_METHOD(CoutBufferFixture, "Weak component")
{
	std::istringstream input("3\n1 2\n2 3\n1 3");
	FindStrongComponents(input);
	CHECK(GetBufferValue() == "1 \n2 \n3 \n");
}

TEST_CASE_METHOD(CoutBufferFixture, "From lecture")
{
	std::istringstream input("15\n1 4\n1 6\n2 1\n2 7\n3 5\n3 8\n3 2\n4 2\n4 7\n4 6\n5 3\n5 8\n6 4\n6 9\n8 10\n8 9\n9 7\n10 11\n11 8\n12 14\n12 15\n14 15");
	FindStrongComponents(input);
	CHECK(GetBufferValue() == "13 \n12 \n14 \n15 \n3 5 \n8 11 10 \n1 2 4 6 \n9 \n7 \n");
}