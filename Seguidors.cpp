#include "Seguidors.h"
#include <iostream>
#include <iomanip>
using namespace std;

Seguidors::Seguidors(){
    a_inici = NULL;
}

Seguidors::Seguidors(const Seguidors &o){
    a_inici = NULL;
    copia(o);
}

Seguidors::~Seguidors(){
    allibera();
}

Seguidors& Seguidors::operator=(const Seguidors &o) {
    if (this != &o) {
        allibera();
        copia(o);
    }
    return *this;
}

bool Seguidors::buida() const {
    return a_inici == NULL;
}

bool Seguidors::existeix(Carta c) const {
    Node *p = a_inici;
    bool fiCerca = false;
    bool trobat = false;
    while ((p!=NULL) && (!fiCerca)){
        if (p->dada.carta_mes_gran(c)){
            fiCerca = true;
            trobat = p->dada.carta_igual(c);
        }
        else
            p = p->seg;
    }
    return trobat;
}

void Seguidors::inserir(Carta c){
    Node *ant, *p, *nou;
    bool fiCerca = false;
    bool trobat = false;
    ant = NULL;
    p = a_inici;
    while((p!=NULL) && (!fiCerca)){
        if (p->dada.carta_mes_gran(c)){
            fiCerca = true;
            trobat = p->dada.carta_igual(c);
        }
        else{
            ant = p;
            p = p->seg;
        }
    }
    if (!trobat) {
        nou = new Node;
        nou->dada = c;
        nou->seg = p;
        if (ant == NULL)
            a_inici = nou;
        else
            ant->seg = nou;
    }
}

Carta Seguidors::eliminar(Carta c) {
    Node *ant, *p;
    Carta carta;
    bool fiCerca = false;
    bool trobat = false;
    ant = NULL;
    p = a_inici;
    while((p!=NULL) && (!fiCerca)) {
        if (p->dada.carta_mes_gran(c)){
            fiCerca = true;
            trobat = p->dada.carta_igual(c);
        }
        else{
            ant = p;
            p = p->seg;
        }
    }
    if (trobat) {
        if(ant!= NULL)
            ant->seg = p->seg;
        else a_inici = p->seg;
        c=p->dada;
        delete p;
    }
    return carta;
}

void Seguidors::mostrar_seguidors()const{
    Node *p = a_inici;
    if(p==NULL) cout << "NO HI HA CAP CARTA";
    while (p!= NULL){
        p->dada.mostrar_carta();
        cout << " ";
        p = p->seg;
    }
    cout << endl;
}

void Seguidors::mostrar_resum(){
    int compt = 0;
    char MAGIA_RES[]={'b','o','p','r','t','v'};
    for (int i=0; i<6; i++){
        cout << "[" << setfill(' ') << setw(2);
        if (i==0) compt = nB;
        else if (i==1) compt = nO;
        else if (i==2) compt = nP;
        else if (i==3) compt = nR;
        else if (i==4) compt = nT;
        else if (i==5) compt = nV;
        if(compt>0) cout << compt;
        else if (compt==0) cout << ' ';
        cout << MAGIA_RES[i] << "]";
        cout << " ";
    }
}

void Seguidors::calcular_seguidors(){
    Node *p = a_inici;
    while (p!= NULL){
        char x = p->dada.retorn_magia();
        if(x=='b') nB+=p->dada.retorn_influ();
        else if(x=='o') nO+=p->dada.retorn_influ();
        else if(x=='p') nP+=p->dada.retorn_influ();
        else if(x=='r') nR+=p->dada.retorn_influ();
        else if(x=='t') nT+=p->dada.retorn_influ();
        else if(x=='v') nV+=p->dada.retorn_influ();
        p = p->seg;
    }
}

void Seguidors::allibera() {
    while (!buida()) {
        Node* aux = a_inici;
        a_inici = a_inici->seg;
        delete aux;
    }
}

void Seguidors::copia(const Seguidors &o) {
    if(!o.buida()) {
        Node *ant, *p, *q;
        p = o.a_inici;
        q = new Node; a_inici = ant = q;
        q->dada = p->dada; q->seg = NULL;
        p = p->seg;
        while (p != NULL) {
            q = new Node;
            q->dada = p->dada; q->seg = NULL;
            ant->seg = q;
            ant = q;
            p = p->seg;
        }
    }
}

int Seguidors::retorn_nB(){
    return nB;
}

int Seguidors::retorn_nO(){
    return nO;
}

int Seguidors::retorn_nP(){
    return nP;
}

int Seguidors::retorn_nR(){
    return nR;
}

int Seguidors::retorn_nT(){
    return nT;
}

int Seguidors::retorn_nV(){
    return nV;
}