#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

enum { _ = -1 };

struct Puzzle
{
  int data[9][9];
} puzzle =
{
  {
    { 6, 8, 7, 1, 5, 4, _, _, 2 },
    { 5, _, 3, 6, 7, 9, 4, 1, 8 },
    { 4, 1, _, 2, 3, 8, 5, 7, _ },
    { 3, 6, 8, 5, 9, 1, 7, 2, 4 },
    { 2, _, 4, 7, 6, _, 1, 8, 5 },
    { 7, 5, _, 8, 4, 2, 9, _, 3 },
    { 1, 4, 6, 3, 2, 7, 8, 5, 9 },
    { 8, _, 5, 9, 1, 6, 2, 4, 7 },
    { 9, 7, 2, 4, 8, 5, 6, 3, 1 },
  }
};

struct Puzzle_mejor_sol
{
  int datas[9][9];
} puzzle_mejor_sol =
{
  {
    { 6, 8, 7, 1, 5, 4, _, _, 2 },
    { 5, _, 3, 6, 7, 9, 4, 1, 8 },
    { 4, 1, _, 2, 3, 8, 5, 7, _ },
    { 3, 6, 8, 5, 9, 1, 7, 2, 4 },
    { 2, _, 4, 7, 6, _, 1, 8, 5 },
    { 7, 5, _, 8, 4, 2, 9, _, 3 },
    { 1, 4, 6, 3, 2, 7, 8, 5, 9 },
    { 8, _, 5, 9, 1, 6, 2, 4, 7 },
    { 9, 7, 2, 4, 8, 5, 6, 3, 1 },
  }
};

struct Puzzle_base
{
  int dato[9][9];
} puzzle_base =
{
  {
    { 6, 8, 7, 1, 5, 4, _, _, 2 },
    { 5, _, 3, 6, 7, 9, 4, 1, 8 },
    { 4, 1, _, 2, 3, 8, 5, 7, _ },
    { 3, 6, 8, 5, 9, 1, 7, 2, 4 },
    { 2, _, 4, 7, 6, _, 1, 8, 5 },
    { 7, 5, _, 8, 4, 2, 9, _, 3 },
    { 1, 4, 6, 3, 2, 7, 8, 5, 9 },
    { 8, _, 5, 9, 1, 6, 2, 4, 7 },
    { 9, 7, 2, 4, 8, 5, 6, 3, 1 },
  }
};

int fallas_global;


int check(const Puzzle &puzzle)
{
 int Numero_de_fallas = 0;
  for (int i = 0; i < 9; ++i){
    for (int j = 0; j < 9; ++j){
      for (int k = j + 1; k < 9; ++k)
      {
        if (puzzle.data[i][j] != _ && puzzle.data[i][j] == puzzle.data[i][k]){
          Numero_de_fallas = Numero_de_fallas + 1;}
        if (puzzle.data[j][i] != _ && puzzle.data[j][i] == puzzle.data[k][i]){
          Numero_de_fallas = Numero_de_fallas + 1;}
        if (puzzle.data[j % 3 + (i % 3) * 3][j / 3 + (i / 3) * 3] != _ &&
            puzzle.data[j % 3 + (i % 3) * 3][j / 3 + (i / 3) * 3] ==
            puzzle.data[k % 3 + (i % 3) * 3][k / 3 + (i / 3) * 3]){
          Numero_de_fallas = Numero_de_fallas + 1;}
      }
    }
  }
  return Numero_de_fallas;
}

bool findSolution(Puzzle &puzzle)
{
  int x = -1;
  int y = -1;
  int min = 10;
  for (int i = 0; i < 9; ++i){
    for (int j = 0; j < 9; ++j)
    {
      if (puzzle.data[i][j] == _)
      {
        int c = 0;
        for (int k = 1; k <= 9; ++k)
        {
          puzzle.data[i][j] = k;
          if (check(puzzle))
            ++c;
          puzzle.data[i][j] = _;
        }
        if (min > c)
        {
          min = c;
          x = i;
          y = j;
        }
      }
    }
  }
    for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j)
        std::cout << puzzle.data[i][j] << " ";
      std::cout << std::endl;
    }
    std::cout << std::endl;
  if (x == -1)
    return true;
  for (int k = 1; k <= 9; ++k)
  {
    puzzle.data[x][y] = k;

    if (check(puzzle))
      if (findSolution(puzzle))

        return true;
  }
  puzzle.data[x][y] = _;
  return false;
}

int main()
{
    int Random_num;
    int fallas_mejor_sol;
    int contador=0;
    int fallas;
  for (int i = 0; i < 9; ++i){
    for (int j = 0; j < 9; ++j)
    {
      if (puzzle_base.dato[i][j] == _)
      {
          Random_num = rand() % 9 + 1;
          puzzle.data[i][j] = Random_num;
      }
    }
  }

    for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j){
        puzzle_mejor_sol.datas[i][j] = puzzle.data[i][j];}

    }
  fallas_mejor_sol = check(puzzle);

  while (fallas_mejor_sol != 0){

    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j)
        {
            if (puzzle_base.dato[i][j] == _)
            {
                for (int k = 1; k <= 9; ++k){
				
                puzzle.data[i][j] = k;
                fallas = check(puzzle);
                if (fallas <= fallas_mejor_sol){
                    fallas_mejor_sol = fallas;
                    for (int i = 0; i < 9; ++i)
                    {
                      for (int j = 0; j < 9; ++j){
                        puzzle_mejor_sol.datas[i][j] = puzzle.data[i][j];}

                    }
                }
            	}

            }
        }
    }
    for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j){
        puzzle.data[i][j] = puzzle_mejor_sol.datas[i][j];
        }
    }


  }
     for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j)
        std::cout << puzzle.data[i][j] << " ";
      std::cout << std::endl;
    }
    std::cout << std::endl;

}
