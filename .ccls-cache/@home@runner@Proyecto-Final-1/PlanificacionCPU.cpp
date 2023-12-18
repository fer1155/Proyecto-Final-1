#include "PlanificacionCPU.h"
#include "CicloBasico.h"
#include "Proceso.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdlib.h>

PlanificacionCPU::PlanificacionCPU() {
  this->indicador = 0;
}

void PlanificacionCPU::crearProceso() {
  string nombreArchivo;
  cout << "Ingrese el nombre del archivo sin espacios(EJ:proceso1): ";
  cin >> nombreArchivo;
  int burstTime = 0;
  
  //cout << "Ingrese el tiempo de duración del proceso: ";
  //cin >> burstTime;
  
  ofstream archivoCreado(nombreArchivo + ".txt");  
  if(archivoCreado.is_open()) {
    cout << "Ingrese las instrucciones del proceso a crear, por cada "
            "instruccion presione enter. Para finalizar escriba END NULL NULL "
            "NULL NULL\n";
    cin.ignore();
    
    string linea;
    while (getline(cin, linea)) {
      if (linea == "END NULL NULL NULL NULL") {
        archivoCreado << linea;
        break;
      }
      archivoCreado << linea << endl;
    }

    archivoCreado.close();
  } else {
    cerr << "Error al abrir el archivo." << endl;
  }

  int nuevoBursTime = clcburstTime(nombreArchivo+".txt");
  if(nuevoBursTime == -1){
    cout << "El archivo no existe o no se encuentra en la carpeta" << endl;
  }else{
    burstTime = nuevoBursTime;
  }

  indicador++;
  nombreProcesosFIFO.push_back(nombreArchivo);
  //nombreProcesosSJF.push_back(nombreArchivo);
  nombreProcesosSJF2.push_back(nombreArchivo);
  //bursTimeSJF.push_back(burstTime);
  burstTimeGeneral.push_back(burstTime);
  proceso nuevoProceso(nombreArchivo, 0, burstTime, 0, indicador);
  listaProcesos.agregarProceso(nuevoProceso);
}

void PlanificacionCPU::mostrarProcesos() {
  
  int opcion = 0;
  while (opcion != 3) {
    cout << "1. Mostrar todos los procesos." << endl;
    cout << "2. Buscar y mostrar un solo proceso." << endl;
    cout << "3. Regresar al menú principal." << endl;
    cout << "Ingrese una opción válida: ";
    cin >> opcion;
    cout << endl;

    int opcion2 = 0;
    switch(opcion){
      case 1:
        listaProcesos.mostrarTodosProcesos();
        break;
      case 2:
        while (opcion2 != 3){
          cout << "¿Buscar proceso por nombre o Indicador?" << endl;
          cout << "1. Nombre" << endl;
          cout << "2. Indicador" << endl;
          cout << "3. Regresar al menú principal." << endl;
          cout << "Ingrese una opción: ";
          cin >> opcion2;
          cout << endl;
          
          string nombre;
          int indicador;
          switch(opcion2){
            case 1:
              cout << "Ingrese el nombre del proceso: ";
              cin >> nombre;
              if(listaProcesos.buscarNombreProceso(nombre) == false){
                cout << "No se encontró el proceso." << endl;
              }
              break;
            case 2:
              cout << "Ingrese el indicador del proceso: ";
              cin >> indicador;
              if(listaProcesos.buscarProceso(indicador) == false){
                cout << "No se encontró el proceso." << endl;
              }
              break;
            case 3:
              cout << "Saliendo..." << endl;
              break;
            default:
              cout << "Opción inválida." << endl;
              break;
          }
        }
        break;
      case 3:
        cout << "Saliendo..." << endl;
        break;
      default:
        cout << "Opción inválida." << endl;
        break;
    }
  }
}

void PlanificacionCPU::actualizarProcesos(){
  int opcion = 0;
  while (opcion != 3) {
    cout << "Ingrese una opción" << endl;
    cout << "1. Buscar proceso por nombre" << endl;
    cout << "2. Buscar proceso por indicador" << endl;
    cout << "3. Regresar al menú principal" << endl;
    cout << "Ingrese una opción: ";
    cin >> opcion;
    cout << endl;
    
    string nombre;
    int indicador;
    switch(opcion){
      case 1:
        cout << "Ingrese el nombre del proceso a actualizar: " << endl;
        cin >> nombre;
        listaProcesos.actualizarNombreProceso(nombre);
        break;
      case 2:    
        cout << "Ingrese el indicador del proceso a actualizar: " << endl;
        cin >> indicador;
        listaProcesos.actualizarProceso(indicador);
        break;
      case 3:
        cout << "Saliendo..." << endl;
        break;
      default:
        cout << "Opción inválida." << endl;
        break;
    }
  }
}

void PlanificacionCPU::eliminarProceso(){
  int opcion = 0;
  while (opcion != 3) {
    cout << "1. Eliminar proceso por nombre" << endl;
    cout << "2. Eliminar proceso por indicador" << endl;
    cout << "3. Regresar al menú principal" << endl;
    cout << "Ingrese una opción: ";
    cin >> opcion;
    cout << endl;

    string nombreEliminar;
    int indicador;
    switch(opcion){
      case 1:
        cout << "Ingrese el nombre del proceso a eliminar: ";
        cin >> nombreEliminar;

        for(int  i = 0; i < listaProcesos.getVectorProcesosGuardados().size(); i++){
          if(listaProcesos.getVectorProcesosGuardados()[i].getNombre() == nombreEliminar){
            for(int j = 0; j < burstTimeGeneral.size(); j++){
              if(burstTimeGeneral[j] == listaProcesos.getVectorProcesosGuardados()[i].getBurstTime()){
                burstTimeGeneral.erase(burstTimeGeneral.begin() + j);
              }
            }
          }
        }
        
        if(listaProcesos.quitarNombreProceso(nombreEliminar) == false){
          cout << "No se encontró el proceso." << endl;
        }

        for(int i = 0; i < nombreProcesosFIFO.size(); i++){
          if(nombreProcesosFIFO[i] == nombreEliminar){
            nombreProcesosFIFO.erase(nombreProcesosFIFO.begin() + i);
          }
        }

        for(int i = 0; i < nombreProcesosSJF2.size(); i++){
          if(nombreProcesosSJF2[i] == nombreEliminar){
            nombreProcesosSJF2.erase(nombreProcesosSJF2.begin() + i);
          }
        }
        break;
      case 2:
        cout << "Ingrese el indicador del proceso a eliminar: ";
        cin >> indicador;

        for(int i = 0; i < listaProcesos.getVectorProcesosGuardados().size(); i++){
          if(listaProcesos.getVectorProcesosGuardados()[i].getIndicador()  == indicador){
            for(int j = 0; j < burstTimeGeneral.size(); j++){
              if(burstTimeGeneral[j] == listaProcesos.getVectorProcesosGuardados()[i].getBurstTime()){
                burstTimeGeneral.erase(burstTimeGeneral.begin() + j); 
              }
            }    
          }
        }
        
        if(listaProcesos.quitarProceso(indicador) == false){
          cout << "No se encontró el proceso." << endl;
        }

        for(int i = 0; i < listaProcesos.getVectorProcesosGuardados().size(); i++){
          if(listaProcesos.getVectorProcesosGuardados()[i].getIndicador()  == indicador){
            for(int j = 0; j < nombreProcesosFIFO.size(); j++){
              string nombre = listaProcesos.getVectorProcesosGuardados()[i].getNombre();
              if(nombre == nombreProcesosFIFO[j]){
                nombreProcesosFIFO.erase(nombreProcesosFIFO.begin() + j);
              }
            }
          }  
        }

        for(int i = 0; i < listaProcesos.getVectorProcesosGuardados().size(); i++){
          if(listaProcesos.getVectorProcesosGuardados()[i].getIndicador()  == indicador){
            for(int j = 0; j < nombreProcesosSJF2.size(); j++){
              string nombre = listaProcesos.getVectorProcesosGuardados()[i].getNombre();
              if(nombre == nombreProcesosSJF2[j]){
                nombreProcesosSJF2.erase(nombreProcesosSJF2.begin() + j);
              }
            }
          }  
        }
        break;
      case 3:
        cout << "Saliendo..." << endl;
        break;
      default:
        cout << "Opción inválida." << endl;
        break;
    }
  }
}

void PlanificacionCPU::algFifo(){
  int opcion = 0;
  while(opcion != 2){
    cout << "Actualmente estas inicializando el algoritmo FIFO" << endl;
    cout << "1. Iniciar algoritmo" << endl;
    cout << "2. Volver al menu Principal" << endl;
    cout << "Ingrese una opción: ";
    cin >> opcion;
    cout << endl;

    switch(opcion){
      case 1:
        cout << "Iniciando algoritmo FIFO" << endl;
        for(int i = 0; i < listaProcesos.getVectorProcesosGuardados().size(); i++){
          int arrivalTimeNuevo;
          cout << "Ingrese el tiempo de llegada del proceso " << listaProcesos.getVectorProcesosGuardados()[i].getNombre() + ": ";
          cin >> arrivalTimeNuevo;     
          listaProcesos.setArrivalTimeNuevo(arrivalTimeNuevo, i);
          arrivalTimeFIFO.push_back(arrivalTimeNuevo);
        }
        fifo();
        break;
      case 2:
        cout << "Saliendo..." << endl<< endl;
        break;
      default:
        cout << "Opción inválida." << endl;
        break;
    }
  }
}

void PlanificacionCPU::fifo(){
  cout << endl << "Ejecutando FIFO..." << endl;
  int fifo = 0;
  ordenarArrivalTimeFifo();
  bool yaColoco0 = false;
  for(int i = 0; i < nombreProcesosFIFO.size(); i++){
    for(int j = 0; j < listaProcesos.getVectorProcesosGuardados().size(); j++){
      if(listaProcesos.getVectorProcesosGuardados()[j].getNombre() == nombreProcesosFIFO[i]){
        
        burstTimeFifo.push_back(listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());
        burstTimeFifo2.push_back(listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());
        
        if(listaProcesos.getVectorProcesosGuardados()[j].getArrivalTime() == 0){
          int contadorCeros = 0;
          for (int i = 0; i < arrivalTimeFIFO.size(); ++i) {
              if (arrivalTimeFIFO[i] == 0) {
                  contadorCeros++;
              }
          }
          if(contadorCeros > 1){
            if(yaColoco0 == false){
              fifoEjecucion.push_back("0");
              fifo += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
              fifoEjecucion.push_back(to_string(fifo));
              fifoIndicadores.push_back(nombreProcesosFIFO[i]);
              ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
              yaColoco0 = true;
            }else if (yaColoco0 == true){
              fifo += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
              fifoEjecucion.push_back(to_string(fifo));
              fifoIndicadores.push_back(nombreProcesosFIFO[i]);
              ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
            }
          }else if(contadorCeros == 1){
            fifoEjecucion.push_back("0");
            fifo += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
            fifoEjecucion.push_back(to_string(fifo));
            fifoIndicadores.push_back(nombreProcesosFIFO[i]);
            ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
          }
        }else{
          if(arrivalTimeFIFO[i] <= fifo){
            fifo += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
            fifoEjecucion.push_back(to_string(fifo));
            fifoIndicadores.push_back(nombreProcesosFIFO[i]);
            ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
          }else{
            fifoIndicadores.push_back("CPU INUTILIZADA");
            fifoEjecucion.push_back(to_string(arrivalTimeFIFO[i]));
            burstTimeFifo[i] += arrivalTimeFIFO[i] - fifo;
            fifo += arrivalTimeFIFO[i] - fifo;
            fifo += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
            fifoEjecucion.push_back(to_string(fifo));
            fifoIndicadores.push_back(nombreProcesosFIFO[i]);
            ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
          }
        }
      }
    }
  }

  cout << endl << "----------------------------" << endl;
  cout << endl << "Diagrama de Gantt:" << endl << endl;
  int ind = 0;
  for(int i = 0; i < fifoEjecucion.size(); i++){
    cout << fifoEjecucion[i] << "--";
    if(ind < fifoIndicadores.size()){
      cout<<fifoIndicadores[i];
      ind++;
    }
    cout <<"--";
  }

  cout << endl << endl << "Metricas" <<endl;
  cout << endl << "Tiempo de retorno promedio: ";
  float tiempoDeRetornoPromedio = 0;
  double tiempoDeEsperaPromedio = 0;
  int tiempoCompletado = 0;
  for(int i = 0; i < burstTimeFifo.size(); i++){
    if(i == 0){
      tiempoCompletado = burstTimeFifo[i];
    }else{
      tiempoCompletado += burstTimeFifo[i];
    }
    
    tiempoDeRetornoPromedio += tiempoCompletado - arrivalTimeFIFO[i];
    tiempoDeEsperaPromedio += (tiempoCompletado - arrivalTimeFIFO[i]) - burstTimeFifo2[i];;
  }
  cout << tiempoDeRetornoPromedio/nombreProcesosFIFO.size() << endl << endl;

  cout << "Tiempo de espera promedio: ";
  cout << tiempoDeEsperaPromedio/nombreProcesosFIFO.size() << endl;
  cout << endl << "----------------------------" << endl;
  cout << endl << "FIFO ejecutado" << endl << endl;

  fifoEjecucion.clear();
  fifoIndicadores.clear();
  burstTimeFifo.clear();
  burstTimeFifo2.clear();
  arrivalTimeFIFO.clear();
}

void PlanificacionCPU::ordenarArrivalTimeFifo(){
  size_t n = arrivalTimeFIFO.size();

  // Crear un vector de pares para almacenar números e identificadores juntos
  vector<pair<int, string>> pairedVector;

  for (size_t i = 0; i < n; ++i) {
    pairedVector.push_back(make_pair(arrivalTimeFIFO[i], nombreProcesosFIFO[i]));
  }

  // Ordenar el vector de pares basándose en el primer elemento (los números)
  sort(pairedVector.begin(), pairedVector.end());

  // Actualizar los vectores originales con los elementos ordenados
  for (size_t i = 0; i < n; ++i) {
      arrivalTimeFIFO[i] = pairedVector[i].first;
      nombreProcesosFIFO[i] = pairedVector[i].second;
  }
}

void PlanificacionCPU::algSJF(){
  int opcion = 0;
  while(opcion != 2){
    cout << "Actualmente estas inicializando el algoritmo SJN" << endl;
    cout << "1. Iniciar algoritmo" << endl;
    cout << "2. Volver al menu Principal" << endl;
    cout << "Ingrese una opción: ";
    cin >> opcion;
    cout << endl;

    switch(opcion){
      case 1:
        cout << endl << "Iniciando algoritmo SJN" << endl;

        for(int i = 0; i < nombreProcesosFIFO.size(); i++){
          nombreProcesosSJF.push_back(nombreProcesosFIFO[i]);
        }

        for(int i = 0; i < burstTimeGeneral.size(); i++){
          bursTimeSJF.push_back(burstTimeGeneral[i]);
        }
        
        for(int i = 0; i < listaProcesos.getVectorProcesosGuardados().size(); i++){
          int arrivalTimeNuevo;
          cout << "Ingrese el tiempo de llegada del proceso " << listaProcesos.getVectorProcesosGuardados()[i].getNombre() + ": ";
          cin >> arrivalTimeNuevo;     
          listaProcesos.setArrivalTimeNuevo(arrivalTimeNuevo, i);
          arrivalTimeSJF.push_back(arrivalTimeNuevo);
          arrivalTimeSJF2.push_back(arrivalTimeNuevo);
          //burstTimeSJN.push_back(listaProcesos.getVectorProcesosGuardados()[i].getBurstTime());
        }
        sjf();
        break;
      case 2:
        cout << "Saliendo..." << endl<< endl;
        break;
      default:
        cout << "Opción inválida." << endl;
        break;
    }
  }  
}

void PlanificacionCPU::sjf(){
  cout << "Ejecutando SJN..." << endl;
  int sjf = 0;
  ordenarArrivalTimeSJF();

  int contadorCeros = 0;
  for (int i = 0; i < arrivalTimeSJF.size(); ++i) {
    if (arrivalTimeSJF[i] == 0) {
      contadorCeros++;
    }
  }
  
  if(contadorCeros > 1){
    if(contadorCeros == arrivalTimeSJF.size()){
      nombreProcesosSJF.clear();
      //Reasignar nombreProcesosSJF
      for(int i = 0; i < listaProcesos.getVectorProcesosGuardados().size(); i++){
        for(int j = 0; j < bursTimeSJF.size(); j++){
          if(listaProcesos.getVectorProcesosGuardados()[i].getBurstTime() == bursTimeSJF[j]){
            nombreProcesosSJF.push_back(listaProcesos.getVectorProcesosGuardados()[i].getNombre());
          }
        }
      }
      
      ordenarBursTimeSJF();

      bool salir = false;
      for(int i = 0; i < nombreProcesosSJF.size() && !salir; i++){
        for(int j = 0; j < listaProcesos.getVectorProcesosGuardados().size(); j++){
          if(listaProcesos.getVectorProcesosGuardados()[j].getNombre() == nombreProcesosSJF[i]){
            bursTimeSJF2.push_back(listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());
            arrivalTimeSJF2.push_back(listaProcesos.getVectorProcesosGuardados()[j].getArrivalTime());
            sjfEjecucion.push_back("0");
            sjf += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
            sjfEjecucion.push_back(to_string(sjf));
            sjfIndicadores.push_back(nombreProcesosSJF[i]);
            ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
            salir = true;
            nombreProcesosSJF.erase(nombreProcesosSJF.begin() + i);
            bursTimeSJF.erase(bursTimeSJF.begin() + i);
            break;
          }
        }
      }
      
      arrivalTimeSJF.erase(arrivalTimeSJF.begin() + 0);
      
      for(int i = 0; i < nombreProcesosSJF.size(); i++){
        for(int j = 0; j < listaProcesos.getVectorProcesosGuardados().size(); j++){
          if(listaProcesos.getVectorProcesosGuardados()[j].getNombre() == nombreProcesosSJF[i]){
            bursTimeSJF2.push_back(listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());
            arrivalTimeSJF2.push_back(listaProcesos.getVectorProcesosGuardados()[j].getArrivalTime());
            if(arrivalTimeSJF[i] <= sjf){
              sjf += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
              sjfEjecucion.push_back(to_string(sjf));
              sjfIndicadores.push_back(nombreProcesosSJF[i]);
              ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
            }else{
              sjfIndicadores.push_back("CPU INUTILIZADA");
              sjfEjecucion.push_back(to_string(arrivalTimeSJF[i]));
              bursTimeSJF[i] += arrivalTimeSJF[i] - sjf;
              bursTimeSJF2[i+1] += arrivalTimeSJF[i] - sjf;
              sjf += arrivalTimeSJF[i] - sjf;
              sjf += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
              sjfEjecucion.push_back(to_string(sjf));
              sjfIndicadores.push_back(nombreProcesosSJF[i]);
              ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
            }
          }
        }
      }
    }
  }else if (contadorCeros == 1){
    bool salir = false;
    for(int i = 0; i < nombreProcesosSJF.size() && !salir; i++){
      for(int j = 0; j < listaProcesos.getVectorProcesosGuardados().size(); j++){
        if(listaProcesos.getVectorProcesosGuardados()[j].getArrivalTime() == 0){
          bursTimeSJF2.push_back(listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());
          arrivalTimeSJF2.push_back(listaProcesos.getVectorProcesosGuardados()[j].getArrivalTime());
          sjfEjecucion.push_back("0");
          sjf += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
          sjfEjecucion.push_back(to_string(sjf));
          sjfIndicadores.push_back(nombreProcesosSJF[i]);
          ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
          salir = true;
          break;
        }
      }
    }

    arrivalTimeSJF.erase(arrivalTimeSJF.begin() + 0);

    //ELIMINAR DEL BURST TIME EL ARRIVVAL TIME 0
    for(int i = 0; i < nombreProcesosSJF.size(); i++){
      for(int j = 0; j < listaProcesos.getVectorProcesosGuardados().size(); j++){
        if(listaProcesos.getVectorProcesosGuardados()[j].getNombre() == nombreProcesosSJF[i]){
          if(listaProcesos.getVectorProcesosGuardados()[j].getArrivalTime() == 0){  
            bursTimeSJF.erase(bursTimeSJF.begin() + i);
            nombreProcesosSJF.erase(nombreProcesosSJF.begin() + 0);
          }
        }
      }
    }

    nombreProcesosSJF.clear();
    //Reasignar nombreProcesosSJF
    for(int i = 0; i < listaProcesos.getVectorProcesosGuardados().size(); i++){
      for(int j = 0; j < bursTimeSJF.size(); j++){
        if(listaProcesos.getVectorProcesosGuardados()[i].getBurstTime() == bursTimeSJF[j]){
          nombreProcesosSJF.push_back(listaProcesos.getVectorProcesosGuardados()[i].getNombre());
        }
      }
    }
    ordenarBursTimeSJF();

    for(int i = 0; i < nombreProcesosSJF.size(); i++){
      for(int j = 0; j < listaProcesos.getVectorProcesosGuardados().size(); j++){
        if(listaProcesos.getVectorProcesosGuardados()[j].getNombre() == nombreProcesosSJF[i]){
          bursTimeSJF2.push_back(listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());
          arrivalTimeSJF2.push_back(listaProcesos.getVectorProcesosGuardados()[j].getArrivalTime());
          
          if(arrivalTimeSJF[i] <= sjf){
            sjf += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
            sjfEjecucion.push_back(to_string(sjf));
            sjfIndicadores.push_back(nombreProcesosSJF[i]);
            ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
          }else{
            sjfIndicadores.push_back("CPU INUTILIZADA");
            sjfEjecucion.push_back(to_string(arrivalTimeSJF[i]));
            bursTimeSJF[i] += arrivalTimeSJF[i] - sjf;
            //bursTimeSJF2[i+1] += arrivalTimeSJF[i] - sjf;
            sjf += arrivalTimeSJF[i] - sjf;
            sjf += listaProcesos.getVectorProcesosGuardados()[j].getBurstTime();
            sjfEjecucion.push_back(to_string(sjf));
            sjfIndicadores.push_back(nombreProcesosSJF[i]);
            ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[j].getNombre() + ".txt");
          }
        }
      }
    }
  }

  cout << endl << "----------------------------" << endl;
  cout << endl << "Diagrama de Gantt:" << endl << endl;
  int ind = 0;
  for(int i = 0; i < sjfEjecucion.size(); i++){
    cout << sjfEjecucion[i] << "--";
    if(ind < sjfIndicadores.size()){
      cout << sjfIndicadores[i];
      ind++;
    }
    cout <<"--";
  }
  cout << endl << endl << "Metricas" <<endl;
  
  float tiempoDeRetornoPromedio = 0;
  double tiempoDeEsperaPromedio = 0;
  int tiempoCompletado = 0;
  for(int i = 0; i < bursTimeSJF2.size(); i++){
    if(i == 0){
      tiempoCompletado = bursTimeSJF2[i];
    }else{
      tiempoCompletado += bursTimeSJF2[i];
    }

    tiempoDeRetornoPromedio += tiempoCompletado - arrivalTimeSJF2[i];
    //cout << "Arrival:" << arrivalTimeSJF2[i] << " Burst:" << bursTimeSJF2[i] << endl;
    //cout << "Time: " << tiempoDeRetornoPromedio;
    tiempoDeEsperaPromedio += (tiempoCompletado - arrivalTimeSJF2[i]) - bursTimeSJF2[i];;
  }
  cout << endl << "Tiempo de retorno promedio: ";
  cout << tiempoDeRetornoPromedio/nombreProcesosSJF2.size() << endl << endl;
  
  cout << "Tiempo de espera promedio: ";
  cout << tiempoDeEsperaPromedio/nombreProcesosSJF2.size() << endl;
  cout << endl << "----------------------------" << endl;
  cout << "SJF ejecutado" << endl << endl;

  sjfEjecucion.clear();
  sjfIndicadores.clear();
  bursTimeSJF.clear();
  bursTimeSJF2.clear();
  bursTimeSJF3.clear();
  arrivalTimeSJF.clear();
  arrivalTimeSJF2.clear();
  nombreProcesosSJF.clear();
  //nombreProcesosSJF2.clear();
}

void PlanificacionCPU::ordenarArrivalTimeSJF(){
  size_t n = arrivalTimeSJF.size();

  // Crear un vector de pares para almacenar números e identificadores juntos
  vector<pair<int, string>> pairedVector;

  for (size_t i = 0; i < n; ++i) {
    pairedVector.push_back(make_pair(arrivalTimeSJF[i], nombreProcesosSJF[i]));
  }

  // Ordenar el vector de pares basándose en el primer elemento (los números)
  sort(pairedVector.begin(), pairedVector.end());

  // Actualizar los vectores originales con los elementos ordenados
  for (size_t i = 0; i < n; ++i) {
      arrivalTimeSJF[i] = pairedVector[i].first;
      nombreProcesosSJF[i] = pairedVector[i].second;
  }
}

void PlanificacionCPU::ordenarBursTimeSJF(){
  size_t n = bursTimeSJF.size();

  // Crear un vector de pares para almacenar números e identificadores juntos
  vector<pair<int, string>> pairedVector;

  for (size_t i = 0; i < n; ++i) {
    pairedVector.push_back(make_pair(bursTimeSJF[i], nombreProcesosSJF[i]));
  }

  // Ordenar el vector de pares basándose en el primer elemento (los números)
  sort(pairedVector.begin(), pairedVector.end());

  // Actualizar los vectores originales con los elementos ordenados
  for (size_t i = 0; i < n; ++i) {
      bursTimeSJF[i] = pairedVector[i].first;
      nombreProcesosSJF[i] = pairedVector[i].second;
  }
}

int PlanificacionCPU::clcburstTime(string nombreArchivo){

  // Abrir el archivo en modo lectura
  ifstream archivo(nombreArchivo);

  // Verificar si el archivo se abrió correctamente
  if (!archivo.is_open()) {
      cerr << "Error al abrir el archivo." << endl;
      return -1;
  }

  // Contador de líneas
  int contadorLineas = 0;
  string linea;

  // Leer el archivo línea por línea y contar las líneas
  while (getline(archivo, linea)) {
      contadorLineas++;
  }

  // Mostrar la cantidad de líneas
  cout << "El archivo tiene " << contadorLineas << " lineas." << std::endl;

  // Cerrar el archivo
  archivo.close();

  return contadorLineas;
}

void PlanificacionCPU::algRR(){
  int opcion = 0;
  while(opcion != 2){
    cout << "Actualmente estas inicializando el algoritmo RR" << endl;
    cout << "1. Iniciar algoritmo" << endl;
    cout << "2. Volver al menu Principal" << endl;
    cout << "Ingrese una opción: ";
    cin >> opcion;
    cout << endl;

    switch(opcion){
      case 1:
        cout << "Iniciando algoritmo RR" << endl;

        for(int i = 0; i < nombreProcesosFIFO.size(); i++){
          nombreProcesosRR.push_back(nombreProcesosFIFO[i]);
        }

        for(int i = 0; i < burstTimeGeneral.size(); i++){
          burstTimeRR.push_back(burstTimeGeneral[i]);
        }
        
        for(int i = 0; i < listaProcesos.getVectorProcesosGuardados().size(); i++){
          int arrivalTimeNuevo;
          cout << "Ingrese el tiempo de llegada del proceso " << listaProcesos.getVectorProcesosGuardados()[i].getNombre() + ": ";
          cin >> arrivalTimeNuevo;     
          listaProcesos.setArrivalTimeNuevo(arrivalTimeNuevo, i);
          arrivalTimeRR.push_back(arrivalTimeNuevo);
        }
        cout << "Ingrese el quantum a utilizar: ";
        cin >> quantum;
        rr();
        break;
      case 2:
        cout << "Saliendo..." << endl;
        break;
      default:
        cout << "Opción inválida." << endl;
        break;
    }
  }
}

void PlanificacionCPU::rr(){
  cout << "Ejecutando RR..." << endl;
  int rr = 0;
  int contadorCeros = 0;

  cout << endl <<"Ejecucion General de todos los procesos" << endl;
  for(int i = 0; i < listaProcesos.getVectorProcesosGuardados().size(); i++){
    ejecutarCicloBasico(listaProcesos.getVectorProcesosGuardados()[i].getNombre() + ".txt");
  }
  
  for (int i = 0; i < arrivalTimeRR.size(); ++i) {
    if (arrivalTimeRR[i] == 0) {
      contadorCeros++;
    }
  }

  if(contadorCeros > 1){
    bool salir = false;
    retry1:

    while(!burstTimeRR.empty()){
      for(int i = 0; i < nombreProcesosRR.size(); i++){
        for(int j = 0; j < listaProcesos.getVectorProcesosGuardados().size(); j++){
          if(listaProcesos.getVectorProcesosGuardados()[j].getNombre() == nombreProcesosRR[i]){
            if(salir == false){
              salir = true;
              rrEjecucion.push_back("0");
              int burstEjecutado = calcularRestaQuantum(burstTimeRR[i], quantum);
              rr += burstEjecutado;
              rrEjecucion.push_back(to_string(rr));
              rrIndicadores.push_back(nombreProcesosRR[i]);
              int indSiSeCumplio = restarBusrtTime(i, burstEjecutado, rr, arrivalTimeRR[i], listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());
              if (indSiSeCumplio == 1) {
                  // Utilizar goto para volver a la etiqueta "retry"
                  goto retry1;
              }
            }else if(salir == true){
              int burstEjecutado = calcularRestaQuantum(burstTimeRR[i], quantum);
              rr += burstEjecutado;
              rrEjecucion.push_back(to_string(rr));
              rrIndicadores.push_back(nombreProcesosRR[i]);
              int indSiSeCumplio = restarBusrtTime(i, burstEjecutado, rr, arrivalTimeRR[i], listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());
              if (indSiSeCumplio == 1) {
                // Utilizar goto para volver a la etiqueta "retry"
                goto retry1;
              }
            }
          }
        }
      }
    }    
  }else if(contadorCeros == 1){
    ordenarArrivalTimeRR();
    bool salir = false;
    retry2:
    
    while(!burstTimeRR.empty()){
      for(int i = 0; i < nombreProcesosRR.size(); i++){
        for(int j = 0; j < listaProcesos.getVectorProcesosGuardados().size(); j++){
          if(listaProcesos.getVectorProcesosGuardados()[j].getNombre() == nombreProcesosRR[i]){
            if(arrivalTimeRR[i] == 0 && salir == false){
              salir = true;
              rrEjecucion.push_back("0");
              int burstEjecutado = calcularRestaQuantum(burstTimeRR[i], quantum);
              rr += burstEjecutado;
              rrEjecucion.push_back(to_string(rr));
              rrIndicadores.push_back(nombreProcesosRR[i]);
              int indSiSeCumplio = restarBusrtTime(i, burstEjecutado, rr, arrivalTimeRR[i], listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());
              if (indSiSeCumplio == 1) {
                  // Utilizar goto para volver a la etiqueta "retry"
                  goto retry2;
              }
            }else if(salir == true){
               if(arrivalTimeRR[i] <= rr){
                 int burstEjecutado = calcularRestaQuantum(burstTimeRR[i], quantum);
                 rr += burstEjecutado;
                 //cout << burstEjecutado;
                 rrEjecucion.push_back(to_string(rr));
                 rrIndicadores.push_back(nombreProcesosRR[i]);
                 int indSiSeCumplio = restarBusrtTime(i, burstEjecutado, rr, arrivalTimeRR[i], listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());
                 if (indSiSeCumplio == 1) {
                      // Utilizar goto para volver a la etiqueta "retry"
                      goto retry2;
                  }
               }else{
                 rrIndicadores.push_back("CPU INUTILIZADA");
                 rrEjecucion.push_back(to_string(arrivalTimeRR[i]));
                 //burstTimeRR[i] += arrivalTimeRR[i] - rr;
                 rr += arrivalTimeRR[i] - rr;
                 int burstEjecutado = calcularRestaQuantum(burstTimeRR[i], quantum);
                 rr += burstEjecutado;
                 rrEjecucion.push_back(to_string(rr));
                 rrIndicadores.push_back(nombreProcesosRR[i]);
                 int indSiSeCumplio = restarBusrtTime(i, burstEjecutado, rr, arrivalTimeRR[i], listaProcesos.getVectorProcesosGuardados()[j].getBurstTime());   
                 if (indSiSeCumplio == 1) {
                      // Utilizar goto para volver a la etiqueta "retry"
                      goto retry2;
                  }
               }
            }
          }
        }
      }
    }
  }

  cout << endl << "----------------------------" << endl;
  cout << endl << "Diagrama de Gantt:" << endl << endl;
  int ind = 0;
  for(int i = 0; i < rrEjecucion.size(); i++){
    cout << rrEjecucion[i] << "--";
    if(ind < rrIndicadores.size()){
      cout << rrIndicadores[i];
      ind++;
    }
    cout <<"--";
  }

  cout << endl << endl << "Metricas" <<endl;
  float tiempoDeRetornoPromedio = 0;
  double tiempoDeEsperaPromedio = 0;
  int tiempoCompletado = 0;
  for(int i = 0; i < tiempoCompletadoProcesosTerminados.size(); i++){
    tiempoCompletado = tiempoCompletadoProcesosTerminados[i];

    tiempoDeRetornoPromedio += tiempoCompletado - arrivalTimeRR2[i];
    tiempoDeEsperaPromedio += (tiempoCompletado - arrivalTimeRR2[i]) - burstTimeRR2[i];
  }
  
  cout << endl << "Tiempo de retorno promedio: ";
  cout << tiempoDeRetornoPromedio/burstTimeGeneral.size() << endl << endl;
  
  cout << "Tiempo de espera promedio: ";
  cout << tiempoDeEsperaPromedio/burstTimeGeneral.size() << endl;
  cout << endl << "----------------------------" << endl;
  cout << endl <<"RR ejecutado" << endl << endl;

  rrEjecucion.clear();
  rrIndicadores.clear();
  burstTimeRR.clear();
  burstTimeRR2.clear();
  arrivalTimeRR.clear();
  nombreProcesosRR.clear();
  tiempoCompletadoProcesosTerminados.clear();
  arrivalTimeRR2.clear();
}

void PlanificacionCPU::ordenarArrivalTimeRR(){
  size_t n = arrivalTimeRR.size();

  // Crear un vector de pares para almacenar números e identificadores juntos
  vector<tuple<int, string, int>> tupleVector;

  for (size_t i = 0; i < n; ++i) {
    tupleVector.push_back(make_tuple(arrivalTimeRR[i], nombreProcesosRR[i], burstTimeRR[i]));
  }

  // Ordenar el vector de pares basándose en el primer elemento (los números)
  sort(tupleVector.begin(), tupleVector.end());

  // Actualizar los vectores originales con los elementos ordenados
  for (size_t i = 0; i < n; ++i) {
      arrivalTimeRR[i] = get<0>(tupleVector[i]);
      nombreProcesosRR[i] = get<1>(tupleVector[i]);
        burstTimeRR[i] = get<2>(tupleVector[i]);
  }
}

int PlanificacionCPU::calcularRestaQuantum(int bursTimeDelProceso, int quantum){
  int burstTimeRestante = bursTimeDelProceso - quantum;

  if(burstTimeRestante > 0){
    return quantum;
  }else if(burstTimeRestante < 0){
    return burstTimeRestante + quantum;
  }else if (burstTimeRestante == 0){
    return quantum;
  }
  return -1;
}

int PlanificacionCPU::restarBusrtTime(int posicion, int numRestar, int tiempoCompletado, int arrivalDelTiempoCompletado, int burstTimeDelTiempoCompletado){
  burstTimeRR[posicion] -= numRestar;

  if(burstTimeRR[posicion] <= 0){
    burstTimeRR.erase(burstTimeRR.begin() + posicion);
    burstTimeRR2.push_back(burstTimeDelTiempoCompletado);
    nombreProcesosRR.erase(nombreProcesosRR.begin() + posicion);
    tiempoCompletadoProcesosTerminados.push_back(tiempoCompletado);
    arrivalTimeRR2.push_back(arrivalDelTiempoCompletado);
    arrivalTimeRR.erase(arrivalTimeRR.begin() + posicion);
    return 1;
  }
  return 0;
}

int PlanificacionCPU::ejecutarCicloBasico(string nombreArchivo){
  CicloBasico cicloBasico1("Ciclo basico de instruccion");
  //cicloBasico1.mostrarMenu();

  int idInstruccion = 0;

  ifstream archivo(nombreArchivo);

  if (!archivo.is_open()) {
    cerr << "No se pudo abrir el archivo" << endl;
    return 1; //Termina el programa con un código de error
  }

  cout << endl<< "-------------------------------" << endl;
  cout << "Accediendo a " +  nombreArchivo + "..."<< endl;
  cout << "Accediendo a " +  nombreArchivo + "..."<< endl;
  cout << "Accediendo a " +  nombreArchivo + "..."<< endl  << endl;

  string linea;
  while (getline(archivo, linea)) {
    //Vector para almacenar las partes de cada linea
    vector<string> partes;

    //istringstream para dividir la cadena en partes
    istringstream stream(linea);
    string parte;

    // Lee cada palabra y la agrega al vector
    while (stream >> parte) {
      partes.push_back(parte);
    }

    string instruccion = partes[0];

    if(instruccion == "N"){
      cout << "No hay linea" << endl;
    }else if(instruccion == "SET") {

      cout << "Asignando valor de memoria con SET ";
      string direccionEnMemoria = partes[1];
      string valor = partes[2];
      cicloBasico1.setValores(direccionEnMemoria, valor);
      cout << valor + " -> " + direccionEnMemoria << endl;

    }else if(instruccion != "SET" and instruccion != "PAUSE" and instruccion !="END"){

      cout << "\nIniciando ejecucion de la linea " + instruccion << endl;
      string valor1 = partes[1];
      string valor2 = partes[2];
      string valor3 = partes[3];
      string valor4 = partes[4];

      cicloBasico1.setInstrucciones(idInstruccion, instruccion, valor1, valor2, valor3, valor4);
      cicloBasico1.ejecucionDeCicloBasico();
      idInstruccion++;

    }else if (instruccion == "PAUSE"){

      while(true){
        string opcion;
        cout << "\nPausa\n" << endl;
        cicloBasico1.funcionalidadPause();
        cout << "¿Desea salir de la pausa? (S/N): ";
        cin >> opcion;

        if(opcion == "S"){
          break;
        }
      } 

    }else if (instruccion == "END"){

      cout << "\nFinalizacion del programa, ¡hasta la proxima!" << endl << endl;
      break;

    }
  }
  return 0;
}

ProcesosGuardados PlanificacionCPU::getlistaProcesos(){
  return listaProcesos;
}

void PlanificacionCPU::mostrarMenu(){
  cout << "●┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅●"<<endl;
  cout << "│                Bienvenid@ al simulador de                │"<<endl;
  cout << "│                                                          │"<<endl;
  cout << "│                •  Planificación de CPU  •                │"<<endl;
  cout << "│                                                          │"<<endl;
  cout << "●┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅●"<<endl;
  cout << "│                                                          │"<<endl;  
  cout << "│               Fernando Cardona - 2241381                 │"<<endl;
  cout << "│                  Oscar Muñoz - 2242481                   │"<<endl;
  cout << "│                Santiago Alzate - 2242274                 │"<<endl;
  cout << "│                                                          │"<<endl;
  cout << "●┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅┅●"<<endl<<endl;

  cout << "¡Revise el archivo instrucciones.txt antes de iniciar!"<<endl<<endl;
}