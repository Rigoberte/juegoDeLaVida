#include <algorithm>
#include "ejercicios.h"
#include "auxiliares.h"
#include "definiciones.h"

// EJERCICIO 1
bool toroideValido(vector<vector<bool>> const &t) {
    bool resp = esToroide(t);
    return resp;
}

// EJERCICIO 2
bool toroideMuerto(toroide const &t){
    bool resp = toroideSinVida(t);
    return resp;
}

// EJERCICIO 3
vector<posicion> posicionesVivas(toroide const &t) {
    vector<posicion> vivas = {};
    for (int f=0; f < filas(t); f++){
        for (int c=0; c < columnas(t); c++){
            if (t[f][c] == true){
                vivas.push_back({f,c});
            }
        }
    }
    return vivas;
}

// EJERCICIO 4
float densidadPoblacion(toroide const &t) {
    int cantidadVivas = posicionesVivas(t).size();
    float resp = (float) cantidadVivas / superficieTotal(t);
    return resp;
}

// EJERCICIO 5
int cantidadVecinosVivos(toroide const &t, int f, int c) {
    int resp = (int) vecinosVivos(t,f,c);
    return resp;
}

// EJERCICIO 6
bool evolucionDePosicion(toroide const &t, posicion x) {
    bool resp = debeVivir(t, x.first, x.second);
    return resp;
}

// EJERCICIO 7
void evolucionToroide(toroide &t){
    t = evolucionarToroideUnTick(t);
    return;
}

// EJERCICIO 8
toroide evolucionMultiple(toroide const &t, int K) {
    vector <toroide> s = {t};
    for (int i= 0; i<K; i++){
        s.push_back( evolucionarToroideUnTick(s[i]) );
    }
    toroide out = s[K];
    return out;
}

// EJERCICIO 9
bool esPeriodico(toroide const &t, int &p) {
    bool resp = true;
    int p0 = p;
    toroide t_ev = t;
    t_ev = evolucionarToroideUnTick(t_ev);
    p = 1;

    while (toroideMuerto(t_ev) == false && t_ev != t){
        t_ev = evolucionarToroideUnTick(t_ev);
        p++;
    }
    if (toroideMuerto(t_ev)){
        resp = false;
        p = p0;
    }
    return resp;
}

// EJERCICIO 10
bool primosLejanos(toroide const &t, toroide const &u) { //NO PASA TODOS LOS TESTS
    bool primos = false;
    if ( evolucionarHastaIgualdad_o_Morir(t, u) || evolucionarHastaIgualdad_o_Morir(u, t) ){
        primos = true;
    }
    return primos;
}

// EJERCICIO 11
int seleccionNatural(vector <toroide> ts){
    int resp = -1;
    int maxTicksHastaMorir = 0;
    for (int i=0; i<ts.size(); i++){
        if (cantidadTicksHastaMorir(ts[i]) > maxTicksHastaMorir){
            maxTicksHastaMorir = cantidadTicksHastaMorir(ts[i]);
            resp = i;
        }
    }
    return resp;
}

// EJERCICIO 12
toroide fusionar(toroide const &t, toroide const &u) {
    toroide res = t;
    for (int f=0; f<filas(t); f++){
        for (int c=0; c<columnas(t); c++){
            if (estaViva(f,c,t) == true && estaViva(f,c,u) == true){
                res[f][c] = true;
            } else {
                res[f][c] = false;
            }
        }
    }
    return res;
}

// EJERCICIO 13
bool vistaTrasladada(toroide const &t, toroide const &u){
    bool resp = esTrasladada(t,u);
    return resp;
}

// EJERCICIO 14
int menorSuperficieViva(toroide const &t){
    toroide t_trasladado = t;
    int areaMin = calcularArea(t_trasladado);
    int area_t_trasl = 0;

    for (int i=0; i<filas(t); i++){
        for (int j=0; j<columnas(t); j++){
            t_trasladado = trasladar(t,i,j);
            area_t_trasl = calcularArea(t_trasladado);
            if (area_t_trasl < areaMin){
                areaMin = area_t_trasl;
            }
        }
    }
    return areaMin;
}


bool pertenece(vector<int> s, int x){
    bool res = false;
    int i = 0;
    while (!res && i < s.size())
    {
        if (s[i] == x)
        {
            res = true;
        }
        i++;
    }
    return res;
}

int cantidadDeDistEntreAyB(vector<int> s, int a, int b){
    vector <int> res = {};
    for (int i = a; i <= b; i++) //O(n)
    {
        if( ! pertenece(res, s[i]))
        {
            res.push_back(s[i]);
        }
    }
    return res.size();
}

int ejercicio3(vector<int> &s)
{
    int index = -1;
    for (int i = 0; i < s.size()-1; i++) // O(n)
    {
        if (cantidadDeDistEntreAyB(s, 0, i) == cantidadDeDistEntreAyB(s, i + 1, s.size()-1))
        {
            index = i;
        }
    }
    return index;
}




vector<int> sumarConsecutuvos(vector<int> s)
{
    vector<int> s0;
    for ( int i = 0; i < s.size() - 1; i++)
    {
        if(i == 0)
            {
            s0[i] = s[i];
            }
        else
            {
            s0[i] = s[i] + s[i-1];
            }
    }
    return s0;
}
/*
vector<int> sumarConsecutuvos(vector<int> s)
{
    vector<int> s0 = s;
    for ( int i = 1; i < s.size() - 1; i++)
    {
        s[i] = s0[i] + s0[i-1];

    }
    return s;
}
*/

bool buscarEnZooms(vector<vector<int>>& M, int elem, int& fi, int& co)
{
    bool res = false;
    fi= 0; co=0;
    while (co < M.size() && !res)
    {
        if (fi >= M.size())
            {
            fi = 0;
            co += 1;
            }
        else if (M[fi][co] == elem)
            {
            res = true;
            }
        else
            {
            fi += 1;
            }
    }
    return res;
}