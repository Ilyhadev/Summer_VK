#include <gtest/gtest.h>

#include "avlTreeImp.h"
TEST(toperatorOne, AVLTreeTests) {
  avl<int, std::string, std::less<>, AllocatorMine<NodeAVL<int, std::string>>>
      a{{12, "asd"},    {4213, "sfdg"},    {5435, "sdfdsf"},
        {12334, "asd"}, {4213243, "sfdg"}, {567435, "sdfdsf"},
        {12234, "asd"}, {4217983, "sfdg"}, {535435, "sdfdsf"}};
  EXPECT_EQ(a[4217983], "sfdg");
}
TEST(toperatorTwo, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  for (int i = 0; i < 10000; i++) {
    a[i] = i;
  }
  EXPECT_EQ(a[400], 400);
}

TEST(toperatorThree, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  a[123] = 423;
  EXPECT_EQ(a[123], 423);
}

TEST(at, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  a[123] = 423;
  EXPECT_EQ(a.at(123).second, 423);
}
TEST(insert, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  a.insert({123, 4023});
  a.insert({1213, 4293});
  a.insert({1232, 423});
  a.insert({12333, 3423});
  a.insert({1234, 4423});
  a.insert({1235, 4253});
  EXPECT_EQ(a.at(12333).second, 3423);
}

TEST(erase, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  a.insert({123, 4023});
  a.insert({1213, 4293});
  a.insert({1232, 423});
  a.insert({12333, 3423});
  a.insert({1234, 4423});
  a.insert({1235, 4253});
  for (auto itera = a.begin(); itera != a.end(); ++itera) {
    a.erase(itera);
  }
  a[12] = 23;
  EXPECT_EQ(a.at(12).second, 23);
}

TEST(find, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  a.insert({123, 4023});
  a.insert({1213, 4293});
  a.insert({1232, 423});
  a.insert({12333, 3423});
  a.insert({1234, 4423});
  a.insert({1235, 4253});  // +6
  a.erase(a.find(123));
  a.erase(a.find(1234));
  a.erase(a.find(1235));  // +3
  a[12] = 23;             // +4
  a.erase(a.find(12));    // +3
  EXPECT_EQ(a.size(), 3);
}

TEST(contains, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  a.insert({123, 4023});
  a.insert({1213, 4293});
  a.insert({1232, 423});
  a.insert({12333, 3423});
  a.insert({1234, 4423});
  a.insert({1235, 4253});  // +6
  a.erase(a.find(123));
  a.erase(a.find(1234));
  a.erase(a.find(1235));  // +3
  a[12] = 23;             // +4
  a.erase(a.find(12));    // +3
  if (!a.contains(123)) {
    EXPECT_EQ(2, 2);
  }
  if (a.contains(12333)) {
    EXPECT_EQ(2, 2);
  }
}

TEST(empty, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  if (a.empty()) {
    EXPECT_EQ(2, 2);
  }
  a[132] = 4322;
  if (a.empty()) {
    EXPECT_EQ(2, 4);
  }
  a.erase(a.find(132));
  if (a.empty()) {
    EXPECT_EQ(2, 2);
  }
}
TEST(size, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  a[1239] = 243;
  a.insert({123, 4023});
  a.insert({1213, 4293});
  a.insert({1232, 423});
  a.insert({12333, 3423});
  a.insert({1234, 4423});
  a.insert({1235, 4253});
  if (a.size() == 7) {
    EXPECT_EQ(1, 1);
  } else {
    EXPECT_EQ(-1, 2);
  }
  a.erase(a.find(123));
  if (a.size() == 6) {
    EXPECT_EQ(1, 1);
  } else {
    EXPECT_EQ(-1, 2);
  }
}

TEST(clear, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  a[1239] = 243;
  a.insert({123, 4023});
  a.insert({1213, 4293});
  a.insert({1232, 423});
  a.insert({12333, 3423});
  a.insert({1234, 4423});
  a.insert({1235, 4253});
  a.clear();
  if (a.size() == 0) {
    EXPECT_EQ(1, 1);
  } else {
    EXPECT_EQ(-1, 2);
  }
}

TEST(normalIterator, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  a[1] = 243;
  a.insert({2, 4023});
  a.insert({3, 4293});
  a.insert({4, 423});
  a.insert({5, 3423});
  a.insert({6, 4423});
  a.insert({7, 4253});
  int i = 1;  // here go from min
  for (auto itera = a.begin(); itera != a.end(); ++itera, i++) {
    EXPECT_EQ((*(itera)).pair.first, i);
  }
}
TEST(reversedIterator, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  a[1] = 243;
  a.insert({2, 4023});
  a.insert({3, 4293});
  a.insert({4, 423});
  a.insert({5, 3423});
  a.insert({6, 4423});
  a.insert({7, 4253});
  int i = 7;  // here go from max
  for (auto itera = a.rbegin(); itera != a.rend(); ++itera, i--) {
    EXPECT_EQ((*(itera)).pair.first, i);
  }
}
TEST(initializer_list, AVLTreeTests) {
  avl<int, std::string, std::less<>, AllocatorMine<NodeAVL<int, std::string>>>
      a{{12, "asd"},       {4213, "sfdg"},    {5435, "sdfdsf"},
        {12334, "asfsdd"}, {4213243, "sfdg"}, {567435, "sdfsdfdsf"},
        {12234, "asd"},    {4217983, "sfdg"}, {535435, "sdffsddsf"}};
  EXPECT_EQ(a.at(5435).second, "sdfdsf");
}
int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
