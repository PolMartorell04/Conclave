#ifndef JUGADOR_H
#define JUGADOR_H
#include "Carta.h"
#include "Seguidors.h"
#include <iostream>
#include <string>
using namespace std;

const int MAX_MA = 4;

class Jugador{

    public:
        Jugador();
        //Pre: --; Post: a_nom_j = " "

        Jugador(string nom);
        //Pre: --; Post: a_nom_j = nom

        void mostrar_ma(int format);
        //Pre: --; Post: es mostra la ma del jugador amb el format requerit (1 o 2)

        void afegir_carta_ma(const Carta& carta);
        //Pre: --; Post: s'afegeix carta a a_ma_c

        void afegir_carta(const Carta& carta, int pos);
        //Pre: --; Post: afegeix carta a_ma_c[pos]

        void mostrar_jug();
        //Pre: --; Post: es mostra el nom del jugador a_nom_j

        string r_nom();
        //Pre: --; Post: es retorna el nom del jugador a_nom_j

        void resum_seguidors();
        //Pre: --; Post: calcula els seguidors de cada magia i els mostra

        void mostrar_seg();
        //Pre: --; Post: mostra a_seg, la llista ordenada per màgies dels seguidors totals

        Carta retorn_carta(int pos);
        //Pre: --; Post: retorna una carta de a_ma_c[pos]

        void afegir_seguidor(Carta c);
        //Pre: --; Post: insereix c a a_seg

        void calcul_seg();
        //Pre: --; Post: crida a calcular_seguidors de cada magia

        Seguidors retorn_seg();
        //Pre: --; Post: es retorna el vector de seguidors a_seg

    private:

        Carta a_ma_c[4];
        int a_nMa=0;

        Seguidors a_seg;

        string a_nom_j;
};

#endif // JUGADOR_H