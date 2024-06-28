#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Allocator.h"
TEST(MyAllocator, identityOfMaxSize) {
  Allocator alloc;

  alloc.makeAllocator(100);

  int size = alloc.getMaxSize();

  EXPECT_EQ(100, size);
}

TEST(MyAllocator, initializeOffSet) {
  Allocator alloc;

  alloc.makeAllocator(100);

  int offSet = alloc.getOffSet();

  EXPECT_EQ(0, offSet);
}

TEST(MyAllocator, allocSizeOut) {
  Allocator alloc;

  alloc.makeAllocator(100);

  EXPECT_EQ(NULL, alloc.alloc(101));
}

TEST(MyAllocator, allocSizeIn) {
  Allocator alloc;

  alloc.makeAllocator(100);

  EXPECT_NE(nullptr, alloc.alloc(99));
}

TEST(MyAllocator, allocCheck) {
  Allocator alloc;

  alloc.makeAllocator(10);

  char* a = alloc.alloc(5);
  for (int i = 0; i < 5; i++) {
    a[i] = 'a';
  }

  char* b = alloc.alloc(5);
  for (int i = 0; i < 5; i++) {
    b[i] = 'b';
  }

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(a[i], 'a');
    EXPECT_EQ(b[i], 'b');
  }
}

TEST(MyAllocator, severalAllocs) {
  Allocator alloc;

  alloc.makeAllocator(100);

  EXPECT_NE(nullptr, alloc.alloc(40));
  EXPECT_NE(nullptr, alloc.alloc(50));
  EXPECT_EQ(nullptr, alloc.alloc(11));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}