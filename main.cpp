#include <iostream>
#include <limits>
#include "Joc.h"
using namespace std;

const char EOS = 'F';
const char P_ESQ = 'e';
const char P_DRET = 'd';
const int MIN_JUG = 2;
const int MAX_JUG = 4;

char llegir_opcio(){
//Pre: --;
//Post: llegeix i retorna un char (opcio)
    char opcio;
    cout << endl << "ENTRA UNA OPCIO:" << endl;
    cin >> opcio;
    return opcio;
}

void menu(){
//Pre: --;
//Post: mostra el menú per pantalla
    cout << endl << "OPCIONS:" << endl;
    cout << "(I) FER JUGADA CEDINT INFLUENCIA" << endl;
    cout << "(J) FER JUGADA SENSE CEDIR INFLUENCIA" << endl;
    cout << "(P) MOSTRAR PILES" << endl;
    cout << "(F) ABANDONAR PARTIDA" << endl;
}

void entrada_jugadors(Joc& joc, int& jugadors){
//Pre: --;
//Post: emplena el vector a_jugadors de joc i els màxims amb les dades entrades per l'usuari
    string nom;
    cout << "ENTRA EL NUMERO DE JUGADORS (" << MIN_JUG
         << "-" << MAX_JUG << "):" << endl;
    cin >> jugadors;
    while(jugadors<2 or jugadors>4){
        cout << "NUMERO DE JUGADORS INCORRECTE" << endl;
        cout << "ENTRA EL NUMERO DE JUGADORS (2-4):" << endl;
        cin >> jugadors;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(int i=1; i<jugadors+1; i++){
        cout << "ENTRA EL NOM DEL JUGADOR " << i << ":" << endl;
        getline(cin,nom);
        Jugador jugador = Jugador(nom);
        joc.creacio_jug(jugador);
    }
}

void posicions_i_piles(int& pos_carta, char& pila, int& primer, int& segon, Joc& joc){
//Pre: --;
//Post: llegeix pos_carta, pila, primer i segon (sempre que siguin valors aptes)
        cout << "ENTRA LA POSICIO DE LA CARTA QUE VOLS COL.LOCAR:" << endl;
        cin >> pos_carta;
        while((cin.fail()) and (pos_carta<0) and (pos_carta>3)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "POSICIO NO VALIDA" << endl;
            cin >> pos_carta;
        }

        cout << "ENTRA LA POSICIO DEL TAULER ON VOLS COL.LOCAR LA CARTA:" << endl;
        cin >> primer >> segon;
        while((cin.fail()) and (primer<0) and (primer>3) and (segon<0) and (segon>3)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "POSICIO NO VALIDA" << endl;
            cin >> primer >> segon;
        }

        while(not(joc.es_lliure(primer,segon))){
            cout << "JUGADA NO PERMESA" << endl;
            cout << "TORNA A INDICAR LA JUGADA" << endl;
            primer=0, segon=0, pos_carta=0;
            posicions_i_piles(pos_carta,pila,primer,segon,joc);
        }

        cout << "DE QUINA PILA VOLS ROBAR LA CARTA? (" << P_ESQ
            << "/" << P_DRET << ")" << endl;
        cin >> pila;
        while((cin.fail()) and (pila!='e') and (pila!='d')){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "AQUESTA PILA NO EXISTEIX" << endl;
            cin >> pila;
        }
}

char no_valid(){
//Pre: --;
//Post: llegeix i retorna un char (interes)
    cout << "MOVIMENT NO VALID" << endl;
    char interes;
    cout << "ENCARA T'INTERESSA CEDIR INFLUENCIA? (s/n)" << endl;
    cin >> interes;
    return interes;
}

void jugada_sense_inf(Joc& joc, int final_jug){
//Pre: final_jug>0
//Post: realitza la jugada sense influència dins de joc en el jugador a_jugador[final_jug]
    char pila;
    int pos_carta;
    int primer, segon;
    posicions_i_piles(pos_carta,pila,primer,segon,joc);
    joc.fer_jugada(pos_carta,primer,segon,final_jug);
    joc.robar_carta(pila,pos_carta,final_jug);
}

void fer_jugada_amb_inf(Joc& joc, int final_jug){
//Pre: final_jug>0
//Post: realitza la jugada amb influència dins de joc en el jugador a_jugador[final_jug]
    char magia, pila;
    int n_jug, pos_carta;
    int primer, segon;

    cout << "ENTRA LA MAGIA QUE VOLS CEDIR:" << endl;
    cin >> magia;

    cout << "ENTRA EL JUGADOR A QUI LA VOLS CEDIR:" << endl;
    cin >> n_jug;
    while(n_jug<0 or n_jug>3){
        cin >> n_jug;
    }

    if(magia!='b' or magia!='o' or magia!='p' or magia!='r' or magia!='t' or magia!='v'){
        char x = no_valid();
        if(x=='s') fer_jugada_amb_inf(joc,final_jug);
        else if (x=='n') jugada_sense_inf(joc,final_jug);
    }

    posicions_i_piles(pos_carta,pila,primer,segon,joc);
    joc.cedir_influencia(magia,n_jug,final_jug);
    joc.fer_jugada(pos_carta,primer,segon,final_jug);
    joc.robar_carta(pila,pos_carta,final_jug);
}

int main(){
    unsigned llavor;
    int jugadors;
    cout << "ENTRA LA LLAVOR:" << endl;
    cin >> llavor;

    bool opcio_defin = false;

    Joc joc(llavor);
    entrada_jugadors(joc,jugadors);
    joc.preparar();

    int final_jug = 0;
    joc.mostrar_joc(final_jug, jugadors);

    menu();
    char opcio=llegir_opcio();

    if(opcio=='P'){
        joc.mostrar_piles_joc();
        joc.mostrar_joc(final_jug, jugadors);
        menu();
        opcio=llegir_opcio();
    }

    while (final_jug < jugadors and opcio != EOS){
        if(opcio=='I') fer_jugada_amb_inf(joc, final_jug);
        else if (opcio=='J') jugada_sense_inf(joc, final_jug);
        else{
            cout << "OPCIO NO DEFINIDA" << endl;
            joc.mostrar_joc(final_jug, jugadors);
            opcio_defin = true;
        }
        if(final_jug < jugadors) final_jug++;
        else final_jug=0;

        if(!opcio_defin) joc.mostrar_joc(final_jug, jugadors);

        menu();
        opcio = llegir_opcio();
        opcio_defin = false;
    }

    if (opcio == EOS) cout << "PARTIDA ABANDONADA" << endl;
}