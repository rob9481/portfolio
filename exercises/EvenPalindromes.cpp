#include <array>
#include <cassert>
#include <iostream>

bool incr(std::array<int, 8> &num) {
  int carry = 1;

  for (auto i = num.rbegin(); i != num.rend(); ++i) {
    const auto sum = carry + *i;
    *i = sum % 10;
    carry = sum / 10;
  }

  return carry == 0;
}

bool equals(const std::array<int, 8> &lhs, const std::array<int, 8> &rhs) {
  for (int i = 0; i < 8; ++i) {
    if (lhs[i] != rhs[i])
      return false;
  }
  return true;
}

void test_incr() {
  {
    std::array<int, 8> arr{1, 2, 3, 4, 5, 6, 7, 8};
    assert(incr(arr));
    assert(equals(arr, {1, 2, 3, 4, 5, 6, 7, 9}));
  }

  {
    std::array<int, 8> arr{1, 2, 3, 4, 5, 6, 9, 9};
    assert(incr(arr));
    assert(equals(arr, {1, 2, 3, 4, 5, 7, 0, 0}));
  }

  {
    std::array<int, 8> arr{9, 9, 9, 9, 9, 9, 9, 9};
    assert(!incr(arr));
  }
}

bool less(const std::array<int, 8> &lhs, const std::array<int, 8> &rhs) {
  for (int i = 0; i < 8; ++i) {
    if (lhs[i] < rhs[i])
      return true;
    else if (lhs[i] > rhs[i])
      return false;
  }

  return false;
}

void test_less() {
  assert(less({1, 2, 3, 4, 5, 6, 7, 8}, {2, 3, 4, 5, 6, 7, 8, 9}));
  assert(less({1, 2, 3, 4, 5, 6, 7, 8}, {1, 3, 4, 5, 6, 7, 8, 9}));
  assert(!less({3, 2, 3, 4, 5, 6, 7, 8}, {2, 3, 4, 5, 6, 7, 8, 9}));
  assert(less({8, 8, 8, 8, 8, 8, 8, 9}, {9, 9, 9, 9, 9, 9, 9, 9}));
}

void print(const std::array<int, 8> &num) {
  for (auto digit : num)
    std::cout << digit;
  std::cout << '\n';
}

bool isPalindrome(const std::array<int, 8> &num) {
  return num[0] == num[7] && num[1] == num[6] && num[2] == num[5] &&
         num[3] == num[4];
}

bool isEven(const std::array<int, 8> &num) { return num[7] % 2 == 0; }

int main() {
  test_incr();
  test_less();
  std::array<int, 8> num{1, 0, 0, 0, 0, 0, 0, 0};
  constexpr const std::array<int, 8> max{9, 9, 9, 9, 9, 9, 9, 9};

  while (less(num, max)) {
    if (isPalindrome(num) && isEven(num))
      print(num);
    incr(num);
    if (num[0] % 2 == 1) {
      num[0] += 1;
    }
  }

  std::cout << std::flush;

  return 0;
}
