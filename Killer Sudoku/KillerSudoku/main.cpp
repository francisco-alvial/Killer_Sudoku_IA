#include <iostream>
#include <queue> 
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

enum { _ = -1 };
using namespace std; 
struct Puzzle
{
  int data[9][9];
} puzzle =
{
  {
    { _, _, _, _, _, _, _, _, _ },
    { _, _, _, 6, _, _, _, _, _ },
    { _, _, _, _, 3, _, _, _, _ },
    { 3, _, _, _, _, 1, _, _, _ },
    { _, _, _, _, _, _, 1, _, _ },
    { _, _, _, _, _, _, 9, 6, _ },
    { _, _, _, _, _, _, _, _, _ },
    { _, _, _, _, _, _, 2, _, 7 },
    { 9, _, _, 4, _, _, _, _, _ },
  }
};

struct Puzzle_mejor_sol
{
  int datas[9][9];
} puzzle_mejor_sol =
{
  {
    { _, _, _, _, _, _, _, _, _ },
    { _, _, _, 6, _, _, _, _, _ },
    { _, _, _, _, 3, _, _, _, _ },
    { 3, _, _, _, _, 1, _, _, _ },
    { _, _, _, _, _, _, 1, _, _ },
    { _, _, _, _, _, _, 9, 6, _ },
    { _, _, _, _, _, _, _, _, _ },
    { _, _, _, _, _, _, 2, _, 7 },
    { 9, _, _, 4, _, _, _, _, _ },
  }
};

struct Puzzle_base
{
  int dato[9][9];
} puzzle_base =
{
  {
    { _, _, _, _, _, _, _, _, _ },
    { _, _, _, 6, _, _, _, _, _ },
    { _, _, _, _, 3, _, _, _, _ },
    { 3, _, _, _, _, 1, _, _, _ },
    { _, _, _, _, _, _, 1, _, _ },
    { _, _, _, _, _, _, 9, 6, _ },
    { _, _, _, _, _, _, _, _, _ },
    { _, _, _, _, _, _, 2, _, 7 },
    { 9, _, _, 4, _, _, _, _, _ },
  }
};



 int sector[9][9] ={

    { 1, 1, 2, 2, 2, 3, 4, 4, 5 },
    { 6, 7, 8, 8, 3, 3, 9, 9, 5 },
    { 6, 7, 7, 10, 11, 12, 13, 14, 14 },
    { 15, 16, 16, 10, 11, 12, 13, 14, 14 },
    { 15, 17, 18, 19, 11, 20, 20, 21, 22 },
    { 23, 17, 18, 19, 24, 24, 25, 21, 22 },
    { 23, 17, 26, 27, 28, 29, 25, 25, 30 },
    { 31, 31, 26, 27, 28, 29, 25, 25, 30 },
    { 31, 31, 27, 27, 32, 32, 33, 33, 33 },
};

int Suma[33] = {14,13,20,12,10,9,12,9,5,7,18,9,12,19,5,14,18,5,15,4,14,8,8,6,28,11,18,3,13,16,27,13,10};

int fallas_global;


int check(const Puzzle &puzzle)
{
    int suma_select = 0;
    int suma_valor = 0;
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
    while(suma_select != 33){
        suma_valor = 0;
        for (int i = 0; i < 9; ++i){
            for (int j = 0; j < 9; ++j){
                if (sector[i][j] == (suma_select+1) ){
                    suma_valor = suma_valor + puzzle.data[i][j];

                }
            }
        }
        if (suma_valor > Suma[suma_select]){
             Numero_de_fallas = Numero_de_fallas + 1;
        }
        suma_select= suma_select + 1;
    }
  return Numero_de_fallas;
}


int main()
{	
	queue <int> Lista_Tabu_i; 
	queue <int> Lista_Tabu_j;
	queue <int> Lista_Tabu_k;  
	queue <int> Cola_Extra_i; 
	queue <int> Cola_Extra_j;
	queue <int> Cola_Extra_k;
	
	int guardar_i;
	int guardar_j;
	int guardar_k;
	
	int comprobar;
	
    int Random_num;
    int fallas_mejor_sol;
    int Mejores_fallas_por_iteracion;
    int contador=0;
    int fallas;
    int Devolver_valor;
    
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
    
         for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j)
        std::cout <<  puzzle_mejor_sol.datas[i][j] << " ";
      std::cout << std::endl;
    }
    std::cout << std::endl;
  fallas_mejor_sol = check(puzzle);
  Mejores_fallas_por_iteracion = 10000;
  while (fallas_mejor_sol != 0){

    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j)
        {
            if (puzzle_base.dato[i][j] == _)
            {
            	Devolver_valor = puzzle.data[i][j];
                for (int k = 1; k <= 9; ++k){
				
                puzzle.data[i][j] = k;
                fallas = check(puzzle);

                if (fallas <= Mejores_fallas_por_iteracion ){
                	
                		comprobar = 0;
                		
                		Cola_Extra_i = Lista_Tabu_i;
						Cola_Extra_j = Lista_Tabu_j;
						Cola_Extra_k = Lista_Tabu_k;
					    while (!Cola_Extra_i.empty()) 
					    {
					    	if ( Cola_Extra_i.front() == i  &&  Cola_Extra_j.front() == j && Cola_Extra_k.front() == k ){
					        	comprobar = 1;
								
								}

							Cola_Extra_i.pop();
							Cola_Extra_j.pop(); 
							Cola_Extra_k.pop();  
					    } 
                		

                		if(comprobar == 0){
                			
                			guardar_i = i;
                			guardar_j = j;
                			guardar_k = k;
							Mejores_fallas_por_iteracion = fallas;

						}
						else{
							comprobar == 0;
						}
	                    
                    
                }
            	}
            	puzzle.data[i][j] =  Devolver_valor;
            	

            }
        }
    }
    std::cout << "i: " << guardar_i << " j: "<< guardar_j << " k: " << guardar_k << "\n";
    std::cout << "MEJOR ITERACION: " << Mejores_fallas_por_iteracion << "\n";
    std::cout << "MEJOR FALLA: " << fallas_mejor_sol << "\n";
    
    puzzle.data[guardar_i][guardar_j] = guardar_k;
    
    if (fallas_mejor_sol > Mejores_fallas_por_iteracion){
    	fallas_mejor_sol = Mejores_fallas_por_iteracion;
    	    for (int i = 0; i < 9; ++i)
		    {
		      for (int j = 0; j < 9; ++j){
		        puzzle_mejor_sol.datas[i][j]  = puzzle.data[i][j];
		        }
		    }
	}
	Mejores_fallas_por_iteracion = 100000;

    Lista_Tabu_i.push(guardar_i);
    Lista_Tabu_j.push(guardar_j);
    Lista_Tabu_k.push(guardar_k);
    if(Lista_Tabu_i.size() == 150 && Lista_Tabu_j.size() == 150 && Lista_Tabu_k.size() == 150){
    	Lista_Tabu_i.pop();
    	Lista_Tabu_j.pop();
    	Lista_Tabu_k.pop();

	}


  }
  
     for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j)
        std::cout <<  puzzle_mejor_sol.datas[i][j] << " ";
      std::cout << std::endl;
    }
    std::cout << std::endl;


}
