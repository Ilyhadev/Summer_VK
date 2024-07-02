#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include "tokenParser.h"

int64_t func(int64_t  arg) {
  arg += 100500;
  return arg;
}

std::string func2(std::string arg) {
  arg += "100500";
  return arg;
}


TEST(TokenParser, unconditionalFunc) {
  TokenParser tokenParser;

  tokenParser.Parse(" infoString infoStringWithDigits123 1234 ");

  ASSERT_EQ(tokenParser.getInfo(),
            "B infoString infoStringWithDigits123 1234 E");
}

TEST(TokenParser, setDigitStringFunc) {
  TokenParser tokenParser;
  tokenParser.SetDigitTokenCallback(func);
  tokenParser.SetStringTokenCallback(func2);

  std::string info = " infoString infoStringWithDigits123 1234 ";
  std::vector<std::string> output = tokenParser.Parse(info);

  ASSERT_EQ(output[0], "infoString100500");
  ASSERT_EQ(output[1], "infoStringWithDigits123100500");
  ASSERT_EQ(output[2], "101734");
}

TEST(TokenParser, NoSetDigitFunc) {
  TokenParser tokenParser;
  tokenParser.SetStringTokenCallback(func2);

  std::string info = " infoString infoStringWithDigits123 1234 ";
  std::vector<std::string> output = tokenParser.Parse(info);

  ASSERT_EQ(output[0], "infoString100500");
  ASSERT_EQ(output[1], "infoStringWithDigits123100500");
  ASSERT_EQ(output.size(), 2);  //  Проверяет что 3 токен числа не обработался
                                //  никакой функцией, так как она не была задана
}

TEST(TokenParser, NoSetStringFunc) {
  TokenParser tokenParser;
  tokenParser.SetDigitTokenCallback(func);

  std::string info = " infoString infoStringWithDigits123 1234 ";
  std::vector<std::string> output = tokenParser.Parse(info);

  ASSERT_EQ(output[0], "101734");
  ASSERT_EQ(output.size(), 1);  //  Проверяет что 2 токена строк не обработались
                                //  никакой функцией, так как она не была задана
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
