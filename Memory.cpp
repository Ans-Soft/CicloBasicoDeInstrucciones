/*
  Archivo: Memory.cpp

  Fecha creación: 2023-06-10
  Fecha última modificación: 2023-07-01
*/

#include <fstream>
#include <sstream>
#include "Memory.h"  
#include "Slot.h"


Memory::Memory(string nombreArchivo)
{
  // Almacenar instrucciones
  ifstream archivo(nombreArchivo.c_str());
  string linea;
  while (getline(archivo, linea))
  {
    almacenarInstrucciones(linea);
  }

  // Almacena los datos o variables de las instrucciones
  this->num_instruccion = 0;

  // Procesar instrucciones de tipo SET
  while (num_instruccion < instrucciones.size() && instrucciones.at(num_instruccion).at(0) == "SET")
  {
    almacenarPosicion(instrucciones.at(num_instruccion));
    this->num_instruccion++;
  }
}

Memory::~Memory()
{
  //No hace nada
}

void Memory::almacenarInstrucciones(string linea)
{
  // Vector para almacenar las palabras individuales de la línea
  vector<string> words;

  // Variable para almacenar cada palabra extraída
  string word;

  // Creamos un stringstream a partir de la línea para dividirla en palabras
  stringstream sstream(linea);

  // Iteramos hasta obtener todas las palabras de la línea
  while (getline(sstream, word, ' '))
  {
    // Agregamos cada palabra al vector de palabras
    words.push_back(word);
  }

  // Agregamos el vector de palabras (instrucción) a la lista de instrucciones
  instrucciones.push_back(words);
}

void Memory::almacenarPosicion(vector<string> instruccion)
{
  // Extraemos la posición de memoria de la instrucción en la posición 1 del vector
  string posicion = instruccion.at(1);

  // Extraemos el valor numérico de la instrucción en la posición 2 del vector
  int valor = stoi(instruccion.at(2));

  // Creamos un objeto Slot con la posición y valor extraídos
  Slot slot(posicion, valor);

  // Agregamos el objeto Slot al vector de posiciones de memoria
  posiciones.push_back(slot);
}

int Memory::obtenerValor(string posicionEnMemoria)
{
  // Recorremos el vector de posiciones de memoria
  for (int num_posiciones = 0; num_posiciones < posiciones.size(); num_posiciones++)
  {
    // Comparamos la posición actual con la posición buscada
    if (posiciones.at(num_posiciones).obtenerPosicion() == posicionEnMemoria)
    {
      // Si encontramos la posición buscada, devolvemos su valor
      return posiciones.at(num_posiciones).obtenerValor();
    }
  }

  // Si no encontramos la posición buscada, devolvemos 0 (valor predeterminado)
  return 0;
}
    
vector<string> Memory::obtenerInstruccion(int posicionDeInstruccion)
{
  return instrucciones.at(posicionDeInstruccion);
}
  
void Memory::cambiarValor(string posicionEnMemoria, int nuevoValor)
{
  bool isInMemory = false;

  // Recorremos el vector de posiciones de memoria
  for (int num_posiciones = 0; num_posiciones < posiciones.size(); num_posiciones++)
  {
    // Comparamos la posición actual con la posición buscada
    if (posiciones.at(num_posiciones).obtenerPosicion() == posicionEnMemoria)
    {
      isInMemory = true;
      // Si encontramos la posición buscada, cambiamos su valor al nuevo valor proporcionado
      posiciones.at(num_posiciones).cambiarValor(nuevoValor);
      break; // Terminamos el bucle, ya que hemos encontrado la posición y actualizado su valor
    }
  }

  // Si la posición no existe en memoria, la agregamos
  if (!isInMemory)
  {
    vector<string> nuevaInstruccion = {"SET", posicionEnMemoria, to_string(nuevoValor)};
    almacenarPosicion(nuevaInstruccion);
  }
}

int Memory::getNumInstruccion()
{
  return num_instruccion;
}

void Memory::eliminarDireccion(string posicionEnMemoria)
{
  // Recorremos el vector de posiciones de memoria
  for (int num_posiciones = 0; num_posiciones < posiciones.size(); num_posiciones++)
  {
    // Comparamos la posición actual con la posición buscada
    if (posiciones.at(num_posiciones).obtenerPosicion() == posicionEnMemoria)
    {
      // Si encontramos la posición buscada, la eliminamos del vector de posiciones
      posiciones.erase(posiciones.begin() + num_posiciones);
      break; // Terminamos el bucle, ya que hemos eliminado la posición
    }
  }
}

