/*
  Solution to Question 6 of AngelHack May 2023 Coding Challenge
  Answer = 78
*/

#include <iostream>
#include <string>
#include <vector>

int GetMinDeletions(size_t leftIndex, size_t rightIndex, std::vector<std::vector<int>>& dp, const std::string& series)
{
  if (leftIndex > rightIndex)
    return 0;

  if (leftIndex == rightIndex)
    return 1;

  if (dp[leftIndex][rightIndex] != -1)
    return dp[leftIndex][rightIndex];

  auto result = 1 + GetMinDeletions(leftIndex + 1, rightIndex, dp, series);
  for (size_t i = leftIndex + 1; i <= rightIndex; ++i)
  {
    if (series[leftIndex] == series[i])
      result = std::min(result, GetMinDeletions(leftIndex + 1, i - 1, dp, series) + GetMinDeletions(i, rightIndex, dp, series));
  }

  dp[leftIndex][rightIndex] = result;
  return result;
}

int main()
{
  std::string series = "kjslaqpwoereeeeewwwefifjdksjdfhjdksdjfkdfdlddkjdjfjfjfjjjjfjffnefhkjgefkgjefkjgkefjekihutrieruhigtefhgbjkkkknbmssdsdsfdvneurghiueor";
  auto seriesSize = static_cast<int>(series.size());
  std::vector<std::vector<int>> dp(seriesSize, std::vector<int>(seriesSize, -1));
  std::cout << "Answer = " << GetMinDeletions(0, seriesSize - 1, dp, series) << std::endl;
}