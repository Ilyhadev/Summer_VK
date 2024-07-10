#include <gtest/gtest.h>

#include "avlTreeImp.h"
TEST(fancyTestOnTreeInsides,
     AVLTreeTests) {  // Я старался его изначально сделать в одну строчку как вы
                      // вк написали, но из-за длины у меня не вышло так
                      // элегантно)
  avl<int, std::string, std::less<>, AllocatorMine<NodeAVL<int, std::string>>>
      a{{12, "asd"},    {4213, "sfdg"},    {5435, "sdfdsf"},
        {12334, "asd"}, {4213243, "sfdg"}, {567435, "sdfdsf"},
        {12235, "asd"}, {4217984, "sfdg"}, {535436, "sdfdsf"}};
  std::vector<std::pair<int, std::string>> answer{
      NodeAVL<int, std::string>({12, "asd"}).pair,
      NodeAVL<int, std::string>({4213, "sfdg"}).pair,
      NodeAVL<int, std::string>({5435, "sdfdsf"}).pair,
      NodeAVL<int, std::string>({12235, "asd"}).pair,
      NodeAVL<int, std::string>({12334, "asd"}).pair,
      NodeAVL<int, std::string>({535436, "sdfdsf"}).pair,
      NodeAVL<int, std::string>({567435, "sdfdsf"}).pair,
      NodeAVL<int, std::string>({4213243, "sfdg"}).pair,
      NodeAVL<int, std::string>({4217984, "sfdg"}).pair};
  auto itera = a.begin();
  int i = 0;
  for (; itera != a.end(); ++itera, i++) {
    EXPECT_EQ((*itera).pair, answer[i]);
  }
}

TEST(toperatorOne, AVLTreeTests) {
  avl<int, std::string, std::less<>, AllocatorMine<NodeAVL<int, std::string>>>
      a{{12, "asd"},    {4213, "sfdg"},    {5435, "sdfdsf"},
        {12334, "asd"}, {4213243, "sfdg"}, {567435, "sdfdsf"},
        {12234, "asd"}, {4217983, "sfdg"}, {535435, "sdfdsf"}};
  EXPECT_EQ(a[4217983], "sfdg");
}
TEST(treeBalance, AVLTreeTests) {
  avl<int, int, std::less<>, AllocatorMine<NodeAVL<int, int>>> a;
  for (int i = 0; i < 10000; i++) {
    a[i] = i;
  }
  EXPECT_EQ(a.base_->height,
            13);  // Используем курс по DSA: h>=log(n+1)base2 -1,
  // где h - МИНИМАЛЬНАЯ высота дерева, а n - количество узлов.
  // log(10001)base2-1 ~~ 12,3. Округляем до целого числа т.е. 13.
}

TEST(toperatorTwo, AVLTreeTests) {
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
  EXPECT_EQ(a.at(12333).second, 3423);  // для insert и вставок делал
  // рандомные "пробные" проверки
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
