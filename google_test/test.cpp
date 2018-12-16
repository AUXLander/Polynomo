#include "pch.h"
#include <iostream>
#include <string>
#include "../NodeList.h"
#include "../Polynomo.h"
#include "../Polynomo.cpp"
#include "../ToolSet.h"

TEST(TNodeList, can_create_list)
{
	ASSERT_NO_THROW(TNodeList<int> NList);
}
TEST(TNodeList, can_push_back)
{
	TNodeList<int> NList;
	ASSERT_NO_THROW(NList.addNode(5));
}
TEST(TNodeList, can_pop_front)
{
	TNodeList<int> NList;
	NList.addNode(5);
	ASSERT_NO_THROW(NList.getNode(0));
}
TEST(TNodeList, can_compare_two_lists_by_value)
{
	TNodeList<int> NList1, NList2;
	NList1.addNode(10);
	NList2.addNode(10);
	EXPECT_TRUE(NList1[0] == NList2[0]);
}
TEST(TNodeList, two_lists_with_different_size_are_not_equal)
{
	TNodeList<int> NList1, NList2;

	NList1.addNode(1); NList1.addNode(2);
	NList2.addNode(1);

	EXPECT_FALSE(NList1.getNode(0) == NList2.getNode(0));
}
TEST(TNodeList, can_create_copied_list)
{
	TNodeList<int> NList1, NList2;
	NList1.addNode(5);
	NList2 = NList1;
	EXPECT_TRUE(NList1[0] == NList2[0]);
}
TEST(TNodeList, can_assign_list)
{
	TNodeList<int> NList1, NList2;
	NList1.addNode(5);
	ASSERT_NO_THROW(NList2 = NList1);
}
TEST(TNodeList, method_get_return_value)
{
	TNodeList<int> NList;
	NList.addNode(10);
	EXPECT_EQ(10, NList.getNodeValue(0));
}
TEST(TNodeList, can_check_for_empty)
{
	TNodeList<int> NList;
	EXPECT_TRUE(NList.isEmpty());
}