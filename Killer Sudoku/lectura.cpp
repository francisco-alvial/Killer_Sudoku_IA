#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

using namespace std;
enum { _ = -1 };
int main() {
   char cadena[128];
   int puzzle[9][9];
   int puzzle_mejor_sol[9][9];
   int puzzle_base[9][9];
   int sectores[9][9];
   ifstream fe("Instancias Finales/10blank.txt");
   int i = 0;
   int j = 0;
   int i_1=0;
   int Suma[100];
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
    for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j)
        std::cout <<  puzzle_mejor_sol[i][j] << " ";
      std::cout << std::endl;
    }
    std::cout << std::endl;
    
    for (int i = 0; i < 9; ++i)
    {
      for (int j = 0; j < 9; ++j)
        std::cout <<  sectores[i][j] << " ";
      std::cout << std::endl;
    }
    std::cout << std::endl;
    
    for (int i = 0; i < i_1; ++i)
    {
        std::cout << " " <<  Suma[i] ;
    }
   
   fe.close();

   return 0;
}
