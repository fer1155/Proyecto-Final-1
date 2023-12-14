#include "CicloBasico.h"
#include <iostream>
#include <cstring>
#include <vector>

//Constructor
CicloBasico::CicloBasico(string nombre){
  this -> nombre = nombre;
  this -> varAcumulador = 0;
  this -> PC = 0;
}

void CicloBasico::setValores(string direccionDeMemoria, string valor){
   memoriaPrincipalValores[direccionDeMemoria] = stoi(valor);
}

void CicloBasico::setInstrucciones(int idInstruccion, string instruccion, string valor1, string valor2, string valor3, string valor4){
  memoriaPrincipalInstrucciones[idInstruccion] = {instruccion, valor1, valor2, valor3, valor4};
}

void CicloBasico::ejecucionDeCicloBasico(){
  if(PC < memoriaPrincipalInstrucciones.size()){
    funcionalidadMAR();
    funcionalidadMDR("Instruccion");
    funcionalidadICR();
    funcionalidadUC();
  }
}

void CicloBasico::funcionalidadPC(){
  PC++;
}

void CicloBasico::funcionalidadMAR(){
  MAR = to_string(PC);
}

void CicloBasico::funcionalidadMDR(string tipo){
  if(tipo == "Instruccion"){
    MDR1 = memoriaPrincipalInstrucciones[stoi(MAR)];
    asignarMDR(MDR1[0] + MDR1[1] + MDR1[2] + MDR1[3] + MDR1[4]);
  }else if (tipo == "ObtenerValor"){
    MDR2 = memoriaPrincipalValores[MAR];
    asignarMDR(to_string(MDR2));
  }else if(tipo == "AsignarValor"){
    memoriaPrincipalValores[MAR] += acumulador(MDR2);
  }else if(tipo == "ColocarValor"){
    memoriaPrincipalValores[MAR] = varAcumulador;
  }
}

void CicloBasico::funcionalidadICR(){
  ICR = MDR1;
  funcionalidadPC();
}

void CicloBasico::funcionalidadUC(){
  UC = ICR;

  string instruccion = UC[0];
  string valor1 = UC[1];
  string valor2 = UC[2];
  string valor3 = UC[3];
  string valor4 = UC[4];

  if(instruccion == "LDR"){
    ldr(valor1);
  }else if(instruccion == "ADD"){
    add(valor1, valor2, valor3);
  }else if(instruccion == "INC"){
    inc(valor1);
  }else if(instruccion == "DEC"){
    dec(valor1);
  }else if(instruccion == "STR"){
    str(valor1);
  }else if(instruccion == "SHW"){
    shw(valor1);
  }
}

int CicloBasico::acumulador(int valor){
  funcionalidadALU(valor);
  return varAcumulador;
}

void CicloBasico::funcionalidadALU(int valor){
  varAcumulador += valor;
}

void CicloBasico::ldr(string direccionDeMemoria){
  MAR = direccionDeMemoria;
  funcionalidadMDR("ObtenerValor");
  varAcumulador = 0;
  acumulador(MDR2);
}

void CicloBasico::add(string direccionDeMemoria, string direccionDeMemoria2, string direccionDeMemoria3){
  if(direccionDeMemoria2 == "NULL" and direccionDeMemoria3 == "NULL"){
    MAR = direccionDeMemoria;
    funcionalidadMDR("ObtenerValor");
    acumulador(MDR2);
  }else if(direccionDeMemoria2 != "NULL" and direccionDeMemoria3 == "NULL"){
    MAR = direccionDeMemoria;
    funcionalidadMDR("ObtenerValor");
    MAR = direccionDeMemoria2;
    funcionalidadMDR("AsignarValor");
  }else if(direccionDeMemoria2 != "NULL" and direccionDeMemoria3 != "NULL"){
    MAR = direccionDeMemoria;
    funcionalidadMDR("ObtenerValor");
    acumulador(MDR2);
    MAR = direccionDeMemoria2;
    funcionalidadMDR("ObtenerValor");
    acumulador(MDR2);
    MAR = direccionDeMemoria3;
    funcionalidadMDR("ColocarValor");
  }
}

void CicloBasico::inc(string direccionDeMemoria){
  MAR = direccionDeMemoria;
  funcionalidadMDR("ObtenerValor");
  int valor = MDR2 + 1;
  memoriaPrincipalValores[MAR] = valor;
}

void CicloBasico::dec(string direccionDeMemoria){
  MAR = direccionDeMemoria;
  funcionalidadMDR("ObtenerValor");
  int valor = MDR2 - 1;
  memoriaPrincipalValores[MAR] = valor;
}

void CicloBasico::str(string direccionDeMemoria){
  MAR = direccionDeMemoria;
  memoriaPrincipalValores[MAR] = varAcumulador;
}

void CicloBasico::shw(string direccionDeMemoria){
  cout << "-----------------------------------------" << endl;
  if(direccionDeMemoria == "ACC"){
    cout << "Valor del ACC: " << varAcumulador << endl;
  }else if(direccionDeMemoria == "ICR"){
    cout << "Valor del ICR: " << ICR[0]+ " " + ICR[1]+ " " + ICR[2]+ " " + ICR[3]+ " " + ICR[4] << endl;
  }else if(direccionDeMemoria == "MAR"){
    cout << "Valor del MAR: " << MAR << endl;
  }else if(direccionDeMemoria == "MDR"){
    size_t tamano = valorFinalMDR.size();
    if (tamano > 0) {
      cout << "Valor del MDR: " << valorFinalMDR[tamano - 1] << endl;
    }
  }else if (direccionDeMemoria == "UC"){
    cout << "Valor del UC: " << UC[0]+ " " + UC[1]+ " " + UC[2] + " "+ UC[3] + " "+ UC[4] << endl;
  }else{
    MAR = direccionDeMemoria;
    funcionalidadMDR("ObtenerValor");
    cout << "El valor en la direccion de memoria " + MAR + " es " + to_string(MDR2) << endl;
  }
  cout << "-----------------------------------------" << endl;
}

void CicloBasico::asignarMDR(string valor){
  valorFinalMDR.push_back(valor);
}

void CicloBasico::funcionalidadPause(){
  cout << "-----------------------------------------" << endl;
  for(auto it = memoriaPrincipalValores.begin(); it != memoriaPrincipalValores.end(); it++){
    cout << it->first << " : " << it->second << endl;
  }

  cout << "Valor del ACC: " << varAcumulador << endl;
  cout << "Valor del ICR: " << ICR[0] + " " + ICR[1]+ " " + ICR[2]+ " " + ICR[3]+ " " + ICR[4] << endl;
  cout << "Valor del MAR: " << MAR << endl;
  size_t tamano = valorFinalMDR.size();
  if (tamano > 0) {
    cout << "Valor del MDR: " << valorFinalMDR[tamano - 1] << endl;
  }
  cout << "Valor del UC: " << UC[0]+ " " + UC[1]+ " " + UC[2]+ " " + UC[3]+ " " + UC[4] << endl;
  cout << "-----------------------------------------" << endl;
}
