#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


template <typename TipEl>
int Particija(TipEl *niz, const int prvi, const int zadnji) {
//uzimamo pivot i jedan brojac kojim se krecemo i trazimo element VECI od pivota
    TipEl pivot = niz[prvi];
    int p= prvi+1;

//krecemo se kroz niz sve dok ne nadjemo poziciju elementa koji je VECI od pivota
    while(p<=zadnji  &&  niz[p]<=pivot){
        p++;
    }

//kada smo nasli el VECI od pivota opet se nastavljamo kretati
//sve dok ne naiđemo na element MANJI od pivota
//razmjenjujemo mjesta 'p' i tog elemnta MANJEG od pivota i povecavamo brojac 'p' za 1
    for(int i=(p+1); i<=zadnji; i++){
        if(niz[i] <= pivot){
            TipEl temp = niz[i];
            niz[i] = niz[p];
            niz[p] = temp;
            p++; 
        }
    }

//na kraju pivot stavljamo na poziciju p-1
//tj pivot stavljamo u sredinu izmedju desnog i lijevog podniza
//pivot dijeli niz na brojeve manje od pivota i brojeve vece od pivota

  TipEl temp = niz[p-1];
  niz[p-1] = niz[prvi];
  niz[prvi] = temp;

  return p - 1;
}


template <typename TipEl> void quick_sort(TipEl *niz, int vel) {
    static int pocetak = 0;
    static int kraj = vel-1; 

    if(pocetak < kraj){
        int pivot = Particija(niz, pocetak, kraj);
    //pamtimo kraj za poslije
        int tempKraj = kraj;
        kraj = pivot-1;
        quick_sort(niz, vel);
        kraj = tempKraj;
        pocetak = pivot+1;
        quick_sort(niz, vel);
    }
}





