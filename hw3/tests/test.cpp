#include <gtest/gtest.h>

#include "bigInt.h"
#include <iostream>
#include <string>

TEST(BigIntTests, sumPosPos) {
  BigInt num1("123");
  BigInt num2("3456");

  num1 = num1 + num2;

  EXPECT_EQ(num1.getNum(), "3579");
}

TEST(BigIntTests, sumNegPos) {
  BigInt num1("-123");
  BigInt num2("3456");

  num1 = num1 + num2;

  EXPECT_EQ(num1.getNum(), "3333");
}

TEST(BigIntTests, sumPosNeg) {
  BigInt num1("123");
  BigInt num2("-3456");

  num1 = num1 + num2;

  EXPECT_EQ(num1.getNum(), "-3333");
}

TEST(BigIntTests, sumNegNeg) {
  BigInt num1("-123");
  BigInt num2("-3456");

  num1 = num1 + num2;

  EXPECT_EQ(num1.getNum(), "-3579");
}

TEST(BigIntTests, subPosPos) {
  BigInt num1("123");
  BigInt num2("3456");

  num1 = num1 - num2;

  EXPECT_EQ(num1.getNum(), "-3333");
}

TEST(BigIntTests, subNegPos) {
  BigInt num1("-123");
  BigInt num2("3456");

  num1 = num1 - num2;

  EXPECT_EQ(num1.getNum(), "-3579");
}
TEST(BigIntTests, subPosNeg) {
  BigInt num1("123");
  BigInt num2("-3456");

  num1 = num1 - num2;

  EXPECT_EQ(num1.getNum(), "3579");
}
TEST(BigIntTests, subNegNeg) {
  BigInt num1("-123");
  BigInt num2("-3456");

  num1 = num1 - num2;

  EXPECT_EQ(num1.getNum(), "3333");
}

TEST(BigIntTests, mulPosPos) {
  BigInt num1("123");
  BigInt num2("3456");

  num1 = num1 * num2;

  EXPECT_EQ(num1.getNum(), "425088");
}

TEST(BigIntTests, mulNegPos) {
  BigInt num1("-123");
  BigInt num2("3456");

  num1 = num1 * num2;

  EXPECT_EQ(num1.getNum(), "-425088");
}

TEST(BigIntTests, mulPosNeg) {
  BigInt num1("123");
  BigInt num2("-3456");

  num1 = num1 * num2;

  EXPECT_EQ(num1.getNum(), "-425088");
}

TEST(BigIntTests, mulNegNeg) {
  BigInt num1("-123");
  BigInt num2("-3456");

  num1 = num1 * num2;

  EXPECT_EQ(num1.getNum(), "425088");
}

TEST(BigIntTests, bigSum) {
  BigInt num1(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "1");
  BigInt num2(
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "9");

  num1 = num1 + num2;

  EXPECT_EQ(num1.getNum(),
            "111111111111111111111111111111111111111111111111111111111111111111"
            "11111110");
}

TEST(BigIntTests, bigSub) {
  BigInt num1(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "1");
  BigInt num2(
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "9");
  num1 = num2 - num1;

  EXPECT_EQ(num1.getNum(),
            "888888888888888888888888888888888888888888888888888888888888888888"
            "8888888");
}

TEST(BigIntTests, bigMul) {
  BigInt num1(
      "111111111111111111111111111111111111111111111111111111111111111111111111"
      "1");
  BigInt num2(
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "9");
  num1 = num2 * num1;

  EXPECT_EQ(num1.getNum(),
            "111111111111111111111111111111111111111111111111111111111111111111"
            "111111088888888888888888888888888888888888888888888888888888888888"
            "88888888888889");
}

TEST(BigIntTests, bigMulRnd) {
  BigInt num1("47578374679835978649");
  BigInt num2("345359784643279823578");
  num1 = num2 * num1;

  EXPECT_EQ(num1.getNum(), "16431657233105431211820122395305694786122");
}

TEST(BigIntTests, moveTest) {
  BigInt num1("111111");
  BigInt num2(std::move(num1));
  EXPECT_EQ(num2.getNum(), "111111");
  EXPECT_EQ(num1.getNum(), "");  // as we can see num1 was deletes by move
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
