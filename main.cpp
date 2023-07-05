/*
  Archivo: main.cpp

  Realizado por: 

  Ana Sofia Cantillo - 2223763
  Alejandro Fernandez - 2223587
  Santiago Castañeda - 2222138

  Fecha creación: 2023-06-10
  Fecha última modificación: 2023-07-01
*/

/*
  @brief 
  HISTORIA: 
  Las instrucciones se procesan bajo la dirección de la unidad de control paso a paso. 
  
  Este codigo es un simulador de ciclo basico de instrucciones que va a tomar todas las instrucciones de un archivo de texto llamado "instrucciones.txt" donde se ingresan los procesos que se quieren llevar a cabo.

*/
#include <iostream>
#include<string>
#include "Processor.h"
#include "Memory.h"

using namespace std;

int main() {

  Memory memory("instrucciones.txt");
  int num_instruccion = memory.getNumInstruccion();
  Processor processor(&memory);
  processor.comenzarEjecucion(num_instruccion);
 
}

