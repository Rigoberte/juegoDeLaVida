#include "definiciones.h"
#include "auxiliares.h"
#include "ejercicios.h"

using namespace std;
// aqui se pueden ubicar todas las funciones auxiliares de soporte para la resolucion de los ejercicios


pair<int,int> mp(int a, int b) {
    return make_pair(a, b);
}
//No pueden usar esta función para resolver el TPI.
//Tampoco pueden usar iteradores, como usa esta función.
vector<posicion> ordenar(vector<posicion> &v) {
    sort(v.begin(), v.end());
    return v;
}

//*************** Ejercicio 01 ****************
int filas(vector<vector<bool>> const &t) {
    int f = t.size();
    return f;
}

int columnas(vector<vector<bool>> const &t){
    int c = 0;
    if (filas(t) > 0){
        c = t[0].size();
    }
    return c;
}

bool esRectangulo(vector<vector<bool>> const &r){
    bool res = true;
    if (filas(r) > 0 && columnas(r) > 0){
        for (int f=0; f < r.size(); f++){
            res = res && (r[f].size() == r[0].size());
        }
    } else {
        res = false;
    }
    return res;
}

bool esToroide(vector<vector<bool>> const &t){
    bool res = false;
    if (esRectangulo(t) && filas(t) >= 3 && columnas(t) >= 3){
        res = true;
    }
    return res;
}

//*************** Ejercicio 02 ****************
bool toroideSinVida(toroide const &t){
    bool resp = true;
    for (int f=0; f < filas( t ); f++){
        for (int c=0; c < columnas(t); c++)
        {
            if (t[f][c] == true){
                resp = resp && false;
            }
        }
    }
    return resp;
}

//*************** Ejercicio 04 ****************
float superficieTotal(toroide const &t){
    float sup = columnas(t) * filas(t);
    return sup;
}

//*************** Ejercicio 05 ****************
bool enRango(int i, int s){
    bool res = false;
    if (i >= 0 && i < s){
        res = true;
    }
    return res;
}

bool enRangoToroide(int f, int c,toroide t){
    bool res = false;
    if ( enRango(f, filas(t)) && enRango(c, columnas(t)) ){
        res = true;
    }
    return res;
}

bool estaViva(int f, int c, toroide const &t){
    bool res = enRangoToroide(f,c,t) && t[f][c] == true;
    return res;
}

int mod(int x, int y){
    int res = x % y;
    if (res < 0){
        res = res + y;
    }
    return res;
}

int filaToroide(int f, toroide const &t){
    int res = mod(f, filas(t));
    return res;
}

int columnaToroide(int c, toroide const &t){
    int res = mod(c, columnas(t));
    return res;
}

bool vivaToroide(int f, int c, toroide const &t){
    bool res = estaViva(filaToroide(f,t), columnaToroide(c,t),t);
    return res;
}

bool vecinaViva(toroide const &t, int f, int c, int i, int j){
    return vivaToroide(f+i, c+j, t);
}

float vecinosVivos(toroide const &t, int f, int c){
    float res = 0;
    for (int i=-1; i <= 1; i++){
        for (int j=-1; j <= 1; j++){
            if ((i != 0 || j != 0) && vecinaViva(t,f,c,i,j)){
                res++;
            }
        }
    }
    return res;
}

//*************** Ejercicio 06 ****************
bool estaMuerta ( int &f, int &c, toroide const &t){
    bool resp = enRangoToroide(f, c, t) && (!t[f][c]);
    return resp;
}

bool debeVivir(toroide const &t, int &f, int &c){
    bool resp = false;
    if ((estaViva(f, c, t) && 2 <= vecinosVivos(t, f, c) && 3 >= vecinosVivos(t, f, c)) || ( (estaMuerta(f, c, t) && vecinosVivos(t, f, c) == 3) ) ){
        resp = true;
    }
    return resp;
}

//*************** Ejercicio 07 ****************
toroide evolucionarToroideUnTick(toroide &t0){
    toroide t = t0;
    for (int f=0; f < filas(t0); f++){
        for (int c=0; c < columnas(t0); c++){
            if (debeVivir(t0,f,c) == true){
                t[f][c] = true;
            } else {
                t[f][c] = false;
            }
        }
    };
    return t;
}

//*************** Ejercicio 10 ****************
int cantidadTicksHastaMorir(toroide const &t){
    int i = 0;
    toroide t_ev = t;
    while (!toroideSinVida(t_ev)){
        i++;
        t_ev = evolucionarToroideUnTick(t_ev);
    }
    return i;
}

bool evolucionarHastaIgualdad_o_Morir (toroide const &t, toroide const &u){
    bool resp = false;
    vector <toroide> s = {t};
    int p = 0;
    int limite = 0;

    if (esPeriodico(t, p)){
        limite = p;
    } else {
        limite = cantidadTicksHastaMorir(t) + 1; //en el caso de comparar contra un toroide muerto necesitamos que incluya al tick en el que muere
    }

    int i = 0;
    while (i < limite && !toroideSinVida(s[i]) && s[i] != u){
        s.push_back( evolucionarToroideUnTick(s[i]));
        i++;
    }
    if (s[i] == u){
        resp = true;
    }

    return resp;
}

//*************** Ejercicio 13 ****************
bool traslacion(toroide const &t1, toroide const &t2, int &i, int &j){
    bool res = true;
    for (int f=0; f<filas(t1); f++){
        for (int c=0; c<columnas(t1); c++){
            res = res && (estaViva(f,c,t1) == vivaToroide(f+i,c+j,t2)); //retorna True cuando las dos partes son True = True o False = False
        }
    }
    return res;
}

bool esTrasladada(toroide const &t1, toroide const &t2){
    bool res = false;
    for (int i=0; i<filas(t1); i++){
        for (int j=0; j<columnas(t1); j++){
            res = res || (traslacion(t1,t2,i,j));
        }
    }
    return res;
}

//*************** Ejercicio 14 ****************
toroide trasladar(toroide const &t, int f, int c){
    toroide t_ev = t;
    for (int i=0; i<filas(t); i++){
        for (int j=0; j<columnas(t); j++){
            t_ev[filaToroide(f+i,t)][columnaToroide(c+j,t)] = t[i][j];
        }
    }
    return t_ev;
}


void calcularExtremos(toroide &t, int &maxFila, int &minFila, int &maxColumna, int &minColumna){
    for (int i=0; i<filas(t); i++){
        for (int j=0; j<columnas(t); j++){
            if (t[i][j] == true){
                if (j < minColumna){
                    minColumna = j;
                }
                if (j > maxColumna){
                    maxColumna = j;
                }
                if (i < minFila){
                    minFila = i;
                }
                if (i > maxFila){
                    maxFila = i;
                }
            }
        }
    }
    return;
}

int area(int maxFila, int minFila, int maxColumna, int minColumna){
    int altura = (maxFila - minFila) + 1;
    int base = (maxColumna - minColumna) + 1;
    return (altura * base);
}


int calcularArea(toroide &t){
    //estamos asumiendo que tiene alguna celda viva asi que esto no deberia fallar
    int maxFila = 0;
    int minFila = filas(t) - 1;
    int maxColumna = 0;
    int minColumna = columnas(t) - 1;
    calcularExtremos(t, maxFila, minFila, maxColumna, minColumna);
    int res = area(maxFila, minFila, maxColumna, minColumna);
    return res;
}


