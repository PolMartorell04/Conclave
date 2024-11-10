#include "Baralla.h"
#include <iostream>
using namespace std;

Baralla::Baralla(){
    a_n=0;
    a_max=0;
    reserva();
}

Baralla::Baralla(int llavor){
    char MAGIA[]={'b','o','p','r','t','v'};
    char GERMANDAT[]={'c','g','s'};
    a_ll=llavor;
    a_n=0;
    a_max=5;
    reserva();
    for (int i=0; i<6; i++){
        for (int s=0; s<3; s++){
            for (int j=1; j<6; j++) {
                Carta carta = Carta(MAGIA[i],j,GERMANDAT[s]);
                afegir_carta(carta);
            }
        }
    }
}

int Baralla::aleatori(int rang){
    int valor;
    a_ll = (a_ll*1103515245) + 12345;
    valor=((a_ll/32)%32768)%rang;
    return valor;
}

 Baralla::Baralla(const Baralla& b){
    copia(b);
}

Baralla::~Baralla(){
    allibera();
}

Baralla& Baralla::operator=(const Baralla& b){
    if (this != &b) {
        allibera();
        copia(b);
    }
    return *this;
}

void Baralla::afegir_carta(const Carta& c){
    if(a_n == a_max) expandeix();
    a_t[a_n] = c;
    a_n++;
}

Carta Baralla::robar_carta(){
    if(a_n<0){
        delete []a_t;
    }
    else{
        a_n--;
    }
    return
        a_t[a_n];
}

void Baralla::mostrar(){
    if (a_n==0) cout << "NO HI HA CAP CARTA";
    else{
        for(int i=0; i<a_n; i++){
            a_t[i].mostrar_carta();
        }
    }
    cout << endl;
}

void Baralla::intercanvi(Carta& a1, Carta& a2){
    Carta auxiliar = a1;
    a1=a2;
    a2=auxiliar;
}

void Baralla::barrejar(){
    for(int i=a_n-1; i>0; i--){
        int pos = aleatori(i+1);
        intercanvi(a_t[pos],a_t[i]);
    }
}

void Baralla::emplenar_pila_esquerra(PilaCartes& pila_esquerra){
    int aux = a_n;
    for(int i=aux-1; i>=aux/2; i--){
        Carta carta = robar_carta();
        pila_esquerra.empila(carta);
    }
}

void Baralla::emplenar_pila_dreta(PilaCartes& pila_dreta){
    int aux = a_n;
    for(int i=aux-1; i>=0; i--){
        Carta carta = robar_carta();
        pila_dreta.empila(carta);
    }
}

void Baralla::allibera(){
    delete [] a_t;
}

void Baralla::copia(const Baralla& b){
    a_n = b.a_n;
    a_max = b.a_max;
    reserva();
    for(int i=0; i<a_n; i++)
        a_t[i] = b.a_t[i];
}

void Baralla::reserva(){
    a_t = new Carta[a_max];
}

void Baralla::expandeix(){
    Carta *aux = a_t; // taula a substituir
    a_max = 2*a_max; //s'amplia la capacitat
    reserva(); // es crea la nova taula
    for(int i=0; i<a_n; i++) // es copien les caselles
        a_t[i] = aux[i];
    delete[] aux; //s'allibera la vella
}
