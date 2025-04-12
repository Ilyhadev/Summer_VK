#include <gtest/gtest.h>

#include "format.h"
TEST(basic_small, FormatFuncTests) {
  std::string answer = "{0}+{0} = {1}{1}";
  try {
    checkIfstringValid(answer);
    answer = format(answer, 2, "one");
  } catch (ErrorFormatBrackets &error) {
    error.showError();
    EXPECT_EQ(answer, "err");
  } catch (ErrorNumOfArg &error) {
    error.showError();
    EXPECT_EQ(answer, "err");
  }
  EXPECT_EQ(answer, "2+2 = oneone");  // Это просто троичная СИС :)
}
TEST(basic_big, FormatFuncTests) {
  std::string answer = "{0}{1}{2}{3}{4}{5}{6}{7}{8}{9} asdsdaa";
  try {
    checkIfstringValid(answer);
    answer = format(answer, 1, "2", 3, "4", 5, "6", 7, "8", 9, "10");
  } catch (ErrorFormatBrackets &error) {
    error.showError();
    EXPECT_EQ(answer, "err");
  } catch (ErrorNumOfArg &error) {
    error.showError();
    EXPECT_EQ(answer, "err");
  }
  EXPECT_EQ(answer, "12345678910 asdsdaa");
}
TEST(basic_very_big, basicCases) {
  std::string answer =
      "{0}{1}{2}{3}{4}{5}{6}{7}{8}{9}{10}{11}{12}{13}{14}{15}{16}{17}{18}+{"
      "19}";
  try {
    checkIfstringValid(answer);
    answer = format(answer, 1, "2", 3, "4", 5, "6", 7, "8", 9, "10", 11, "12",
                    13, "14", 15, "16", 17, "18", 19, "20");
  } catch (ErrorFormatBrackets &error) {
    error.showError();
    EXPECT_EQ(answer, "err");
  } catch (ErrorNumOfArg &error) {
    error.showError();
    EXPECT_EQ(answer, "err");
  }
  EXPECT_EQ(answer, "12345678910111213141516171819+20");
}
TEST(basic_very_big, errorFormatBrackets) {
  std::string answer =
      "0{1}{2{3}{4}{5}{6}{7{8}{9}{10}11}{12}{13{14}{15}{16}{17}{18}+{19}";
  try {
    checkIfstringValid(answer);
    answer = format(answer, 1, "2", 3, "4", 5, "6", 7, "8", 9, "10", 11, "12",
                    13, "14", 15, "16", 17, "18", 19, "20");
  } catch (ErrorFormatBrackets &error) {
    answer = "-1";  // Только здесь меняется значение (при ошибке)
  } catch (ErrorNumOfArg &error) {
    EXPECT_EQ(answer, "err");
  }
  EXPECT_EQ(answer, "-1");
}

TEST(basic_very_big, lessAmountOfArg) {
  std::string answer = "{0}+{0} = {1}{1}";
  try {
    checkIfstringValid(answer);
    answer = format(answer, "one");
  } catch (ErrorFormatBrackets &error) {
  } catch (ErrorNumOfArg &error) {
    answer = "-1";  // Только здесь меняется значение (при ошибке)
  }
  EXPECT_EQ(answer, "-1");
}

TEST(basic_very_big, moreAmountOfArg) {
  std::string answer = "{0}+{0} = {1}{1}";
  try {
    checkIfstringValid(answer);
    answer = format(answer, "one", 2, "adsad");
  } catch (ErrorFormatBrackets &error) {
  } catch (ErrorNumOfArg &error) {
    answer = "-1";  // Только здесь меняется значение (при ошибке)
  }
  EXPECT_EQ(answer, "-1");
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
