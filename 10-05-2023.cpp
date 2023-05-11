/*
  Solution to Question 4 of AngelHack May 2023 Coding Challenge
  Answer = 475 (Exclude number 79)
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main()
{
  std::vector<int> numbers{
    1, 3, 54, 712, 52, 904, 113, 12, 135, 32, 31, 56, 23, 79, 611, 123, 677, 232, 997,
    101, 111, 123, 2, 7, 24, 57, 99, 45, 666, 42, 104, 129, 554, 335, 876, 35, 15, 93, 13};

  std::sort(numbers.begin(), numbers.end());

  auto numbersSize = numbers.size();
  int minCost = std::numeric_limits<int>::max();
  size_t excludedIndex = 0;
  for (size_t i = 0; i < numbersSize; ++i)
  {
    std::vector<int> numbersAfterExclusion = numbers;
    numbersAfterExclusion.erase(numbersAfterExclusion.begin() + i);
    int currentMinCost = 0;
    auto numbersAfterExclusionSize = numbersAfterExclusion.size();
    for (size_t j = 1; j < numbersAfterExclusionSize; j += 2)
      currentMinCost += numbersAfterExclusion[j] - numbersAfterExclusion[j - 1];

    if (currentMinCost < minCost)
    {
      minCost = currentMinCost;
      excludedIndex = i;
    }
  }

  std::cout << "Minimum cost = " << minCost << " after excluding number " << numbers[excludedIndex] << std::endl;
}