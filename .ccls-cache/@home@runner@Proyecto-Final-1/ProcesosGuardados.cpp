#include "ProcesosGuardados.h"
#include "Proceso.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

ProcesosGuardados::ProcesosGuardados(){};
ProcesosGuardados::~ProcesosGuardados(){};

vector<proceso> ProcesosGuardados::getVectorProcesosGuardados(){
  return procesosGuardados;
}

void ProcesosGuardados::setArrivalTimeNuevo(int arrivalTime, int posicion){
  procesosGuardados[posicion].setArrivalTime(arrivalTime);
}

void ProcesosGuardados::agregarProceso(proceso p) {
  procesosGuardados.push_back(p);
  cout << endl << "Proceso agregado exitosamente" << endl << endl;
}

void ProcesosGuardados::mostrarTodosProcesos(){
  cout << "Procesos guardados: " << endl;
  for (int i = 0; i < procesosGuardados.size(); i++){
    cout << "-------------------------------" << endl;
    cout << "Nombre: " << procesosGuardados[i].getNombre() << endl;
    cout << "Arrival Time: " << procesosGuardados[i].getArrivalTime() << endl;
    cout << "Burst Time: " << procesosGuardados[i].getBurstTime() << endl;
    cout << "Indicador: " << procesosGuardados[i].getIndicador() << endl; 
    cout << "-------------------------------" << endl;
    //string nombreArchivo = procesosGuardados[i].getNombre() + ".txt";
  }
}

// void ProcesosGuardados::mostrarProceso(int indicador){
//   for (int i = 0; i < procesosGuardados.size(); i++){
//     if (indicador == procesosGuardados[i].getIndicador()){
//       cout << "Nombre: " << procesosGuardados[i].getNombre() << endl;
//       cout << "Arrival Time: " << procesosGuardados[i].getArrivalTime() << endl;
//       cout << "Burst Time: " << procesosGuardados[i].getBurstTime() << endl;
//       cout << "Prioridad: " << procesosGuardados[i].getPrioridad() << endl; 
//     }else{
//       cout<< "No se encontró el proceso." << endl;
//       break;
//         }
//   }
// }

bool ProcesosGuardados::buscarProceso(int indicador){
  for (int i = 0; i < procesosGuardados.size(); i++){
    if (indicador == procesosGuardados[i].getIndicador()){
      cout << endl <<"Nombre: " << procesosGuardados[i].getNombre() << endl;
      cout << "Arrival Time: " << procesosGuardados[i].getArrivalTime() << endl;
      cout << "Burst Time: " << procesosGuardados[i].getBurstTime() << endl;
      cout << "Indicador: " << procesosGuardados[i].getIndicador() << endl;
      cout << "\n";
      return true;
    }
  }

  return false;
}

bool ProcesosGuardados::buscarNombreProceso(string nombre){
  for (int i = 0; i < procesosGuardados.size(); i++){
    if (nombre == procesosGuardados[i].getNombre()){
      cout << endl <<"Nombre: " << procesosGuardados[i].getNombre() << endl;
      cout << "Arrival Time: " << procesosGuardados[i].getArrivalTime() << endl;
      cout << "Burst Time: " << procesosGuardados[i].getBurstTime() << endl;
      cout << "Indicador: " << procesosGuardados[i].getIndicador() << endl;
      cout << "\n";
      return true;
    }
  }

  return false;
}

bool ProcesosGuardados::quitarNombreProceso(string nombre){
  string nombreArchivo = nombre + ".txt";
  const char* nombreArchivoCStr  = nombreArchivo.c_str();
  for (int i = 0; i < procesosGuardados.size(); i++){
    if (nombre == procesosGuardados[i].getNombre()){
      if (remove(nombreArchivoCStr) == 0) {
        procesosGuardados.erase(procesosGuardados.begin() + i);
        cout<< "El archivo "<< nombreArchivo << " ha sido eliminado con éxito.\n";
        return true;
      } else {
        perror("Error al intentar eliminar el archivo");
        return false;
      }
    }
  }

  return false;
}

bool ProcesosGuardados::quitarProceso(int indicador){
  for (int i = 0; i < procesosGuardados.size(); i++){
    if (indicador == procesosGuardados[i].getIndicador()){
      string nombre = procesosGuardados[i].getNombre();
      string nombreArchivo = nombre + ".txt";
      const char* nombreArchivoCStr  = nombreArchivo.c_str();
      if (remove(nombreArchivoCStr) == 0) {
        procesosGuardados.erase(procesosGuardados.begin() + i);
        cout<< "El archivo "<< nombreArchivo << " ha sido eliminado con éxito.\n";
        return true;
      } else {
        perror("Error al intentar eliminar el archivo");
        return false;
      }
    }
  }

  return false;
}

void ProcesosGuardados::actualizarProceso(int indicador){
  for (int i = 0; i < procesosGuardados.size(); i++){
    if (indicador == procesosGuardados[i].getIndicador()){
      cout << "Ingrese el atributo que desea cambiar" << endl;
      cout << "1. Nombre" << endl;
      cout << "2. Duración (Burst Time)" << endl;

      int opcion = 0;
      cin >> opcion;
      while (opcion != 1 && opcion != 2){
        cout << "Ingrese una opción válida: ";
        cin >> opcion;
        if (opcion == 1){
          string nombre = "";
          cout << "Ingrese el nuevo nombre: ";
          cin >> nombre;
          procesosGuardados[i].setNombre(nombre);
          break;
        }if (opcion == 2){
          int burstTime = 0;
          cout << "Ingrese la nueva duración: ";
          cin >> burstTime;
          procesosGuardados[i].setBurstTime(burstTime);
          break;
        }
      }
    }
  }
}

void ProcesosGuardados::actualizarNombreProceso(string nombre){
  for (int i = 0; i < procesosGuardados.size(); i++){
    if (nombre == procesosGuardados[i].getNombre()){
      cout << "Ingrese el atributo que desea cambiar" << endl;
      cout << "1. Nombre" << endl;
      cout << "2. Duración (Burst Time)" << endl;

      int opcion = 0;
      cin >> opcion;
      while (opcion != 1 && opcion != 2){
        cout << "Ingrese una opción válida: ";
        cin >> opcion;
        if (opcion == 1){
          string nombre = "";
          cout << "Ingrese el nuevo nombre: ";
          cin >> nombre;
          procesosGuardados[i].setNombre(nombre);
          break;
        }if (opcion == 2){
          int burstTime = 0;
          cout << "Ingrese la nueva duración: ";
          cin >> burstTime;
          procesosGuardados[i].setBurstTime(burstTime);
          break;
        }
      }
    }
  }
}

