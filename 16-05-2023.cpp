/*
  Solution to Question 7 of AngelHack May 2023 Coding Challenge
  Answer = 32509983
*/

#include <array>
#include <cmath>
#include <iostream>
#include <map>

enum Tile
{
  EMPTY = 0,
  LIFEFORM = 1,
};

int main()
{
  static constexpr size_t ROWS = 5;
  static constexpr size_t COLS = 5;
  static constexpr size_t GRID_SIZE = ROWS * COLS;

  std::array<Tile, GRID_SIZE> grid = {
    LIFEFORM, LIFEFORM, LIFEFORM, LIFEFORM, EMPTY,
    LIFEFORM, EMPTY, EMPTY, EMPTY, EMPTY,
    LIFEFORM, EMPTY, EMPTY, LIFEFORM, EMPTY,
    EMPTY, LIFEFORM, EMPTY, LIFEFORM, EMPTY,
    LIFEFORM, LIFEFORM, EMPTY, LIFEFORM, LIFEFORM
  };

  std::map<std::array<Tile, GRID_SIZE>, int> appearedGridsMap;
  while (true)
  {
    std::array<Tile, GRID_SIZE> newGrid;
    for (size_t row = 0; row < ROWS; ++row)
    {
      for (size_t col = 0; col < COLS; ++col)
      {
        size_t index = row * ROWS + col;
        auto tile = grid[index];
        int adjacentLifeforms = 0;

        // Check left tile
        if (index % 5)
        {
          size_t leftIndex = index - 1;
          adjacentLifeforms += grid[leftIndex];
        }

        // Check right tile
        if (index % 5 != 4)
        {
          size_t rightIndex = index + 1;
          adjacentLifeforms += grid[rightIndex];
        }

        // Check top tile
        if (index > 4)
        {
          size_t topIndex = index - COLS;
          adjacentLifeforms += grid[topIndex];
        }

        // Check bottom tile
        if (index < 20)
        {
          size_t bottomIndex = index + COLS;
          adjacentLifeforms += grid[bottomIndex];
        }

        if (tile == LIFEFORM)
          newGrid[index] = adjacentLifeforms == 1 ? LIFEFORM : EMPTY;
        else
          newGrid[index] = adjacentLifeforms == 1 || adjacentLifeforms == 2 ? LIFEFORM : EMPTY;
      }
    }
    grid = newGrid;
    if (++appearedGridsMap[grid] == 2)
      break;
  }

  // Calculate score
  unsigned long long score = 0;
  for (size_t i = 0; i < GRID_SIZE; ++i)
  {
    if (grid[i] == LIFEFORM)
      score += std::pow(2, i);
  }
  std::cout << "Answer = " << score << std::endl;
}