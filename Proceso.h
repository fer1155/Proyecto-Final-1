#ifndef Proceso_H
#define Proceso_H


#include <string>
using namespace std;

class proceso{
  private:
    string nombre;
    int indicador;
    int burstTime;
    int prioridad;
    
  public:
    int arrivalTime;
    proceso(string nombre, int arrivalTime, int burstTime, int prioridad, int indicador);
    ~proceso();

    string getNombre();
    int getArrivalTime();
    int getBurstTime();
    int getPrioridad();
    int getIndicador();

    void setNombre(string nombre);
    void setIndicador(int indicador);
    void setBurstTime(int burstTime);
    void setPrioridad(int prioridad);
    void setArrivalTime(int arrivalTime);

};

#endif