#ifndef PLANIFICACIONCPU_H
#define PLANIFICACIONCPU_H

#include <string>
#include "Proceso.h"
#include "ProcesosGuardados.h"
#include "CicloBasico.h"

using namespace std;

class PlanificacionCPU{
  private:
    ProcesosGuardados listaProcesos;
    vector<int> burstTimeGeneral;
    
    vector<int> arrivalTimeFIFO;
    vector<string> nombreProcesosFIFO;
    vector<string> fifoEjecucion;
    vector<string> fifoIndicadores;
    vector<int> burstTimeFifo;
    vector<int> burstTimeFifo2;
    
    vector<int> arrivalTimeSJF;
    vector<int> arrivalTimeSJF2;
    vector<int> bursTimeSJF;
    vector<string> nombreProcesosSJF;
    vector<string> nombreProcesosSJF2;
    vector<string> sjfEjecucion;
    vector<string> sjfIndicadores;
    vector<int> bursTimeSJF2;
    vector<int> bursTimeSJF3;

    vector<int> arrivalTimeRR;
    vector<string> nombreProcesosRR;
    vector<string> rrEjecucion;
    vector<string> rrIndicadores;
    vector<int> burstTimeRR;
    vector<int> burstTimeRR2;
    vector<int> tiempoCompletadoProcesosTerminados;
    vector<int> arrivalTimeRR2;
    int quantum;
    int indicador;
    //vector<proceso> listaProcesosGuardados;

  public:
    PlanificacionCPU();
    virtual void crearProceso();
    int clcburstTime(string nombre);
    virtual void mostrarProcesos();
    virtual void actualizarProcesos();
    virtual void eliminarProceso();
    virtual ProcesosGuardados getlistaProcesos();
    
    virtual void algFifo();
    virtual void fifo();
    virtual void ordenarArrivalTimeFifo();
    
    virtual void algSJF();
    virtual void sjf();
    virtual void ordenarArrivalTimeSJF();
    virtual void ordenarBursTimeSJF();
    
    virtual void algRR();
    virtual void rr();
    virtual void ordenarArrivalTimeRR();
    //virtual void ordenarQuantum();
    virtual int calcularRestaQuantum(int bursTimeDelProceso, int quantum);
    virtual int restarBusrtTime(int posicion, int numRestar, int tiempoCompletado, int arrivalDelTiempoCompletado, int burstTimeDelTiempoCompletado);

    virtual int ejecutarCicloBasico(string nombreArchivo);
    virtual void mostrarMenu();
};

#else
class PlanificacionCPU; 
#endif