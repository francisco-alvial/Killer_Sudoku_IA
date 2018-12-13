#include <iostream>
#include <queue> 
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <string.h>

enum { _ = -1 };
using namespace std; 


int fallas_global;
int puzzle[9][9];
int puzzle_mejor_sol[9][9];
int puzzle_base[9][9];
int sectores[9][9];
int Suma[100];
   
int check(int puzzle[9][9])
{
    int suma_select = 0;
    int suma_valor = 0;
 int Numero_de_fallas = 0;
  for (int i = 0; i < 9; ++i){
    for (int j = 0; j < 9; ++j){
      for (int k = j + 1; k < 9; ++k)
      {
        if (puzzle[i][j] != _ && puzzle[i][j] == puzzle[i][k]){
          Numero_de_fallas = Numero_de_fallas + 1;}
        if (puzzle[j][i] != _ && puzzle[j][i] == puzzle[k][i]){
          Numero_de_fallas = Numero_de_fallas + 1;}
        if (puzzle[j % 3 + (i % 3) * 3][j / 3 + (i / 3) * 3] != _ &&
            puzzle[j % 3 + (i % 3) * 3][j / 3 + (i / 3) * 3] ==
            puzzle[k % 3 + (i % 3) * 3][k / 3 + (i / 3) * 3]){
          Numero_de_fallas = Numero_de_fallas + 1;}
      }
    }
  }
    while(suma_select != 33){
        suma_valor = 0;
        for (int i = 0; i < 9; ++i){
            for (int j = 0; j < 9; ++j){
                if (sectores[i][j] == (suma_select+1) ){
                    suma_valor = suma_valor + puzzle[i][j];

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

      char cadena[128];
   char name[256];
   cout << "Ingresa nombre del archivo: ";
   cin.getline (name,256);
   char direccion[256]="Instancias Finales/";
   strcat(direccion,name);
   
   int Largo_Lista_Tabu;
   cout << "\n" << "ingresa un tamaño de la lista tabu: ";
   cin >> Largo_Lista_Tabu;
   
   ifstream fe(direccion);
   int i = 0;
   int j = 0;
   int i_1=0;

   int longitud;
   string num;
   int verificar = 0;
   while(!fe.eof()) {
      fe >> cadena;
      longitud=strlen(cadena);
      num=cadena;
      if(verificar == 1){

      	if( longitud == 5 && cadena[2] ==':'){
      		Suma[i_1]= atoi(num.substr(3,2).c_str());

		  }
		else if(longitud == 5 && cadena[3] ==':'){
			Suma[i_1]= cadena[4] - '0';
		}
		else if(longitud == 4){
			Suma[i_1]= cadena[3] - '0';
		}
		else if(longitud == 6){
			Suma[i_1]= atoi(num.substr(4,2).c_str());
		}
      	i_1++;
	  }
      if(cadena[0] == '.' && verificar == 0){
      	puzzle[i][j]= -1;
      	puzzle_mejor_sol[i][j]= -1;
      	puzzle_base[i][j]= -1;
      	if(longitud==3){
      		sectores[i][j]= cadena[2] - '0';
		  }
		else if(longitud==4){
			sectores[i][j]= atoi(num.substr(2,2).c_str());
		}
	  }
	  else if(verificar == 0){
	  	puzzle[i][j]=cadena[0] - '0';
      	puzzle_mejor_sol[i][j]= cadena[0] - '0';;
      	puzzle_base[i][j]= cadena[0] - '0';;
	  	if(longitud==3){
      		sectores[i][j]= cadena[2] - '0';
		  }
		else if(longitud==4){
			sectores[i][j]= atoi(num.substr(2,2).c_str());
		}
	  }
	  if (i == 8 && j == 8){
	  	verificar = 1;
	  }
      if (j==8){
      	i++;
      	j=0;
	  }

	  else{
	  	j++;
	  }
      
   }





	
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
      if (puzzle_base[i][j] == _)
      {
          Random_num = rand() % 9 + 1;
          puzzle[i][j] = Random_num;
      }
    }
  }

    for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j){
        puzzle_mejor_sol[i][j] = puzzle[i][j];}

    }
    
         for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j)
        std::cout <<  puzzle_mejor_sol[i][j] << " ";
      std::cout << std::endl;
    }
    std::cout << std::endl;
    
  fallas_mejor_sol = check(puzzle);
  Mejores_fallas_por_iteracion = 10000;
  
  while (fallas_mejor_sol != 0){

    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j)
        {
            if (puzzle_base[i][j] == _)
            {
            	Devolver_valor = puzzle[i][j];
                for (int k = 1; k <= 9; ++k){
				
                puzzle[i][j] = k;
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
            	puzzle[i][j] =  Devolver_valor;
            	

            }
        }
    }
    std::cout << "i: " << guardar_i << " j: "<< guardar_j << " k: " << guardar_k << "\n";
    std::cout << "MEJOR ITERACION: " << Mejores_fallas_por_iteracion << "\n";
    std::cout << "MEJOR FALLA: " << fallas_mejor_sol << "\n";
    
    puzzle[guardar_i][guardar_j] = guardar_k;
    
    if (fallas_mejor_sol > Mejores_fallas_por_iteracion){
    	fallas_mejor_sol = Mejores_fallas_por_iteracion;
    	    for (int i = 0; i < 9; ++i)
		    {
		      for (int j = 0; j < 9; ++j){
		        puzzle_mejor_sol[i][j]  = puzzle[i][j];
		        }
		    }
	}
	Mejores_fallas_por_iteracion = 100000;

    Lista_Tabu_i.push(guardar_i);
    Lista_Tabu_j.push(guardar_j);
    Lista_Tabu_k.push(guardar_k);
    if(Lista_Tabu_i.size() == Largo_Lista_Tabu && Lista_Tabu_j.size() == Largo_Lista_Tabu && Lista_Tabu_k.size() == Largo_Lista_Tabu){
    	Lista_Tabu_i.pop();
    	Lista_Tabu_j.pop();
    	Lista_Tabu_k.pop();

	}


  }
  
     for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j)
        std::cout <<  puzzle_mejor_sol[i][j] << " ";
      std::cout << std::endl;
    }
    std::cout << std::endl;


}
