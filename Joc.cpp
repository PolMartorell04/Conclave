#include "Joc.h"
#include <iostream>
using namespace std;

Joc::Joc(){
    a_llavor=0;
}

Joc::Joc(int llavor){
    a_llavor=llavor;
}

void Joc::retirar_sobrants(Baralla& baralla){
    int aux = ((M*J)+(M*(J-j)));
    for(int i=aux; i>0; i--){
        baralla.robar_carta();
    }
}

void Joc::creacio_jug(const Jugador& jugador){
    a_jugadors[j]=jugador;
    j++;
}

void Joc::repartir_inicials(Baralla& baralla){
    for(int i=0; i<j; i++){
        for(int s=0; s<4; s++){
            Carta carta = baralla.robar_carta();
            a_jugadors[i].afegir_carta_ma(carta);
        }
    }
}

void Joc::repartir_tauler(Baralla& baralla, Tauler& tauler){
    for(int i=0; i<4; i++){
        for(int k=0; k<4; k++){
            if(not((i==1 and(k==1 or k==2)) or (i==2 and (k==1 or k==2)))){
                Carta carta = baralla.robar_carta();
                tauler.afegirCarta(i,k,carta);
            }
            else{
                Carta c = Carta();
                tauler.afegirCarta(i,k,c);
            }
        }
    }
}

void Joc::preparar(){
    Tauler tauler(J,J);
    Baralla baralla (a_llavor);
    baralla.barrejar();

    retirar_sobrants(baralla);
    repartir_inicials(baralla);
    repartir_tauler(baralla,tauler);

    PilaCartes pila_esquerra;
    PilaCartes pila_dreta;

    baralla.emplenar_pila_esquerra(pila_esquerra);
    baralla.emplenar_pila_dreta(pila_dreta);

    a_pila_esq=pila_esquerra;
    a_pila_dreta=pila_dreta;

    a_tauler=tauler;
}

void Joc::mostrar_piles_joc(){
    cout << endl << "PILA ESQUERRA:" << endl;
    a_pila_esq.mostrar();
    cout << endl << "PILA DRETA:" << endl;
    a_pila_dreta.mostrar();
}

Tauler Joc::retorn_tauler(){
    return a_tauler;
}

PilaCartes Joc::retorn_pila_esquerra(){
    return a_pila_esq;
}

PilaCartes Joc::retorn_pila_dreta(){
    return a_pila_dreta;
}

bool Joc::es_lliure(int primer, int segon){
    return a_tauler.es_lliure(primer,segon);
}

void Joc::mostrar_joc(int final_jug, int jugadors){
    cout << endl << "TORN DE " << a_jugadors[final_jug].r_nom() << endl;
    cout << string(8 + a_jugadors[final_jug].r_nom().size(), '=') << endl;
    a_tauler.mostrar_tauler(a_pila_esq,a_pila_dreta);
    cout << endl;

    cout << endl << "MA DE " << a_jugadors[final_jug].r_nom() << ":" << endl;
    a_jugadors[final_jug].mostrar_ma(1);

    cout << endl << endl << "MANS DELS OPONENTS:" << endl;
    if(final_jug>0){
        a_jugadors[0].mostrar_ma(2);
        cout << "  " << JUG_U << " " << a_jugadors[0].r_nom() << endl;
    }
    for(int i=final_jug+1; i<jugadors; i++){
        a_jugadors[i].mostrar_ma(2);
        cout << "  " << i+1 << " " << a_jugadors[i].r_nom() << endl;
    }

    cout << endl << "RESUM DELS SEGUIDORS:" << endl;
    for(int i=0; i<jugadors; i++){
        a_jugadors[i].resum_seguidors();
        cout << "  " << i+1 << " " << a_jugadors[i].r_nom() << endl;
    }
}

int Joc::comptador(char magia, int a){
    int x=0;
    if(magia=='b') x = a_jugadors[a].retorn_seg().retorn_nB();
    else if(magia=='o') x = a_jugadors[a].retorn_seg().retorn_nO();
    else if(magia=='p') x = a_jugadors[a].retorn_seg().retorn_nP();
    else if(magia=='r') x = a_jugadors[a].retorn_seg().retorn_nR();
    else if(magia=='t') x = a_jugadors[a].retorn_seg().retorn_nT();
    else if(magia=='v') x = a_jugadors[a].retorn_seg().retorn_nV();
    return x;
}

void Joc::cedir_influencia(char magia, int n_jug, int final_jug){
    Carta c;
    int s = comptador(magia, n_jug);
    int y = comptador(magia,final_jug);
    if(s==0){
        while(y>0){
            c = a_jugadors[final_jug].retorn_seg().eliminar(c);
            y--;
            a_jugadors[n_jug].retorn_seg().inserir(c);
        }
    }
}

void Joc::fer_jugada(int pos_carta, int primer, int segon, int final_jug){
    Carta c = a_jugadors[final_jug].retorn_carta(pos_carta);
    a_tauler.afegirCarta(primer,segon,c);
    obtenir_seguidors(primer,segon,c,final_jug);
    crisi_magica(c,final_jug,primer,segon);
    a_jugadors[final_jug].calcul_seg();
}

void Joc::robar_carta(char pila, int pos_carta, int final_jug){
    if(pila=='e' or a_pila_dreta.buida()){
        Carta c = a_pila_esq.cim();
        a_jugadors[final_jug].afegir_carta(c, pos_carta);
        a_pila_esq.desempila();
    }
    else if (pila=='d' or a_pila_esq.buida()) {
        Carta c = a_pila_dreta.cim();
        a_jugadors[final_jug].afegir_carta(c, pos_carta);
        a_pila_dreta.desempila();
    }
    else if(a_pila_esq.buida() and a_pila_dreta.buida()) valorar_final();
    reposar_conclave(pila);
}

void Joc::valorar_final(){
    int jugadors=0;
    int decepcio=0;
    string jugador, guanyador;

    cout << endl << "RESULTAT FINAL" << endl;
    cout << string(14, '=') << endl << endl;

    cout << "TOTS ELS SEGUIDORS:" << endl;
    for(int i=0; i<jugadors; i++){
        cout << i+1 << " " << a_jugadors[i].r_nom() << endl << " ";
        a_jugadors[i].mostrar_seg();

    }
    cout << endl;

    cout << endl << "PUNTS DE DECEPCIO:" << endl;
    cout << setfill(' ') << setw(3) << decepcio << " "
     << jugador << endl;
    cout << endl << "ENHORABONA " << guanyador << "! "
     << "HAS GUANYAT LA PARTIDA!" << endl;

}

void Joc::obtenir_seguidors(int i, int j,Carta c, int final_jug){
    int aux_i_inf = i-1;
    int aux_i_sup = i+1;
    int ajud_j_inf = j-1;
    int ajud_j_sup = j+1;
    int sortida = 0;
    int sortida2 = 0;
    int sortida3 = 0;

    Carta c1, c2, c3;

    bool fase_1_i = false;
    bool fase_2_i = false;
    bool fase_3_i = false;

    bool fase_1_s = false;
    bool fase_2_s = false;
    bool fase_3_s = false;

    int suma = c.retorn_influ();
    char magia = c.retorn_magia();
    char germandat = c.retorn_germandat();

    //Per mirar si coincideix en columna
    while (aux_i_inf>-1 and not(fase_3_i) and sortida!=5){ //de la carta cap a dalt
        if(not(a_tauler.obtElem(aux_i_inf,j).es_lliure())){
            suma+=a_tauler.obtElem(aux_i_inf,j).retorn_influ();
            fase_1_i = true;
            aux_i_inf--;
            while(aux_i_inf>-1 and not(fase_3_i) and sortida2!=5){
                if(not(a_tauler.obtElem(aux_i_inf,j).es_lliure())){
                    suma+=a_tauler.obtElem(aux_i_inf,j).retorn_influ();
                    fase_2_i = true;
                    aux_i_inf--;
                    while(aux_i_inf>-1 and sortida3!=5){
                        if(not(a_tauler.obtElem(aux_i_inf,j).es_lliure())){
                            suma+=a_tauler.obtElem(aux_i_inf,j).retorn_influ();
                            fase_3_i = true;
                        }
                        else sortida3 = 5;
                    }
                }
                else sortida2 = 5;
            }
        }
        else sortida = 5;
    }

    sortida=0;
    sortida2=0;
    sortida3 = 0;

    while(aux_i_sup<4 and not(fase_3_s) and sortida!=5){ //de la carta cap a baix
        if(not(a_tauler.obtElem(aux_i_sup,j).es_lliure())){
            suma+=a_tauler.obtElem(aux_i_sup,j).retorn_influ();
            fase_1_s = true;
            aux_i_sup++;
            while(aux_i_sup<4 and not(fase_3_s) and sortida2!=5){
                if((not(a_tauler.obtElem(aux_i_sup,j).es_lliure()))){
                    suma+=a_tauler.obtElem(aux_i_sup,j).retorn_influ();
                    fase_2_s = true;
                    aux_i_sup++;
                    while(aux_i_sup<4 and sortida3!=5){
                        if((not(a_tauler.obtElem(aux_i_sup,j).es_lliure()))){
                            suma+=a_tauler.obtElem(aux_i_sup,j).retorn_influ();
                            fase_3_s = true;
                        }
                        else sortida3 = 5;
                    }
                }
                else sortida2 = 5;
            }
        }
        else sortida = 5;
    }

    sortida = 0;
    sortida2 = 0;
    sortida3 = 0;

    if (suma>9){ //comprovar les suma i si coincideixen els paràmetres
        if(fase_3_i){
            c1=a_tauler.obtElem(aux_i_inf,j);
            aux_i_inf++;
            c2=a_tauler.obtElem(aux_i_inf,j);
            aux_i_inf++;
            c3=a_tauler.obtElem(aux_i_inf,j);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_inf,j); //borrar element de tauler
                a_jugadors[final_jug].afegir_seguidor(c1); //guardar element a seguidors
            }
            if(c2.retorn_magia()== magia or c2.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_inf,j);
                a_jugadors[final_jug].afegir_seguidor(c2);
            }
            if(c3.retorn_magia()== magia or c3.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_inf,j);
                a_jugadors[final_jug].afegir_seguidor(c3);
            }
        }
        else if(fase_2_i){
            c1=a_tauler.obtElem(aux_i_inf,j);
            aux_i_inf++;
            c2=a_tauler.obtElem(aux_i_inf,j);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_inf,j);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }
            if(c2.retorn_magia()== magia or c2.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_inf,j);
                a_jugadors[final_jug].afegir_seguidor(c2);
            }
        }
        else if (fase_1_i){
            c1=a_tauler.obtElem(aux_i_inf,j);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_inf,j);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }
        }
        if(fase_3_s){
            c1=a_tauler.obtElem(aux_i_sup,j);
            aux_i_inf--;
            c2=a_tauler.obtElem(aux_i_sup,j);
            aux_i_inf--;
            c3=a_tauler.obtElem(aux_i_sup,j);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_sup,j);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }
            if(c2.retorn_magia()== magia or c2.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_sup,j);
                a_jugadors[final_jug].afegir_seguidor(c2);
            }
            if(c3.retorn_magia()== magia or c3.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_sup,j);
                a_jugadors[final_jug].afegir_seguidor(c3);
            }
        }
        else if(fase_2_s){
            c1=a_tauler.obtElem(aux_i_sup,j);
            aux_i_inf--;
            c2=a_tauler.obtElem(aux_i_sup,j);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_sup,j);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }
            if(c2.retorn_magia()== magia or c2.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_sup,j);
                a_jugadors[final_jug].afegir_seguidor(c2);
            }
        }
        else if (fase_1_s){
            c1=a_tauler.obtElem(aux_i_sup,j);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(aux_i_sup,j);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }

        }
    }
    else suma = 0;

    fase_1_i = false;
    fase_2_i = false;
    fase_3_i = false;
    fase_1_s = false;
    fase_2_s = false;
    fase_3_s = false;

    //Per mirar si coincideix en fila

    while (ajud_j_inf>-1 and not(fase_3_i) and sortida!=5){ //de la carta cap a l'esquerra
        if(not(a_tauler.obtElem(i,ajud_j_inf).es_lliure())){
            suma+=a_tauler.obtElem(i,ajud_j_inf).retorn_influ();
            ajud_j_inf--;
            fase_1_i = true;
            while(ajud_j_inf>-1 and not(fase_3_i) and sortida2!=5){
                if(not(a_tauler.obtElem(i,ajud_j_inf).es_lliure())){
                    suma+=a_tauler.obtElem(i,ajud_j_inf).retorn_influ();
                    ajud_j_inf--;
                    fase_2_i = true;
                    while(ajud_j_inf>-1 and sortida3!=5){
                        if(not(a_tauler.obtElem(i,ajud_j_inf).es_lliure())){
                            suma+=a_tauler.obtElem(i,ajud_j_inf).retorn_influ();
                            fase_3_i = true;
                        }
                        else sortida3 = 5;
                    }
                }
                else sortida2=5;
            }
        }
        else sortida = 5;
    }

    sortida = 0;
    sortida2 = 0;
    sortida3 = 0;

    while (ajud_j_sup<4 and not(fase_3_s) and sortida!=5){ //de la carta cap a la dreta
        if(not(a_tauler.obtElem(i,ajud_j_sup).es_lliure())){
            suma+=a_tauler.obtElem(i,ajud_j_sup).retorn_influ();
            ajud_j_sup++;
            fase_1_s = true;
            while(ajud_j_sup<4 and not(fase_3_s) and sortida2!=5){
                if(not(a_tauler.obtElem(i,ajud_j_sup).es_lliure())){
                    suma+=a_tauler.obtElem(i,ajud_j_sup).retorn_influ();
                    ajud_j_sup++;
                    fase_2_s = true;
                    while(ajud_j_sup<4 and sortida3!=5){
                        if(not(a_tauler.obtElem(i,ajud_j_sup).es_lliure())){
                            suma+=a_tauler.obtElem(i,ajud_j_sup).retorn_influ();
                            fase_3_s = true;
                        }
                        else sortida3 = 5;
                    }
                }
                else sortida2 = 5;
            }
        }
        else sortida = 5;
    }

    sortida = 0;
    sortida2 = 0;
    sortida3 = 0;

    if(suma>9){ //comprovar les suma i si coincideixen els paràmetres
        if(fase_3_i){
            c1=a_tauler.obtElem(i,ajud_j_inf);
            ajud_j_inf++;
            c2=a_tauler.obtElem(i,ajud_j_inf);
            ajud_j_inf++;
            c3=a_tauler.obtElem(i,ajud_j_inf);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_inf);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }
            if(c2.retorn_magia()== magia or c2.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_inf);
                a_jugadors[final_jug].afegir_seguidor(c2);
            }
            if(c3.retorn_magia()== magia or c3.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_inf);
                a_jugadors[final_jug].afegir_seguidor(c3);
            }
        }
        else if(fase_2_i){
            c1=a_tauler.obtElem(i,ajud_j_inf);
            ajud_j_inf++;
            c2=a_tauler.obtElem(i,ajud_j_inf);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_inf);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }
            if(c2.retorn_magia()== magia or c2.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_inf);
                a_jugadors[final_jug].afegir_seguidor(c2);
            }
        }
        else{
            c1=a_tauler.obtElem(i,ajud_j_inf);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_inf);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }
        }

        if(fase_3_s){
            c1=a_tauler.obtElem(i,ajud_j_sup);
            ajud_j_inf--;
            c2=a_tauler.obtElem(i,ajud_j_sup);
            ajud_j_inf--;
            c3=a_tauler.obtElem(i,ajud_j_sup);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_sup);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }
            if(c2.retorn_magia()== magia or c2.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_sup);
                a_jugadors[final_jug].afegir_seguidor(c2);
            }
            if(c3.retorn_magia()== magia or c3.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_sup);
                a_jugadors[final_jug].afegir_seguidor(c3);
            }
        }
        else if(fase_2_s){
            c1=a_tauler.obtElem(i,ajud_j_sup);
            ajud_j_inf--;
            c2=a_tauler.obtElem(i,ajud_j_sup);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_sup);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }
            if(c2.retorn_magia()== magia or c2.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_sup);
                a_jugadors[final_jug].afegir_seguidor(c2);
            }
        }
        else{
            c1=a_tauler.obtElem(i,ajud_j_sup);
            if(c1.retorn_magia()== magia or c1.retorn_germandat()==germandat){
                a_tauler.treure_carta_t(i,ajud_j_sup);
                a_jugadors[final_jug].afegir_seguidor(c1);
            }
        }
    }
    else suma = 0;
}

int Joc::retorn_espais(){
    int espais = 0;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(a_tauler.obtElem(i,j).es_lliure()) espais++;
        }
    }
    return espais;
}

void Joc::auxiliar_repos(char pila, int i, int j){
    if(pila=='e' or a_pila_dreta.buida()){
        Carta c = a_pila_esq.cim();
        a_pila_esq.desempila();
        a_tauler.afegirCarta(i,j,c);
    }
    else if (pila=='d' or a_pila_esq.buida()) {
        Carta c = a_pila_dreta.cim();
        a_pila_dreta.desempila();
        a_tauler.afegirCarta(i,j,c);
    }
    else if(a_pila_esq.buida() and a_pila_dreta.buida()) valorar_final();
}

void Joc::crisi_magica(Carta c, int final_jug, int primer, int segon){
    if(retorn_espais()==0){
        for(int i=0; i<4; i++){
            for(int k=0; k<4; k++){
                if(a_tauler.obtElem(i,k).retorn_germandat()==c.retorn_germandat() or a_tauler.obtElem(i,k).retorn_magia()==c.retorn_magia() or (i!=primer and i!=segon)){
                    Carta carta = a_tauler.obtElem(i,k);
                    a_tauler.treure_carta_t(i,k);
                    a_jugadors[final_jug].afegir_seguidor(carta);
                }
            }
        }
    }
}

void Joc::reposar_conclave(char pila){
    int espais = retorn_espais();
    if(espais>4){
        while(espais>4){
            for(int i=0; i<4; i++){
                for(int j=0; j<4; j++){
                if(a_tauler.obtElem(i,j).es_lliure()) espais--;
                    auxiliar_repos(pila,i,j);
                }
            }
        }
    }
}