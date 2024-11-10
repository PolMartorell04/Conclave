#ifndef PILACARTES_H
#define PILACARTES_H
#include <iostream>
#include <string>
#include "Carta.h"
using namespace std;

class PilaCartes{ //pila dinàmica de cartes;

    public:

        PilaCartes();
        // Pre: --; Post: pila buida

        PilaCartes(const PilaCartes& o);
        // Pre: --; Post: aquesta pila es copia de la pila o

        ~PilaCartes();
        // Pre: --; Post: memoria alliberada (inclosa la dinàmica)

        void mostrar();
        // Pre: --; Post: es mostra la pila dinàmica

        bool buida() const;
        // Pre: -- ; Post: retorna cert si la pila es buida, fals en c.c.

        Carta cim() const;
        // Pre: pila no buida; Post: retorna el valor del cim de la pila

        void empila(Carta c);
        // Pre: --; Post: s'ha afegit c a dalt de la pila

        void desempila();
        // Pre: pila no buida; Post: s'ha eliminat element de dalt de la pila

        PilaCartes& operator=(const PilaCartes& o);
        // Pre: -- ; Post: aquesta pila es copia de la pila o i la seva memòria dinàmica ha estat prèviament alliberada

    private:

        struct Node {
            Carta valor;
            Node* seg;
        };

    // ATRIBUTS
        Node* a_cim; // punter al cim de la pila

    // METODES PRIVATS

        void copia(const PilaCartes& o);
        // Pre: pila buida; Post: aquesta pila es copia de la pila o

        void allibera();
        // Pre: --; Post: memoria dinàmica alliberada

};

#endif // PILACARTES_H