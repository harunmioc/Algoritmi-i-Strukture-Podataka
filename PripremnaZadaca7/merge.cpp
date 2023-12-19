#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

template <typename TipEl>
void Merge(TipEl *niz, const int pocetak, const int krajPrvogPodniza, const int pocetakDrugogPodniza, const int kraj) {
//'i' je brojac kroz LIJEVI podniz
//'j' je brojac kroz DESNI podniz
//'k' je pocetna pozicija u pravom pocetnom nizu koji je zadan (tj *niz)
  int i=0, j=(pocetakDrugogPodniza-pocetak), k=pocetak;
//NOTE: varijable smo vratili za [pocetak] da bi njihovo pozicioniranje bilo od 0-te pozicije
//pravimo pomocni niz u koji cemo spojiti LIJEVI i DESNI podniz
  TipEl *B = new TipEl[kraj-pocetak+1];
  for (int m = 0; m <= kraj-pocetak; m++)
    B[m] = niz[pocetak+m];

//sortiranje u pocetni "*niz"
//sortiramo tako sto poredimo vec sortirane podnizove i stavljamo na pozicije u poctnom nizu (*niz)
// 0< = krajPrvogPodniza  &&  pocetakPrvogPodniza <= kraj
  while (i <= krajPrvogPodniza-pocetak && j <= kraj-pocetak) {
    //LIJEVI  <  DESNI
    if (B[i] < B[j])
      niz[k] = B[i++];
    else
      niz[k] = B[j++];
    k++;
  }

//preostali elementi LIJEVOG
  while (i <= krajPrvogPodniza - pocetak)
    niz[k++] = B[i++];
//preostali elementi DESNOG
  while (j <= pocetakDrugogPodniza - pocetak)
    niz[k++] = B[j++];
  delete[] B;
}




template <typename TipEl> void merge_sort(TipEl *niz, int vel) {
// pocetak i kraj vidimo kao globalnu varijablu kroz sve funkcije
  static int pocetak = 0;
  static int kraj = vel - 1;

  if (kraj > pocetak) {
//dijeljenje (pod)niza na dva manja podniza
    int krajPrvogPodniza = (pocetak + kraj - 1) / 2;
    int pocetakDrugogPodniza = krajPrvogPodniza + 1;
//pamcenje granica (pod)niza prije dijeljenja na podniz  (LIJEVI podniz)
    auto tempKraj = kraj;
    auto tempPocetak = pocetak;
//postavljanje GLOBALNOG kraja na kraj LIJEVOG podniza
//pocetak je ostavljen na pravom mjestu
    kraj = krajPrvogPodniza;

//dalje dijeljenje LIJEVOG podniza (ako uopste moze dalje da se dijeli)
    merge_sort(niz, vel);
//kada se zavrsi dijeljenje LIJEVOG podniza vraca se na DESNI podniz i njega dijelimo
//postavljanje GLOBALNIH pocetak i kraj na granice DESNOG podniza
    pocetak=pocetakDrugogPodniza;
    kraj = tempKraj;
    merge_sort(niz, vel);
//nakon dijeljenja DESNOG podniza vracamo GLOBALNI pocetak na zapamceni pocetak
//kako bi mogli dobiti onaj prvobitni (pod)niz koji je podijeljen
    pocetak = tempPocetak;
//spajamo desni i lijevi podniz i sortiramo ih
    Merge(niz, pocetak, krajPrvogPodniza, pocetakDrugogPodniza, kraj);
  }
}

int main() {

  int *niz = new int[13]{25, 20, 4, 18, 16, 11, 10, 5, 14, 35, 28, 32, 7};

  merge_sort(niz, 13);

  for (int i = 0; i < 13; i++)
    std::cout << i << ". clan: " << niz[i] << std::endl;
}