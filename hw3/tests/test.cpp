#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <cstdint>
#include <memory>

#include "bigInt.h"

TEST(BigIntTests, sumPosPos){
	BigInt num1("123");
	BigInt num2("3456");
	
	num1 = num1 + num2;
	
	EXPECT_EQ(num1.getNum(),"3579");
}

TEST(BigIntTests, sumNegPos){
	BigInt num1("-123");
	BigInt num2("3456");
	
	num1 = num1 + num2;
	
	EXPECT_EQ(num1.getNum(),"3333");
}

TEST(BigIntTests, sumPosNeg){
	BigInt num1("123");
	BigInt num2("-3456");
	
	num1 = num1 + num2;
	
	EXPECT_EQ(num1.getNum(),"-3333");
}

TEST(BigIntTests, sumNegNeg){
	BigInt num1("-123");
	BigInt num2("-3456");
	
	num1 = num1 + num2;
	
	EXPECT_EQ(num1.getNum(),"-3579");
}

TEST(BigIntTests, subPosPos){
	BigInt num1("123");
	BigInt num2("3456");
	
	num1 = num1 - num2;
	
	EXPECT_EQ(num1.getNum(),"-3333");
}

TEST(BigIntTests, subNegPos){
	BigInt num1("-123");
	BigInt num2("3456");
	
	num1 = num1 - num2;
	
	EXPECT_EQ(num1.getNum(),"-3579");
}
TEST(BigIntTests, subPosNeg){
	BigInt num1("123");
	BigInt num2("-3456");
	
	num1 = num1 - num2;
	
	EXPECT_EQ(num1.getNum(),"3579");
}
TEST(BigIntTests, subNegNeg){
	BigInt num1("-123");
	BigInt num2("-3456");
	
	num1 = num1 - num2;
	
	EXPECT_EQ(num1.getNum(),"3333");
}

TEST(BigIntTests, mulPosPos){
	BigInt num1("123");
	BigInt num2("3456");
	
	num1 = num1 * num2;
	
	EXPECT_EQ(num1.getNum(),"425088");
}

TEST(BigIntTests, mulNegPos){
	BigInt num1("-123");
	BigInt num2("3456");
	
	num1 = num1 * num2;
	
	EXPECT_EQ(num1.getNum(),"-425088");
}

TEST(BigIntTests, mulPosNeg){
	BigInt num1("123");
	BigInt num2("-3456");
	
	num1 = num1 * num2;
	
	EXPECT_EQ(num1.getNum(),"-425088");
}

TEST(BigIntTests, mulNegNeg){
	BigInt num1("-123");
	BigInt num2("-3456");
	
	num1 = num1 * num2;
	
	EXPECT_EQ(num1.getNum(),"425088");
}

TEST(BigIntTests, bigSum){
	BigInt num1("1111111111111111111111111111111111111111111111111111111111111111111111111");
	BigInt num2("9999999999999999999999999999999999999999999999999999999999999999999999999");
	
	num1 = num1 + num2;
	
	EXPECT_EQ(num1.getNum(),"11111111111111111111111111111111111111111111111111111111111111111111111110");
}

TEST(BigIntTests, bigSub){
	BigInt num1("1111111111111111111111111111111111111111111111111111111111111111111111111");
	BigInt num2("9999999999999999999999999999999999999999999999999999999999999999999999999");
	num1 =num2-num1;
	
	EXPECT_EQ(num1.getNum(),"8888888888888888888888888888888888888888888888888888888888888888888888888");
}

TEST(BigIntTests, bigMul){
	BigInt num1("1111111111111111111111111111111111111111111111111111111111111111111111111");
	BigInt num2("9999999999999999999999999999999999999999999999999999999999999999999999999");
	num1 =num2*num1;
	
	EXPECT_EQ(num1.getNum(),"11111111111111111111111111111111111111111111111111111111111111111111111108888888888888888888888888888888888888888888888888888888888888888888888889");
}

TEST(BigIntTests, bigMulRnd){
	BigInt num1("47578374679835978649");
	BigInt num2("345359784643279823578");
	num1 =num2*num1;
	
	EXPECT_EQ(num1.getNum(),"16431657233105431211820122395305694786122");
}
int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}