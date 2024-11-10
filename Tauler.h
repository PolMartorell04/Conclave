#ifndef TAULER_H
#define TAULER_H
#include "Carta.h"
#include "PilaCartes.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Tauler{ //matriu dinàmica de cartes

    public:
        Tauler();
        //Pre: --; Post: matriu buida

        Tauler(int nf, int nc);
        //Pre: nf>0 i nc>0; Post: objecte vàlid amb memòria reservada

        Tauler(const Tauler &t);
        //Pre: --; Post: informació de t copiada a lactual

        ~Tauler();
        //Pre: --; Post: allibera la memòria reservada per lobjecte

        Tauler &operator=(const Tauler &t);
        // Pre: --; Post: sha assignat sense aliasing la informació de t a lobjecte actual

        void afegirCarta(int i, int j, const Carta &c);
        //Pre: i>=0, j>=0; Post: s'afegeix a la matriu l'element proporcionat a la posició dels valors entrats per paràmetre

        Carta obtElem(int i, int j) const;
        //Pre: i>=0, j>=0; Post: retorna l'element amb posició dels valors entrats per paràmetre

        int obtNF()const;
        //Pre: --; Post: retorna el nombre de files de la matriu dinàmica

        int obtNC()const;
        //Pre: --; Post: retorna el nombre de columnes de la matriu dinàmica

        void mostrar_tauler(const PilaCartes& pila_esquerra, const PilaCartes& pila_dreta) const;
        //Pre: pila_esquerra i pila_dreta no buides; Post: es mostra la matriu dinàmica

        void treure_carta_t(int x, int y);
        //Pre: x>=0, y>=0; Post: s'elimina l'element amb posició dels valors entrats per paràmetre

        void repos_conclave_t();
        //Pre: --; Post: es reposa el conclave si compleix els requisits.

        void seguidor_crisi_magica();
        //Pre: --; Post: es comprovar si el jugador pot obtenir un seguidor concret en una crisi màgica

        bool es_lliure(int primer, int segon);
        //Pre: --; Post: retorna true si l'element a_mp[primer][segon] és buit

    private:

        int a_nf;
        int a_nc;
        Carta** a_mp;

        static const int MIDA_TAULER = 4;

        void allibera();
        // Pre: --; Post: memòria alliberada

        void reserva();
        // Pre: a_n>0 ^ a_m>0; Post: memòria reservada

        void copia(const Tauler &t);
        // Pre: --; Post: fa un duplicat de la matriu (t)

};

#endif // TAULER_H