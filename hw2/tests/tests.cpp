#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "tokenParser.h"

void func(const std::string& arg, int begin, int end) {
  std::string res;
  for (int i = 0; i < arg.size(); i++) {
    if (i == end) {
      res += "100500Dig";
      if (end + 1 != arg.size()) {
        res += arg[end];
      }
    } else {
      res += arg[i];
    }
  }
  const_cast<std::string&>(arg) = res;
}

void func2(const std::string& arg, int begin, int end) {
  std::string res;
  for (int i = 0; i < arg.size(); i++) {
    if (i == end) {
      res += "100500Str";
      if (end + 1 != arg.size()) {
        res += arg[end];
      }
    } else {
      res += arg[i];
    }
  }
  const_cast<std::string&>(arg) = res;
}

TEST(TokenParser, unconditionalFunc) {
  TokenParser tokenParser;
  std::string info = " infoString infoStringWithDigits123 1234 ";
  tokenParser.Parse(info);

  ASSERT_EQ(info, "B infoString infoStringWithDigits123 1234 E");
}

TEST(TokenParser, setDigitStringFunc) {
  TokenParser tokenParser;
  tokenParser.SetDigitTokenCallback(func);
  tokenParser.SetStringTokenCallback(func2);

  std::string info = " infoString infoStringWithDigits123 1234 ";
  tokenParser.Parse(info);
  ASSERT_EQ(
      info,
      "B infoString100500Str infoStringWithDigits123100500Str 1234100500DigE");
}

TEST(TokenParser, NoSetDigitFunc) {
  TokenParser tokenParser;
  tokenParser.SetStringTokenCallback(func2);

  std::string info = " infoString infoStringWithDigits123 1234 ";
  tokenParser.Parse(info);

  ASSERT_EQ(info,
            "B infoString100500Str infoStringWithDigits123100500Str 1234 E");
}

TEST(TokenParser, NoSetStringFunc) {
  TokenParser tokenParser;
  tokenParser.SetDigitTokenCallback(func);

  std::string info = " infoString infoStringWithDigits123 1234 ";
  tokenParser.Parse(info);

  ASSERT_EQ(info, "B infoString infoStringWithDigits123 1234100500DigE");
}
int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
