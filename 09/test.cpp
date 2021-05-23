#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "sort.hpp"

void ReadFile (std::vector<uint64_t>& nums, std::string filename) {
  std::ifstream file(filename);
  while (file.peek() != EOF) {
    uint64_t cur_n;
    file >> cur_n;
    nums.push_back(cur_n);
  }
}

void CreateTestFile (size_t amount, std::string name) {
  std::ofstream test(name);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<uint64_t> distrib(0);
  for (size_t i = 0; i < amount; ++i) {
    test << distrib(gen);
    if (i < amount - 1) {
      test << std::endl;
    }
  }
  test.close();
}

void ConductTest (size_t amount) {
  CreateTestFile(amount, "test.txt");
  std::vector<uint64_t> starting_perm;
  ReadFile(starting_perm, "test.txt");
  std::string res_name = SortFile("test.txt");
  std::vector<uint64_t> res;
  ReadFile(res, res_name);
  std::sort(starting_perm.begin(), starting_perm.end());
  assert(res == starting_perm);
  std::remove("test.txt");
  std::remove(res_name.c_str());
}

int main() {
  ConductTest(0);
  ConductTest(100000);
  ConductTest(1000001);
  ConductTest(3137921);
  // ConductTest(11324535);
  std::cout << "Success!" << std::endl;
  return 0;
}