#include <iostream>
#include "PlanificacionCPU.h"
#include "Proceso.h"
#include <cstdlib>
using namespace std;

int main() {
  PlanificacionCPU manejoDeProcesos;
  manejoDeProcesos.mostrarMenu();
  
  int opcion = 1;
  while(opcion != 0){
    cout << "1. Crear Proceso" << endl;
    cout << "2. Mostrar Procesos" << endl;
    //cout << "3. Actualizar Procesos" << endl;
    cout << "3. Eliminar proceso" << endl;
    cout << "4. Ejecutar Procesos" << endl;
    cout << "Ingrese una opción: ";
    cin >> opcion;
    cout << endl;

    int opcion2 = 0;
    switch(opcion){
      case 1:
        cout << "\033[2J\033[H";
        manejoDeProcesos.crearProceso();
        break;
      case 2:
        cout << "\033[2J\033[H";
        manejoDeProcesos.mostrarProcesos();
        break;
      //case 3:
        //manejoDeProcesos.actualizarProcesos();
        //cout << "en prueba";
        //break;
      case 3:  
        cout << "\033[2J\033[H";
        manejoDeProcesos.eliminarProceso();
        break;
      case 4:
        cout << "\033[2J\033[H";
        while (opcion2 != 4){
          cout << "¿Qué algoritmo desea utilizar?" << endl;
          cout << "1. Algoritmo FCFS" << endl;
          cout << "2. Algoritmo SJN" << endl;
          cout << "3. Algoritmo Round Robin" << endl;
          cout << "4. Salir del menu principal" << endl;
          cout << "Ingrese una opción:";
          cin >> opcion2;
          cout << endl;
          
          switch(opcion2){
            case 1:
              cout << "\033[2J\033[H";
              manejoDeProcesos.algFifo();
              break;
            case 2:
              cout << "\033[2J\033[H";
              manejoDeProcesos.algSJF();
              break;
            case 3:
              cout << "\033[2J\033[H";
              //manejoDeProcesos.algRoundRobin();
              break;
            case 4:
              cout << "\033[2J\033[H";
              cout << "Saliendo..." << endl;
              break;
            default:
              cout << "Opción inválida. Intente de nuevo." << endl;
          }
        }
        break;
      case 0:
        cout << "Saliendo..." << endl;
        break;
      default:
        cout << "Opción inválida." << endl;
    }
  }

  
  for(int i = 0; i < manejoDeProcesos.getlistaProcesos().getVectorProcesosGuardados().size(); i++){
    string nombre = manejoDeProcesos.getlistaProcesos().getVectorProcesosGuardados()[i].getNombre() + ".txt";
    const char* nombreArchivo = nombre.c_str();
    if (remove(nombreArchivo) == 0) {
        printf("Archivo %s eliminado exitosamente.\n", nombreArchivo);
    } else {
        perror("Error al intentar eliminar el archivo");
    }
  }
  
  return 0;
}