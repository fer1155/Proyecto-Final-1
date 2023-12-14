#ifndef CICLOBASICO_H
#define CICLOBASICO_H

#include <string>
#include <map>
#include <vector>
using namespace std;

class CicloBasico{
  private:
    string nombre;
    map<string, int> memoriaPrincipalValores;
    map<int, vector<string>> memoriaPrincipalInstrucciones;
    int varAcumulador;
    int PC;
    string MAR;
    vector<string> valorFinalMDR;
    vector<string> MDR1;
    int MDR2;
    vector<string> ICR;
    vector<string> UC;
  public:
    //Constructor
    CicloBasico(string);

    virtual void setValores(string, string);
    virtual void setInstrucciones(int, string, string, string, string, string);
    virtual void ejecucionDeCicloBasico();
    virtual void funcionalidadPC();
    virtual void funcionalidadMAR();
    virtual void funcionalidadMDR(string);
    virtual void asignarMDR(string);
    virtual void funcionalidadICR();
    virtual void funcionalidadUC();
    virtual void funcionalidadPause();
    virtual int acumulador(int);
    virtual void funcionalidadALU(int);
    virtual void ldr(string);
    virtual void add(string, string, string);
    virtual void inc(string);
    virtual void dec(string);
    virtual void str(string);
    virtual void shw(string);
};

#else
class CicloBasico; 
#endif