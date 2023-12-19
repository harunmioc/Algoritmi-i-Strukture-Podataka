#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

template <typename TipEl> void insertion_sort(TipEl *niz, int vel) {
  for (int i = 1; i < vel - 1; i++) {
    auto temp = niz[i];
    int j = i - 1;
    // premjestanje elemenata vecih od temp (niz[i])
    while (j >= 0 && niz[j] > temp) {
      niz[j + 1] = niz[j];
      j--;
    }
    // j je uvijek manje za jedan u ondosu na mjesto gdje treba biti temp; (ako
    // treba biti na 0, j=-1)
    niz[j + 1] = temp;
  }
}

template <typename TipEl>
void shell_sort(TipEl *niz, int vel, std::vector<int> razmaci) {

  for (int i = 0; i < razmaci.size(); i++) {
    // biranje velicine razmaka
    int razmak = razmaci.at(i);
    // petlja koja se krece od prvog razmaka do kraja niza
    for (int j = razmak; j < vel; j++) {
      auto temp = niz[j];
      int k = j - razmak;
      // sortiranje elemenata u prividnim nizovima
      while (k > 0 && niz[k] > temp) {
        niz[k + razmak] = niz[k];
        k = k - razmak;
      }
      niz[k + razmak] = temp;
    }
  }
}

template <typename TipEl> void selection_sort(TipEl *niz, int vel) {
  for (int i = 0; i < vel - 1; i++) {
    auto minElement = niz[i];
    int pozicijaMin = i;
    for (int j = i + 1; j < vel; j++) {
      if (niz[j] > minElement) {
        minElement = niz[j];
        pozicijaMin = j;
      }
    }
    niz[pozicijaMin] = niz[i];
    niz[i] = minElement;
  }
}

template <typename TipEl> void bubble_sort(TipEl *niz, int vel) {
  for (int i = vel - 1; i > 1; i--) {
    for (int j = 0; j < i; j++) {
      if (niz[j - 1] > niz[j]) {
        auto temp = niz[j - 1];
        niz[j] = niz[j - 1];
        niz[j - 1] = temp;
      }
    }
  }
}
/*
template <typename TipEl> void bubble_sort(TipEl *niz, int vel) {

  for (int i = 0; i < vel; i++)
    for (int j = i; j < vel; j++)
      if (niz[i] > niz[j]) {
        auto temp = niz[i];
        niz[i] = niz[j];
        niz[j] = temp;
      }
}
*/
/*
template <typename TipEl> void selection_sort(TipEl *niz, int vel) {

  if (niz == nullptr)
    return;

  for (int i = 0; i < vel; i++) {
    TipEl min = niz[i];
    int mini = i;
    for (int j = i + 1; j < vel; j++)
      if (niz[j] < min) {
        min = niz[j];
        mini = j;
      }
    auto temp = niz[mini];
    niz[mini] = niz[i];
    niz[i] = temp;
  }
}
*/
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

void ucitaj(std::string filename, int *&niz, int &vel) {

  int c;
  ifstream ulaz(filename);
  std::vector<int> v;

  while (ulaz >> c) {
    v.push_back(c);
  }

  vel = v.size();
  niz = new int[vel];
  for (int i = 0; i < vel; i++)
    niz[i] = v[i];

  ulaz.close();
}

void generisi(std::string filename, int vel) {

  ofstream ulaz(filename);

  for (int i = 0; i < vel; i++)
    ulaz.put(char(rand()));

  ulaz.close();
}

void funkcija(std::string filename, int *&niz, int &vel, std::string izlaz) {
  ucitaj(filename, niz, vel);

  std::cout << "Niz glasi: ";
  for (int i = 0; i < vel; i++) {
    std::cout << niz[i];
    if (i != vel - 1)
      std::cout << " ";
  }

  std::cout << std::endl;

start:
  std::cout << "Za: merge sort - 1 , quick sort - 2 , bubble sort - 3 , "
               "selection sort - 4 : ";
  int n;
  std::cin >> n;

  auto start = std::chrono::high_resolution_clock::now();

  switch (n) {
  case 1:
    merge_sort(niz, vel);
    break;
  case 2:
    quick_sort(niz, vel);
    break;
  case 3:
    bubble_sort(niz, vel);
    break;
  case 4:
    selection_sort(niz, vel);
    break;
  default: {
    std::cout << "Unesite ispravnu opciju!" << std::endl;
    goto start;
  }
  }

  auto stop = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  for (int i = 0; i < vel - 1; i++)
    if (niz[i] > niz[i + 1])
      std::cout << "GRESKA!";

  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Niz jeste sortiran\nTrajanje sortiranja: " << duration.count()
            << " ms\nNiz sortiran: ";
  for (int i = 0; i < vel; i++) {
    std::cout << niz[i];
    if (i != vel - 1)
      std::cout << " ";
  }

  std::ostringstream os;
  std::ofstream izlazz(izlaz);

  for (int i = 0; i < vel; i++) {
    os << niz[i];
    if (i != vel - 1)
      os << ", ";
  }
  std::string s(os.str());

  izlazz << s;

  izlazz.close();
}

int main() {
  int *niz;
  int vel;
  funkcija("ulaz2.txt", niz, vel, "primjer2.txt");
}