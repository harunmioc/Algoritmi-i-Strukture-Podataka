#include <cmath>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

using namespace std;

template <typename TipKljuca, typename TipVrijednosti> class Mapa {

public:
  Mapa() {}
  virtual ~Mapa(){};
  virtual int brojElemenata() const = 0;
  virtual TipVrijednosti &operator[](TipKljuca i) = 0;
  virtual const TipVrijednosti operator[](TipKljuca i) const = 0;
  virtual void obrisi() = 0;
  virtual void obrisi(const TipKljuca &kljuc) = 0;
};

template <typename TipKljuca, typename TipVrijednosti>
class NizMapa : public Mapa<TipKljuca, TipVrijednosti> {
  int velicina, broj_elemenata;
  std::pair<TipKljuca, TipVrijednosti> **p;

public:
  // konstr
  NizMapa()
      : Mapa<TipKljuca, TipVrijednosti>(), broj_elemenata(0), velicina(100000),
        p(new std::pair<TipKljuca, TipVrijednosti> *[velicina]()){};
  // destr
  ~NizMapa() {
    for (int i = 0; i < broj_elemenata; i++)
      delete p[i];
    delete[] p;
  }

  // kopirajuci konstr
  NizMapa(const NizMapa<TipKljuca, TipVrijednosti> &m) {
    broj_elemenata = m.broj_elemenata;
    velicina = m.velicina;
    if (m.velicina == 0)
      p = nullptr;
    else {
      p = new std::pair<TipKljuca, TipVrijednosti> *[velicina]();
      for (int i = 0; i < broj_elemenata; i++)
        p[i] = new std::pair<TipKljuca, TipVrijednosti>(*m.p[i]);
    }
  }

  // operator =
  NizMapa &operator=(NizMapa<TipKljuca, TipVrijednosti> m) {
    std::swap(velicina, m.velicina);
    std::swap(broj_elemenata, m.broj_elemenata);
    std::swap(p, m.p);
    return *this;
  }

  // metoda  obrisi()
  void obrisi() {
    if (broj_elemenata == 0)
      throw std::range_error("Nema elemenata");
    for (int i = 0; i < broj_elemenata; i++)
      delete p[i];
    broj_elemenata = 0;
  }

  // metoda obrisi(const TipKljuca &kljuc)
  void obrisi(const TipKljuca &kljuc) {
    for (int i = 0; i < broj_elemenata; i++) {
      if (p[i]->first == kljuc) {
        delete p[i];
        for (int j = i; j < broj_elemenata - 1; j++)
          p[j] = p[j + 1];
        p[broj_elemenata] = nullptr;
        broj_elemenata--;
        return;
      }
    }
    throw std::logic_error("Kljuc ne postoji");
  }

  // metoda brojElemenata() i metoda velicina()

  int brojElemenata() const { return broj_elemenata; }

  int Velicina() const { return velicina; }

  // operator []
  const TipVrijednosti operator[](TipKljuca kljuc) const {
    for (int i = 0; i < broj_elemenata; i++)
      if (p[i]->first == kljuc)
        return p[i]->second;

    return TipVrijednosti();
  }

  TipVrijednosti &operator[](TipKljuca kljuc) {
    // u slucaju da je niz pun, pravimo novi s vise memorije
    if (broj_elemenata == velicina) {
      std::pair<TipKljuca, TipVrijednosti> **temp =
          new std::pair<TipKljuca, TipVrijednosti> *[velicina + 10000]();
      for (int i = 0; i < broj_elemenata; i++) {
        temp[i] = new std::pair<TipKljuca, TipVrijednosti>(*p[i]);
        delete p[i];
      }
      delete[] p;
      velicina += 10000;
      p = temp;
      temp = nullptr;
    }

    // pretraga za kljucem
    for (int i = 0; i < broj_elemenata; i++)
      if (p[i]->first == kljuc)
        return p[i]->second;
    // u slucaju da ne postoji kljuc pravimo novi clan s tim kljucem i praznom
    // vrijednosti
    p[broj_elemenata] =
        new std::pair<TipKljuca, TipVrijednosti>(kljuc, TipVrijednosti());
    broj_elemenata++;

    return p[broj_elemenata - 1]->second;
  }
};

// testne funckije

void testOperatoraZagrade1() {
  NizMapa<int, std::string> mapa;
  mapa[1] = "Bojan";
  mapa[2] = "Harun";

  std::cout << "Element sa kljucem 1: " << mapa[1] << std::endl;
  std::cout << "Element sa kljucem 2: " << mapa[2] << std::endl;
}
void testOperatorZagrade2() {
  NizMapa<int, std::string> mapa;
  mapa[1] = "Bojan";
  mapa[2] = "Harun";
  const NizMapa<int, std::string> constMapa = mapa;
  std::cout << "Element sa kljucem 1: " << constMapa[1] << std::endl;
  std::cout << " element sa kljucem 2: " << constMapa[2] << std::endl;
  std::cout << "Element sa nepostojećim kljucem 3: " << constMapa[3]
            << std::endl;
}

void testObrisiSve() {
  NizMapa<int, std::string> mapa;
  mapa[23] = "michael jordan";
  mapa[2] = "dva";
  mapa[12] = "brrrrr";
  mapa[12] = "br";

  std::cout << "Broj elemenata prije brisanja: " << mapa.brojElemenata()
            << std::endl;
  mapa.obrisi();
  std::cout << "Broj elemenata nakon brisanja: " << mapa.brojElemenata()
            << std::endl;
}

void testObrisi() {
  NizMapa<int, std::string> mapa;
  mapa[23] = "michael jordan";
  mapa[2] = "dva";
  mapa[12] = "brrrrr";
  mapa[12] = "br";

  std::cout << "Broj elemenata prije brisanja: " << mapa.brojElemenata()
            << std::endl;
  mapa.obrisi(23);
  std::cout << "Broj elemenata nakon brisanja: " << mapa.brojElemenata()
            << std::endl;

  // Pokušaj brisanja nepostojećeg elementa
  std::cout << "Pokusaj brisanja nepostejec kljuca (315414124): " << std::endl;
  try {
    mapa.obrisi(315414124);
  } catch (const std::logic_error &e) {
    std::cout << e.what() << std::endl;
  }
}

void testKonstruktora(){
    NizMapa<int, std::string> mapa;
    mapa[23] = "michael jordan";
    mapa[2] = "dva";
    mapa[12] = "brrrrr";
    mapa[12] = "br";

    NizMapa<int, std::string> mapa2(mapa);
    NizMapa<int, std::string> &mapa3 = mapa2;

    mapa.obrisi();
    std::cout<<"Broj elemenata mape 1:"<<mapa.brojElemenata()<<"\nBroj elemenata mape 2:"<<mapa2.brojElemenata(); std::cout<<"\nBroj elemenata mape 3:"<<
mapa3.brojElemenata(); mapa2.obrisi(); std::cout<<"\nBroj elemenata mape 3 nakon brisanja mape 2 teeba biti 0 => Broj el. mape 3: "<<mapa3.brojElemenata();
}

int main() {
  testOperatoraZagrade1();
  testOperatorZagrade2();
  testObrisi();
  testObrisiSve();
  testKonstruktora();

  std::cout << "\nSvi testovi uspesno izvrseni!" << std::endl;

  return 0;
}