#include "Proceso.h"
#include "fstream"
#include "iostream"
#include "string"
#include "vector"
#include "sstream"
using namespace std;

proceso::proceso(string nombre, int arrivalTime, int burstTime, int prioridad, int indicador){
  this->nombre = nombre;
  this->arrivalTime = arrivalTime;
  this->burstTime = burstTime;
  this->prioridad = prioridad;
  this->indicador = indicador;
}

proceso::~proceso(){
}

string proceso::getNombre(){
  return this->nombre;
}

int proceso::getIndicador(){
  return this->indicador;
}

int proceso::getArrivalTime(){
  return this->arrivalTime;
}

int proceso::getBurstTime(){
  return this->burstTime;
}

int proceso::getPrioridad(){
  return this->prioridad;
}

void proceso::setNombre(string nombre){
  this->nombre = nombre;
}

void proceso::setIndicador(int indicador){
  this->indicador = indicador;
}

void proceso::setArrivalTime(int arrivalTime){
  this->arrivalTime = arrivalTime;
}

void proceso::setBurstTime(int burstTime){
  this->burstTime = burstTime;
}

void proceso::setPrioridad(int prioridad){
  this->prioridad = prioridad;
}