#include "Tauler.h"
#include <iomanip>
#include <iostream>
using namespace std;

Tauler::Tauler() {
    a_nf=4; a_nc=4; a_mp=NULL;
    reserva();
}

Tauler::Tauler(int nf, int nc){
    a_nf=nf; a_nc=nc;
    reserva();
}

Tauler::Tauler(const Tauler& t){
    copia(t);
}

Tauler::~Tauler(){
    allibera();
}

Tauler& Tauler::operator=(const Tauler& t){
    if(this!=&t){
        allibera();
        copia(t);
    }
    return *this;
}

void Tauler::afegirCarta(int i, int j, const Carta &c){
    a_mp[i][j]=c;
}

Carta Tauler::obtElem(int i, int j) const{
    return a_mp[i][j];
}

int Tauler::obtNF() const{
    return a_nf;
}

int Tauler::obtNC() const{
    return a_nc;
}

void Tauler::allibera(){
    for(int i=0;i<a_nf; i++)
        delete [] a_mp[i];
    delete [] a_mp;
}

void Tauler::reserva(){
    a_mp = new Carta*[a_nf];
    for(int i=0; i<a_nf; i++)
        a_mp[i]= new Carta[a_nc];
}

void Tauler::copia(const Tauler& t){
    a_mp = new Carta*[a_nf];
    for(int i=0; i<a_nf; i++){
        a_mp[i]= new Carta [a_nc];
        for (int j=0; j<a_nc; j++){
            a_mp[i][j]=t.a_mp[i][j];
        }
    }
}

void Tauler::mostrar_tauler(const PilaCartes& pila_esquerra, const PilaCartes& pila_dreta) const{
    cout << string(5, ' ');
    for (int i = 0; i < MIDA_TAULER; i++){
        cout << setfill(' ') << setw(6) << i;
    }
    cout << endl;

    for (int i = 0; i < MIDA_TAULER; i++){
        if (i == 1){
            pila_esquerra.cim().mostrar_revers();
        }
        else cout << "   ";

        cout << setfill(' ') << setw(3) << i << " ";
        for (int j = 0; j < MIDA_TAULER; j++){
            cout << " ";
            if(a_mp[i][j].es_lliure()) cout << "[   ]";
            else a_mp[i][j].mostrar_carta();
        }

        if (i == 1){
            cout << "  ";
            pila_dreta.cim().mostrar_revers();
        }

        cout << endl;
    }
}

bool Tauler::es_lliure(int primer, int segon){
    return a_mp[primer][segon].retorn_influ()==0;
}

void Tauler::treure_carta_t(int x, int y){
    Carta c = Carta();
    a_mp[x][y] = c;
}