#ifndef BARALLA_H
#define BARALLA_H
#include <iostream>
#include <string>
#include "Carta.h"
#include "PilaCartes.h"
using namespace std;

class Baralla{ //taula dinàmica de Carta

    public:

        Baralla();
        //Pre: --; Post: taula buida amb memòria reservada per a_max=0 Carta

        Baralla(int llavor);
        //Pre: --; Post: taula emplenada amb 90 cartes i una llavor

        Baralla(const Baralla &b);
        //Pre: --; Post: aquesta taula és còpia de la taula b

        ~Baralla();
        //Pre: --; Post: memòria alliberada

        void mostrar();
        //Pre: --; Post: es mpstra la taula

        void barrejar();
        //Pre: --; Post: es barrejen els elements de la taula actual

        Baralla &operator=(const Baralla &b);
        //Pre: --; Post: aquesta taula és còpia de la taula b

        void afegir_carta(const Carta &c);
        //Pre: --; Post: c afegit a la taula si hi ha espai

        Carta robar_carta();
        //Pre: --; Post: retorna i borra l'últim element de la taula dinàmica

        void intercanvi(Carta& a1, Carta& a2);
        //Pre: --; Post: a1 i a2 han quedat intercanviats.

        void emplenar_pila_esquerra(PilaCartes& pila_esquerra);
        //Pre: --; Post: pila_esquerra queda emplenada de elements Carta

        void emplenar_pila_dreta(PilaCartes& pila_dreta);
        //Pre: --; Post: pila_dreta queda emplenada de elements Carta

    private:

        unsigned a_ll;
        int a_n; //caselles ocupades
        int a_max; //posicions reservades (capacitat)
        Carta *a_t;

        void allibera();
        //Pre: --; Post: memòria alliberada

        void copia(const Baralla &b);
        //Pre: memòria alliberada; Post: aquesta taula és còpia de la taula b

        void reserva();
        //Pre: --; Post: memòria reservada per a_max Carta

        void expandeix();
        //Pre: --; Post: la memòria reservada es dobla

        int aleatori (int rang);
        //Pre: --; Post: retorna un nombre aleatori generat a partir del rang proporcionat.
};

#endif // BARALLA_H