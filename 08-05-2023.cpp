/*
  Solution to Question 3 of AngelHack May 2023 Coding Challenge
  Answer = 5152
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::string numStr = "1867";
  std::sort(numStr.begin(), numStr.end());
  std::vector<int> numsDivisibleBySeven;

  do
  {
    auto num = std::stoi(numStr);
    if (num % 7 == 0)
      numsDivisibleBySeven.emplace_back(num);
  } while (std::next_permutation(numStr.begin(), numStr.end()));

  if (numsDivisibleBySeven.empty())
  {
    std::cout << "No permutation is divisible by 7!" << std::endl;
  }
  else
  {
    auto answer = (numsDivisibleBySeven.front() + numsDivisibleBySeven.back()) / 2.0f;
    std::cout << "Answer = " << answer << std::endl;
  }
}