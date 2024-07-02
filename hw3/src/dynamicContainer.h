#include <memory>
class DynamicContainer {
private:
  long long int sizeofArr = 1;
  std::shared_ptr<int[]> elem = std::shared_ptr<int[]>(new int[sizeofArr]);
  bool isDeleted;

public:
  long long int currSize = 0;
  DynamicContainer();
  void add(int number);
  int operator[](long long int place);
  int operator[](long long int place) const;

  void set(long long int place, int number);
  DynamicContainer abs();
  void removeFirst();
  std::shared_ptr<int[]> getElem();
};