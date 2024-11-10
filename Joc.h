#ifndef JOC_H
#define JOC_H
#include "Jugador.h"
#include "Tauler.h"
#include "Baralla.h"
#include "PilaCartes.h"
#include <iostream>
#include <string>
using namespace std;

class Joc{

    public:

        Joc();
        //Pre: --; Post: a_llavor = 0

        Joc(int llavor);
        //Pre: --; Post: a_llavor = llavor

        void preparar();
        //Pre: --; Post: es preparen les piles, la baralla i el tauler de joc

        void mostrar_piles_joc();
        //Pre: --; Post: es mostren les piles del joc

        void retirar_sobrants(Baralla& baralla);
        //Pre: --; Post: segons la fórmula proporcionada, es retiren x cartes de baralla

        void creacio_jug(const Jugador& jugador);
        //Pre: --; Post: s'insereix un jugador dins el vector (atribut) a_jugadors

        void repartir_inicials(Baralla& baralla);
        //Pre: --; Post: es reparteixen quatre cartes de la baralla a cada jugador per a formar la mà

        void repartir_tauler(Baralla& baralla, Tauler& tauler);
        //Pre: --; Post: a partir de la baralla es reparteix el tauler deixant quatre espais buits al mig

        Tauler retorn_tauler();
        //Pre: --; Post: es retorna l'atribut a_tauler

        PilaCartes retorn_pila_esquerra();
        //Pre: --; Post: es retorna l'atribut a_pila_esq

        PilaCartes retorn_pila_dreta();
        //Pre: --; Post: es retorna l'atribut a_pila_dreta

        void mostrar_joc(int final_jug, int jugadors);
        //Pre: jugadors>0 Post: es mostra el joc del jugador[final_jug] i les cartes/seguidors dels jugadors restants

        void fer_jugada(int pos_carta, int primer, int segon, int final_jug);
        //Pre: --; Post: s'afegeix a la posicio del tauler[primer][segon] del jugador[final_jug] la carta[pos_carta], es calculen els seguidors obtinguts i si cal es fa la crisi magica

        void cedir_influencia(char magia, int n_jug, int final_jug);
        //Pre: --; Post: si es compleixen les condicions, es cedeixen totes les cartes amb la magia entrada del jugador[final_jug] al jugador[n_jug]

        void robar_carta(char pila, int pos_carta, int final_jug);
        //Pre: --; Post: es roba una carta de la pila requerida per l'usuari i es reposa el conclave si és necessari

        void valorar_final();
        //Pre: --; Post: es valora si s'ha acabat la partida o es segueix

        void puntuacio_resultat();
        //Pre: --; Post: calcula el resultat i les puntuacions finals del joc

        bool es_lliure(int primer, int segon);
        //Pre: --; Post: retorna true si l'element de pos[primer][segon] es lliure

        int comptador(char magia, int a);
        //Pre: --; Post: retorna el comptador pertanyent de la magia entrada

    private:

        unsigned a_llavor;

        Jugador a_jugadors[4];
        int j=0;

        static const int JUG_U = 1;
        static const int M = 6;
        static const int J = 4;

        Tauler a_tauler;
        PilaCartes a_pila_esq;
        PilaCartes a_pila_dreta;

        void obtenir_seguidors(int i, int j,Carta c, int final_jug);
        //Pre: Post: es calcula si s'obtenen seguidors a partir d'una carta entrada en una posicio del tauler [i][j] del jugador[final_jug]

        void reposar_conclave(char pila);
        //Pre: Post: si cal es reposa el conclave robant cartes de la pila

        void crisi_magica(Carta c, int final_jug, int primer, int segon);
        //Pre: Post: si es compleix la condicio, s'aplica la crisi magica al joc comparant amb els valors de c

        int retorn_espais();
        //Pre: Post: es retorna el nombre d'espais buits que té el tauler

        void auxiliar_repos(char pila, int i, int j);
        //Pre: Post: dictamina de quina pila hem de robar carta per afegir-la a la pos[i][j] del tauler per a reposar el conclave
};

#endif // JOC_H