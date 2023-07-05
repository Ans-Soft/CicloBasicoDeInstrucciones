/*
  Archivo: Processor.h

  Fecha creación: 2023-06-10
  Fecha última modificación: 2023-07-01
*/
/**
  @class Processor
  @brief
  Atributos:
    - Memoria principal
    - instruccion
    - registro contador de programa
    - registro de control de instrucciones
    - registro de acceso a memoria
    - registro de datos de mememoria
    - registro unidad de control 
    - acumulador
    - unidad aritmetica logica

  Relaciones:
    - conoce la memoria
*/

#ifndef HH_PROCESSOR
#define HH_PROCESSOR

#include <iostream>
#include<string>
#include<vector>
#include "Slot.h"
#include "Memory.h"

using namespace std;

class Processor
{
  private:

    Memory* memoriaPrincipal;

    vector<string> instruccion;
    
    int contadorPrograma_PC;
    string controlMemoria_ICR;
    string accesoMemoria_MAR;
    string datosMemoria_MDR;  
    vector<string> unidadDeControl_UC;

    int acumulador;
    int ALU;


  public:
  /**
    Constructor -> Da valores iniciales a los atributos internos
  */
  Processor(Memory* memory);

  /**
    Destructor -> No hace nada
  */
  virtual ~Processor();

  /**
    Comienza la ejecucion del proceso
  */
  virtual void comenzarEjecucion(int instruccionInicial);

  /**
    Recibe las instrucciones y determina que es lo que cada una de ellas hace
  */ 
  virtual void unidadDeControl();

  /**
    Devuelve lo que haya en el registro PC
  */ 
  virtual int getPC();
  /**
    Devuelve lo que haya en el registro ICR
  */
  virtual string getICR();
  /**
    Devuelve lo que haya en el registro MAR
  */
  virtual string getMAR();
  /**
    Devuelve lo que haya en el registro MDR
  */
  virtual string getMDR(); 
  /**
    Devuelve lo que haya en el registro UC
  */
  virtual string getUC(); 
  /**
    Devuelve lo que haya en el acumulador
  */
  virtual int getAcumulador(); 

  /**
    Almacene un valor X en la dirección de memoria especificada. Donde X es un valor inmediato, directo o constante.
  */
  virtual void set();
   /**
    Hay tres formas: 
    
      -ADD D1 NULL NULL, agrega el valor en la dirección de memoria D1 al valor cargado en el registro del acumulador. 
      
      -ADD D1 D3 NULL Carga el valor en la dirección de memoria D1 en el registro del acumulador y lo suma al valor encontrado en la dirección de memoria D3. 
      
      -ADD D1 D3 D4 igual que SUMA D1 D3 pero pone el resultado en D4
  */
  virtual void add(); 
  /**
    Carga el valor en la dirección de memoria especificada y lo pone en el acumulador
  */
  virtual void ldr();
  /**
    Lee el valor en el registro acumulador y lo pone en la dirección de memoria especificada
  */
  virtual void str();
  /**
    Existen varias formas: 

    - SHW D2 NULL NULL muestra el valor en la dirección de memoria D2
    - SHW ACC muestra el valor en el registro acumulador
    - SHW ICR muestra el valor en el registro ICR
    - SHW MAR muestra el valor en el registro MAR
    - SHW MDR muestra el valor en el registro MDR 
    - SHW UC muestra el valor en la Unidad de Control
  */
  virtual void shw();
   /**
    Hay tres formas: 
    
      -SUB D1 NULL NULL, resta el valor en la dirección de memoria D1 al valor cargado en el registro del acumulador. 
      
      -SUB D1 D3 NULL Carga el valor en la dirección de memoria D1 en el registro del acumulador y lo resta al valor encontrado en la dirección de memoria D3. 
      
      -SUB D1 D3 D4 igual que SUMA D1 D3 pero pone el resultado en D4
  */
  virtual void sub();
   /**
    Hay tres formas: 
    
      -MUL D1 NULL NULL, multiplica el valor en la dirección de memoria D1 al valor cargado en el registro del acumulador. 
      
      -MUL D1 D3 NULL Carga el valor en la dirección de memoria D1 en el registro del acumulador y lo multiplica al valor encontrado en la dirección de memoria D3. 
      
      -MUL D1 D3 D4 igual que SUMA D1 D3 pero pone el resultado en D4
  */
  virtual void mul();
  /**
    Division de enteros
  */
  virtual void div();
  /**
    Carga el valor en la dirección de memoria especificada agrega 1 y almacena en la misma dirección
  */
  virtual void inc();
  /**
    Carga el valor en la dirección de memoria especificada resta 1 y almacena en la misma dirección
  */
  virtual void dec();
  /**
    Carga el valor de una dirección de memoria inicial a una dirección de memoria final y borra la dirección inicial
  */
  virtual void mov();
  /**
    Carga el valor en la dirección de memoria indicada si la resta con los valores del registro del acumulador es cero, lo pone en la misma dirección de memoria indicada.
    
    Hay tres formas: 

    -BEQ D10 NULL NULL 
    -BEQ D1 D10 NULL 
    -BEQ D1 D2 D3
  */
  virtual void beq();

};

#else
class Processor; // Declaración adelantada
#endif  
