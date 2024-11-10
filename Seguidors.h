#ifndef SEGUIDORS_H
#define SEGUIDORS_H
#include "Carta.h"
#include <iostream>
#include <string>
using namespace std;

class Seguidors{ //llista dinàmica ordenada de cartes cartes

    public:
        Seguidors();
        // Pre:--; Post: llista buida

        Seguidors(const Seguidors &o);
        // Pre:--; Post: seguidors es copia de o

        ~Seguidors();
        // Pre: --; Post: memoria dinamica alliberada

        Seguidors &operator=(const Seguidors &o);
        // Pre:--; Post: seguidors es copia de o i abans s'ha alliberat la memoria ocupada per aquesta llista

        bool buida() const;
        // Pre:--; Post: ens diu si la llista es buida

        bool existeix(Carta c) const;
        // Pre:--; Post: ens diu si c existeix a la llista

        void inserir (Carta c);
        // Pre: --; Post: si c no existeix s'ha inserit en el lloc que li toca per mantenir l'ordre; en cas contrari no es fa cap insercio

        Carta eliminar (Carta c);
        // Pre:--; Post: e s'ha esborrat en el cas que existís; en cas contrari no es fa res

        void mostrar_seguidors() const;
        // Pre:--; Post: mostra la llista

        void calcular_seguidors();
        // Pre:--; Post: calcula el nombre de punts d'influència de cada tipus de màgia

        void mostrar_resum();
        // Pre:--; Post: mostra la llista resumida per punts que es tenen de cada màgia

        int retorn_nB(); //Retorna el comptador nB d'atribut
        int retorn_nO(); //Retorna el comptador nO d'atribut
        int retorn_nP(); //Retorna el comptador nP d'atribut
        int retorn_nR(); //Retorna el comptador nR d'atribut
        int retorn_nT(); //Retorna el comptador nT d'atribut
        int retorn_nV(); //Retorna el comptador nV d'atribut

    private:

        struct Node {
            Carta dada;
            Node *seg;
        };
        Node *a_inici;

        //Nombre de punts d'influència de cada màgia
        int nB = 0;
        int nO = 0;
        int nP = 0;
        int nR = 0;
        int nT = 0;
        int nV = 0;

        void copia(const Seguidors &o);
        // Pre: memoria dinamica alliberada; Post: seguidors es copia de o

        void allibera();
        // Pre: --; Post: memoria dinamica alliberada

};

#endif // SEGUIDORS_H