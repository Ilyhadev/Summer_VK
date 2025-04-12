#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>

#include "avlTreeImp.h"

int main() {
  avl<int, std::string, std::less<>, AllocatorMine<NodeAVL<int, std::string>>>
      a{{12, "asd"},    {4213, "sfdg"},    {5435, "sdfdsf"},
        {12334, "asd"}, {4213243, "sfdg"}, {567435, "sdfdsf"},
        {12234, "asd"}, {4217983, "sfdg"}, {535435, "sdfdsf"}};
}
