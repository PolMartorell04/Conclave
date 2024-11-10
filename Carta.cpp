#include "Carta.h"
#include <iostream>
using namespace std;

Carta::Carta(){
    a_magia=' ';
    a_influencia=0;
    a_germandat=' ';
}

Carta::Carta(char magia, int influencia, char germandat){
    a_magia=magia;
    a_influencia=influencia;
    a_germandat=germandat;
}

void Carta::mostrar_carta(){
    cout << "[" << a_magia << a_influencia << a_germandat << "]";
}

void Carta::mostrar_revers(){
    cout << "[" << a_magia << "]";
}

bool Carta::carta_igual(Carta c){
    return (a_magia==c.a_magia and a_influencia==c.a_influencia and a_germandat==c.a_germandat);
}

bool Carta::carta_mes_gran(Carta c){
    return (a_magia>c.a_magia) or
    (a_magia==c.a_magia and a_influencia>c.a_influencia) or
    (a_magia==c.a_magia and a_influencia==c.a_influencia and a_germandat>c.a_germandat);
}

char Carta::retorn_magia(){
    return a_magia;
}

int Carta::retorn_influ(){
    return a_influencia;
}

char Carta::retorn_germandat(){
    return a_germandat;
}

bool Carta::es_lliure(){
    return a_influencia==0;
}