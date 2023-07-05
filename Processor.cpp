
/*
  Archivo: Processor.cpp

  Fecha creación: 2023-06-10
  Fecha última modificación: 2023-07-01
*/

#include "Processor.h"  

Processor::Processor(Memory* memory)
{
  this->memoriaPrincipal=memory;
    
  this->contadorPrograma_PC=0;
  this->controlMemoria_ICR="";
  this->accesoMemoria_MAR="";
  this->datosMemoria_MDR="";

  this->acumulador=0;
  this->ALU=0;
 
}

Processor::~Processor()
{
  //Destructor -> No hace nada
}

void Processor::comenzarEjecucion(int instruccionInicial)
{
  // Obtener PC -> Contador de Programa
  this->contadorPrograma_PC = instruccionInicial;

  while (true)
  {
    // Cargar el MAR (Registro de Dirección de Memoria) ->  Carga con el valor actual del PC
    this->accesoMemoria_MAR = to_string(this->contadorPrograma_PC);

    // Obtener la instrucción de la memoria usando el MAR
    instruccion = memoriaPrincipal->obtenerInstruccion(stoi(accesoMemoria_MAR));

    // Cargar el MDR (Registro de Datos de Memoria) -> Carga con la instrucción obtenida
    this->datosMemoria_MDR = instruccion.at(0);

    // Cargar el ICR (Registro de Control de Memoria) -> Carga con la instrucción a ejecutar
    this->controlMemoria_ICR = datosMemoria_MDR;

    // Aumentar el contador de programa para apuntar a la siguiente instrucción
    contadorPrograma_PC++;

    // Enviar la instrucción a la unidad de control para ser ejecutada
    this->unidadDeControl_UC = instruccion;

    // Verificar si la instrucción es un END -> fin del programa
    if (datosMemoria_MDR == "END")
    {
      // Si la instrucción es un END, el proceso termina su ejecución
      cout << "Terminó el proceso" << endl;
      break;
    }
    else
    {
      // Si la instrucción no es un END, ejecutar la unidad de control para realizar la operación correspondiente
      unidadDeControl();
    }
  }
}

//Funcion de la unidad de control

void Processor::unidadDeControl()
{  
  if (controlMemoria_ICR == "SET")
  {
    // Ejecutar la operación SET
    set();    
  }
  else if (controlMemoria_ICR == "LDR")
  {
    // Ejecutar la operación LDR
    ldr();
  }
  else if (controlMemoria_ICR == "SHW")
  {
    // Ejecutar la operación SHW
    shw();
  }
  else if (controlMemoria_ICR == "ADD")
  {
    // Ejecutar la operación ADD
    add();
  }
  else if (controlMemoria_ICR == "STR")
  {
    // Ejecutar la operación STR
    str();
  }
  else if (controlMemoria_ICR == "SUB")
  {
    // Ejecutar la operación SUB
    sub();
  }
  else if (controlMemoria_ICR == "MUL")
  {
    // Ejecutar la operación MUL
    mul();
  }
  else if (controlMemoria_ICR == "DIV")
  {
    // Ejecutar la operación DIV
    div();
  }
  else if (controlMemoria_ICR == "INC")
  {
    // Ejecutar la operación INC
    inc();
  }
  else if (controlMemoria_ICR == "DEC")
  {
    // Ejecutar la operación DEC
    dec();
  }
  else if (controlMemoria_ICR == "MOV")
  {
    // Ejecutar la operación MOV
    mov();
  }
  else if (controlMemoria_ICR == "BEQ")
  {
    // Ejecutar la operación BEQ
    beq();
  }
}

//Funciones de las instrucciones

void Processor::set()
{
  // Almacena la instrucción actual en la memoria principal
  memoriaPrincipal->almacenarPosicion(instruccion);
}

void Processor::ldr()
{
  // Obtener la dirección de memoria desde la instrucción actual
  this->accesoMemoria_MAR = unidadDeControl_UC.at(1);
  
  // Obtener el valor almacenado en la dirección de memoria especificada
  this->datosMemoria_MDR = to_string(memoriaPrincipal->obtenerValor(accesoMemoria_MAR));
  
  // Almacenar el valor obtenido en el acumulador del procesador
  this->acumulador = stoi(datosMemoria_MDR);
}

void Processor::shw()
{
  if (unidadDeControl_UC.at(1) == "ACC")
  {
    // Mostrar el valor almacenado en el acumulador
    cout << "Valor acumulador: " << to_string(getAcumulador()) << endl;
  }
  else if (unidadDeControl_UC.at(1) == "ICR")
  {
    // Mostrar el valor del registro ICR
    cout << "Registro ICR: " << getICR() << endl;
  }
  else if (unidadDeControl_UC.at(1) == "MAR")
  {
    // Mostrar el valor del registro MAR
    cout << "Registro MAR: " << getMAR() << endl;
  }
  else if (unidadDeControl_UC.at(1) == "MDR")
  {
    // Mostrar el valor del registro MDR
    cout << "Registro MDR: " << getMDR() << endl;
  }
  else if (unidadDeControl_UC.at(1) == "UC")
  {
    // Mostrar el valor del registro UC
    cout << "Registro UC: " << getUC() << endl;
  }
  else
  {
    
    // Si no se especifica un registro y se pasa una dirección de memoria obtener el valor almacenado en esa dirección y mostrarlo
    this->accesoMemoria_MAR = unidadDeControl_UC.at(1);
    this->datosMemoria_MDR = to_string(memoriaPrincipal->obtenerValor(accesoMemoria_MAR));
    cout << datosMemoria_MDR << endl;
  }
}

void Processor::add()
{
  if (unidadDeControl_UC.at(2) != "NULL")
  {
    
    // Si hay un segundo argumento en la instrucción (dirección de memoria) cargar el valor desde esa dirección en el acumulador
    ldr();
    unidadDeControl_UC.erase(unidadDeControl_UC.begin() + 1);
  }

  // Realizar la operación de suma: ALU = acumulador + acumulador
  this->ALU = this->acumulador;
  ldr(); // Cargar el valor del acumulador nuevamente

  // Sumar el valor actual del acumulador con el valor almacenado previamente en ALU
  this->ALU += this->acumulador;
  this->acumulador = this->ALU; // Almacenar el resultado de la suma en el acumulador

  if (unidadDeControl_UC.at(2) != "NULL")
  {
    // Si hay un tercer argumento en la instrucción (dirección de memoria), almacenar el resultado de la suma en esa dirección
    unidadDeControl_UC.erase(unidadDeControl_UC.begin() + 1);
    str();
  }
}

void Processor::str()
{
  // Obtener la dirección de memoria desde el segundo argumento de la instrucción
  this->accesoMemoria_MAR = unidadDeControl_UC.at(1);

  // Convertir el valor actual del acumulador a una cadena y almacenarlo en datosMemoria_MDR
  this->datosMemoria_MDR = to_string(this->acumulador);

  // Cambiar el valor en la memoria principal en la dirección especificada por accesoMemoria_MAR con el valor almacenado en datosMemoria_MDR (valor del acumulador)
  memoriaPrincipal->cambiarValor(accesoMemoria_MAR, stoi(datosMemoria_MDR));
}

void Processor::sub()
{
  // Si hay un segundo argumento en la instrucción (valor a restar)
  if (unidadDeControl_UC.at(2) != "NULL")
  {
    // Cargar en el acumulador el valor almacenado en la dirección de memoria especificada
    ldr();

    // Eliminar el segundo argumento de la instrucción para que no sea procesado nuevamente
    unidadDeControl_UC.erase(unidadDeControl_UC.begin() + 1);
  }

  // ALU almacena temporalmente el valor actual del acumulador
  this->ALU = this->acumulador;

  // Cargar en el acumulador el valor almacenado en la dirección de memoria especificada
  ldr();

  // Realizar la operación de resta entre ALU (valor anterior del acumulador) y el acumulador actual
  this->ALU -= this->acumulador;

  // Actualizar el acumulador con el resultado de la resta
  this->acumulador = this->ALU;

  // Si hay un segundo argumento en la instrucción (dirección de memoria para almacenar el resultado)
  if (unidadDeControl_UC.at(2) != "NULL")
  {
    // Eliminar el segundo argumento de la instrucción para que no sea procesado nuevamente
    unidadDeControl_UC.erase(unidadDeControl_UC.begin() + 1);

    // Almacenar el valor actual del acumulador en la dirección de memoria especificada
    str();
  }
}

void Processor::mul()
{
  // Si hay un segundo argumento en la instrucción (valor a multiplicar)
  if (unidadDeControl_UC.at(2) != "NULL")
  {
    // Cargar en el acumulador el valor almacenado en la dirección de memoria especificada
    ldr();

    // Eliminar el segundo argumento de la instrucción para que no sea procesado nuevamente
    unidadDeControl_UC.erase(unidadDeControl_UC.begin() + 1);
  }

  // ALU almacena temporalmente el valor actual del acumulador
  this->ALU = this->acumulador;

  // Cargar en el acumulador el valor almacenado en la dirección de memoria especificada
  ldr();

  // Realizar la operación de multiplicación entre ALU (valor anterior del acumulador) y el acumulador actual
  this->ALU *= this->acumulador;

  // Actualizar el acumulador con el resultado de la multiplicación
  this->acumulador = this->ALU;

  // Si hay un segundo argumento en la instrucción (dirección de memoria para almacenar el resultado)
  if (unidadDeControl_UC.at(2) != "NULL")
  {
    // Eliminar el segundo argumento de la instrucción para que no sea procesado nuevamente
    unidadDeControl_UC.erase(unidadDeControl_UC.begin() + 1);

    // Almacenar el valor actual del acumulador en la dirección de memoria especificada
    str();
  }
}

void Processor::div()
{
  // Si hay un segundo argumento en la instrucción (valor a dividir)
  if (unidadDeControl_UC.at(2) != "NULL")
  {
    // PREGUNTAR: ¿Por qué primero se carga el acumulador con su valor actual y luego se reemplaza con el valor almacenado en memoria?
    this->ALU = this->acumulador;

    // Cargar en el acumulador el valor almacenado en la dirección de memoria especificada
    ldr();

    // Realizar la operación de división entre ALU (valor anterior del acumulador) y el acumulador actual
    this->ALU /= this->acumulador;

    // Actualizar el acumulador con el resultado de la división
    this->acumulador = this->ALU;
  }
  else
  {
    // Si no hay segundo argumento en la instrucción, dividir el acumulador actual por sí mismo
    this->ALU /= this->acumulador;

    // Actualizar el acumulador con el resultado de la división.
    this->acumulador = this->ALU;
  }
}

void Processor::inc()
{
  // Cargar en el acumulador el valor almacenado en la dirección de memoria especificada
  ldr();

  // Incrementar el valor del acumulador en 1
  this->ALU = this->acumulador + 1;

  // Actualizar el acumulador con el resultado del incremento
  this->acumulador = this->ALU;

  // Almacenar el valor actual del acumulador en la dirección de memoria especificada
  str();
}

void Processor::dec()
{
  // Cargar en el acumulador el valor almacenado en la dirección de memoria especificada
  ldr();

  // Decrementar el valor del acumulador en 1
  this->ALU = this->acumulador - 1;

  // Actualizar el acumulador con el resultado del decremento
  this->acumulador = this->ALU;

  // Almacenar el valor actual del acumulador en la dirección de memoria especificada
  str();
}

void Processor::mov()
{
  // Cargar en el acumulador el valor almacenado en la dirección de memoria especificada
  ldr();

  // Eliminar la dirección de memoria actual para liberar espacio de memoria
  memoriaPrincipal->eliminarDireccion(accesoMemoria_MAR);

  // Obtener la nueva dirección de memoria desde la unidad de control
  this->accesoMemoria_MAR = unidadDeControl_UC.at(2);

  // Cargar en el MDR el valor del acumulador para ser almacenado en la nueva dirección
  this->datosMemoria_MDR = to_string(this->acumulador);

  // Almacenar el valor del MDR en la nueva dirección de memoria
  memoriaPrincipal->cambiarValor(accesoMemoria_MAR, stoi(datosMemoria_MDR));
}

void Processor::beq()
{
  // Realizar la operación de resta
  sub();

  // Verificar si el valor del acumulador es igual a cero
  if (acumulador == 0)
  {
    // Si es igual a cero, almacenar el valor del acumulador en la dirección de memoria actual
    str();
  }
}

//obtener valores de los registros 

int Processor::getPC()
{
  return this->contadorPrograma_PC;
}
  
string Processor::getICR()
{
  return this->controlMemoria_ICR;
}
  
string Processor::getMAR()
{
  return this->accesoMemoria_MAR;
}
  
string Processor::getMDR()
{
  return this->datosMemoria_MDR;
}

string Processor::getUC()
{
  // Inicializar una cadena vacía para almacenar la instrucción completa
  string instruccionTexto;

  // Recorrer todos los elementos de la instrucción almacenada en el vector unidadDeControl_UC
  for (int posicionInstruccion = 0; posicionInstruccion < unidadDeControl_UC.size(); posicionInstruccion++)
  {
    // Concatenar cada elemento de la instrucción a la cadena instruccionTexto
    instruccionTexto += unidadDeControl_UC.at(posicionInstruccion);
  }

  // Devolver la instrucción completa como una cadena de texto
  return instruccionTexto;
}

int Processor::getAcumulador()
{
  return this->acumulador;
}
