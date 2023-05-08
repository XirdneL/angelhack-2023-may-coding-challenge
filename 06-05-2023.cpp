/*
  Solution to Question 2 of AngelHack May 2023 Coding Challenge
  Answer = 3540m (Jenna)
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

int CalculateDistance(const int speed, const int runDuration, const int restDuration, const int raceDuration = 1234)
{
  int dist = 0;
  int time = 0;
  while (time < raceDuration)
  {
   int runTime = std::min(runDuration, 1234 - time);
   dist += runTime * speed;
   time += runTime + restDuration;
  }
  return dist;
}

int main()
{
  std::unordered_map<std::string, int> runnerDistanceMap;
  runnerDistanceMap["John"] = CalculateDistance(10,6,20);
  runnerDistanceMap["James"] = CalculateDistance(8,8,25);
  runnerDistanceMap["Jenna"] = CalculateDistance(12,5,16);
  runnerDistanceMap["Josh"] = CalculateDistance(7,7,23);
  runnerDistanceMap["Jacob"] = CalculateDistance(9,4,32);
  runnerDistanceMap["Jerry"] = CalculateDistance(5,9,18);

  auto iter = runnerDistanceMap.begin();
  auto furthestDistanceIter = runnerDistanceMap.begin();
  const auto end = runnerDistanceMap.end();
  while (iter != end)
  {
    if (iter->second > furthestDistanceIter->second)
      furthestDistanceIter = iter; // Note: Solution does not handle case with multiple winners
    ++iter;
  }

  std::cout << furthestDistanceIter->first << " won the race at " << furthestDistanceIter->second << "m" << std::endl;
}