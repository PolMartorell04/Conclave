#ifndef CARTA_H
#define CARTA_H
#include <iostream>
#include <string>
using namespace std;

class Carta{ //conté la informació d'una carta del joc

    public:
        Carta();
        //Pre: --; Post: carta inicialitzada a 0.

        Carta(char magia, int influencia, char germandat);
        //Pre: --; Post: carta inicialitzada a una magia, influencia i germandat entrades per paràmetres

        void mostrar_carta();
        //Pre: carta no buida; Post: mostra la carta actual

        void mostrar_revers();
        //Pre: carta no buida; Post: mostra el revers de la carta actual

        bool carta_igual(Carta c);
        //Pre: --; Post: retorna true si la carta actual i c són iguals

        bool carta_mes_gran(Carta c);
        //Pre: --; Post: retorna true si la carta actual és major que c

        char retorn_magia();
        //Pre: --; Post: retorna la màgia de la carta actual

        int retorn_influ();
        //Pre: --; Post: retorna els punts d'influència de la carta actual

        char retorn_germandat();
        //Pre: --; Post: retorna la germandat de la carta actual

        bool es_lliure();
        //Pre: --; Post: retorna true si la influencia de la carta és 0, false en c.c.

    private:

        char a_magia;
        int a_influencia;
        char a_germandat;
};

#endif // CARTA_H