/*
  Archivo: Slot.cpp

  Fecha creación: 2023-06-10
  Fecha última modificación: 2023-07-01
*/

#include "Slot.h" 

Slot::Slot(string posicion, int valor)
{
  this->posicion=posicion;
  this->valor=valor;
 
}

Slot::~Slot()
{
}

int Slot::obtenerValor()
{
  return valor;
}
  
string Slot::obtenerPosicion()
{
  return posicion;
}

void Slot::cambiarValor(int nuevoValor)
{
  this->valor = nuevoValor;
}
