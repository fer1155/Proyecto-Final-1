#ifndef ProcesosGuardados_H
#define ProcesosGuardados_H
#include <vector>
#include <fstream>
#include <string.h>
#include <iostream>
#include "Proceso.h"
using namespace std;

class ProcesosGuardados{
  private:
    vector<proceso> procesosGuardados;
  public:
    ProcesosGuardados();
    ~ProcesosGuardados();
    vector<proceso> getVectorProcesosGuardados();
    void agregarProceso(proceso p);
    void mostrarProceso(int indicador);
    void mostrarTodosProcesos();
    bool quitarProceso(int indicador);
    bool quitarNombreProceso(string nombre);
    void actualizarProceso(int indicador);
    void actualizarNombreProceso(string nombre);
    bool buscarProceso(int indicador);
    bool buscarNombreProceso(string nombre);
    void setArrivalTimeNuevo(int arrivalTime, int posicion);
};


#else
class ProcesosGuardados_H; 
#endif