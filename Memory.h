/*
  Archivo: Memory.h

  Fecha creación: 2023-06-10
  Fecha última modificación: 2023-07-01
*/

/**
  @class Memory
  @brief
  Atributos:
    - direcciones de memoria
    - instrucciones
    - id de la instruccion que se está ejecutando

  Relaciones:
    - contiene los slots de memoria o las direcciones en el vector de las direcciones de memoria (posiciones)
*/

#ifndef HH_MEMORY
#define HH_MEMORY


#include<string>
#include<vector>
#include "Slot.h"


using namespace std;

class Memory
{
  protected:
    vector<Slot> posiciones;//carga los valores
    vector<vector<string>>instrucciones;//carga las instrucciones
    int num_instruccion;

  public:
    /**
      Constructor -> Da valores iniciales a los atributos internos
    */
    Memory(string nombreArchivo);
    /**
      Destructor -> No hace nada
    */
    virtual ~Memory();

    /**
      Almacenar todas las intrucciones menos las de tipo SET en un vector 
    */
    virtual void almacenarInstrucciones(string linea);
    
    /**
      Almacenar todas las intrucciones de tipo SET en un vector diferente al anterior
    */
    virtual void almacenarPosicion(vector<string> instruccion);

    /**
      Devuelve el valor que hay en una posicion en memoria
    */
    virtual int obtenerValor(string posicion);

    /**
      Devuelve el vector de una instrucion. Las posiciones del vector contienen las palabras de la instruccion
    */
    virtual vector<string> obtenerInstruccion(int posicion);

    /**
      cambia el valor de una direccion o slot por otro, si la direcion a la que se está queriendo acceder no existe, la crea. 
    */
    virtual void cambiarValor(string posicion, int nuevoValor);

    /**
      Devuelve el indicador de la posicion de ultima instruccion que se ejecutó
    */
    virtual int getNumInstruccion();

    /**
      elimina una direccion de la memoria
    */
    virtual void eliminarDireccion(string posicion);

};

#else
class Memoria; // Declaración adelantada
#endif
