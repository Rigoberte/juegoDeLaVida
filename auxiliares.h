//


#ifndef REUNIONESREMOTAS_AUXILIARES_H
#define REUNIONESREMOTAS_AUXILIARES_H

#include "definiciones.h"

using namespace std;
// definir aqui las funciones
pair<int,int> mp(int a, int b);
vector<posicion> ordenar(vector<posicion> &v);

//*************** Ejercicio 01 ****************
int filas(vector<vector<bool>> const &t);
int columnas(vector<vector<bool>> const &t);
bool esRectangulo(vector<vector<bool>> const &r);
bool esToroide(vector<vector<bool>> const &t);

//*************** Ejercicio 02 ****************
bool toroideSinVida(toroide const &t);

//*************** Ejercicio 04 ****************
float superficieTotal(toroide const &t);

//*************** Ejercicio 05 ****************
bool enRango(int i, int s);
bool enRangoToroide(int f, int c,toroide t);
bool estaViva(int f, int c, toroide const &t);
int mod(int x, int y);
int filaToroide(int f, toroide const &t);
int columnaToroide(int c, toroide const &t);
bool vivaToroide(int f, int c, toroide const &t);
bool vecinaViva(toroide const &t, int f, int c, int i, int j);
float vecinosVivos(toroide const &t, int f, int c);

//*************** Ejercicio 06 ****************
bool debeVivir(toroide const &t, int &f, int &c);
bool estaMuerta ( int &f, int &c, toroide const &t);

//*************** Ejercicio 07 ****************
toroide evolucionarToroideUnTick(toroide &t0);

//*************** Ejercicio 10 ****************
int cantidadTicksHastaMorir(toroide const &t);
bool evolucionarHastaIgualdad_o_Morir (toroide const &t, toroide const &u);

//*************** Ejercicio 13 ****************
bool traslacion(toroide const &t1, toroide const &t2, int &i, int &j);
bool esTrasladada(toroide const &t1, toroide const &t2);

//*************** Ejercicio 14 ****************
toroide trasladar(toroide const &t, int f, int c);
void calcularExtremos(toroide &t, int &maxFila, int &minFila, int &maxColumna, int &minColumna);
int area(int maxFila, int minFila, int maxColumna, int minColumna);
int calcularArea(toroide &t);

#endif //REUNIONESREMOTAS_AUXILIARES_H
