#include "Jugador.h"
#include <iostream>
using namespace std;

Jugador::Jugador(){
    a_nom_j=" ";
}

Jugador::Jugador(string nom){
    a_nom_j=nom;
}

void Jugador::mostrar_ma(int format){
    for(int i=0; i<4; i++){
        if(format==1){
            cout << i << ":";
            a_ma_c[i].mostrar_carta();
        }
        else if (format ==2) a_ma_c[i].mostrar_revers();
        cout << " ";
    }
}

void Jugador::afegir_carta_ma(const Carta& carta){
    a_ma_c[a_nMa]=carta;
    a_nMa++;
}

void Jugador::afegir_carta(const Carta& carta, int pos){
    a_ma_c[pos]=carta;
}

void Jugador::mostrar_jug(){
    cout << a_nom_j;
}

string Jugador::r_nom(){
    return a_nom_j;
}

void Jugador::resum_seguidors(){
    a_seg.calcular_seguidors();
    a_seg.mostrar_resum();
}

void Jugador::calcul_seg(){
    a_seg.calcular_seguidors();
}

void Jugador::mostrar_seg(){
    a_seg.mostrar_seguidors();
}

Carta Jugador::retorn_carta(int pos){
    return a_ma_c[pos];
}

void Jugador::afegir_seguidor(Carta c){
    a_seg.inserir(c);
}

Seguidors Jugador::retorn_seg(){
    return a_seg;
}