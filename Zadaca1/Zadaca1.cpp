#include <cstddef>
#include <iostream>
#include <new>
#include <stdexcept>

/* 1.
   Zadatak
            */

template <typename TipEl> class Lista {

public:
  Lista(){};
  virtual ~Lista(){};
  virtual int brojElemenata() const = 0;
  // metoda    trenutni()
  virtual TipEl trenutni() const = 0;
  virtual TipEl &trenutni() = 0;
  // metoda    prethodni() i sljedeci()
  virtual bool sljedeci() = 0;
  virtual bool prethodni() = 0;
  // metode    pocetak() i kraj()
  virtual void pocetak() = 0;
  virtual void kraj() = 0;

  virtual void obrisi() = 0;
  // metode dodaj
  virtual void dodajIspred(const TipEl &a) = 0;
  virtual void dodajIza(const TipEl &a) = 0;

  virtual TipEl &operator[](int i) = 0;
  virtual const TipEl operator[](int i) const = 0;
};


template <typename spp> 
 struct Cvor {
    spp a;
    Cvor *sljedeci;
    Cvor *prethodni;
  };
  
template <typename TipEl> class DvostrukaLista : public Lista<TipEl> {
private:
  struct Cvor {
    TipEl a;
    Cvor* sljedeci;
    Cvor* prethodni;
  };
  Cvor *prvi, *posljednji, *tekuci;
  int duzina;

public:
  DvostrukaLista<TipEl>()
      : duzina(0), prvi(nullptr), tekuci(nullptr), posljednji(nullptr) {}
  ~DvostrukaLista<TipEl>() {
    while (prvi != nullptr) {
      tekuci = prvi;
      prvi = prvi->sljedeci;
      delete tekuci;
    }
    duzina = 0;
  }
  int brojElemenata() const { return duzina; }

  DvostrukaLista(const DvostrukaLista<TipEl> &a) {
    duzina = 0;
    prvi = nullptr;
    tekuci = nullptr;
    posljednji = nullptr;

    if (a.duzina == 0) {
      prvi = nullptr;
      posljednji = nullptr;
      tekuci = nullptr;
    } else {
      Cvor *temp = a.prvi;
      if (prvi)
        pocetak();
      while (temp != nullptr) {
        dodajIza(temp->a);
        sljedeci();
        temp = temp->sljedeci;
        posljednji = tekuci;
      }
    }
  }

  // operator =
  DvostrukaLista<TipEl> &operator=(const DvostrukaLista<TipEl> &a) {

    if (this == &a)
      return *this;

    while (prvi != nullptr) {
      tekuci = prvi;
      prvi = prvi->sljedeci;
      delete tekuci;
    }

    duzina = 0;
    if (a.duzina == 0) {
      prvi = nullptr;
      posljednji = nullptr;
      tekuci = nullptr;
    } else {
      Cvor *temp = a.prvi;

      while (temp != nullptr) {
        dodajIza(temp->a);
        sljedeci();
        temp = temp->sljedeci;
        posljednji = tekuci;
      }
    }
    return *this;
  }

  TipEl &operator[](int i) {
    if (i < 0 || i >= duzina)
      throw std::range_error("Nema elemenata");
    Cvor *temp = prvi;
    for (int j = 0; j < i; j++)
      temp = temp->sljedeci;
    return temp->a;
  }

  const TipEl operator[](int i) const {
    if (i < 0 || i >= duzina)
      std::range_error("Nema elemenata");
    Cvor *temp = prvi;
    for (int j = 0; j < i; j++)
      temp = temp->sljedeci;
    return temp->a;
  }

  TipEl &trenutni() {
    if (prvi == nullptr)
      throw std::range_error("Nema elemenata");
    return tekuci->a;
  }

  TipEl trenutni() const {
    if (prvi == nullptr)
     throw std::range_error ("Nema elemenata");
    return tekuci->a;
  }

  bool prethodni() {
    if (prvi == nullptr)
      std::range_error("Nema elemenata");

    if (tekuci == prvi)
      return false;

    tekuci=tekuci->prethodni;

    return true;
  }

  bool sljedeci() {
    if (prvi == nullptr)
      std::range_error("Nema elemenata");

    if (tekuci->sljedeci == nullptr)
      return false;

    tekuci = tekuci->sljedeci;
    return true;
  }

  void pocetak() {
    if (prvi == nullptr)
      std::range_error("Nema elemenata");
    tekuci = prvi;
  }

  void kraj() {
    if (prvi == nullptr)
      std::range_error("Nema elemenata");

    tekuci = posljednji;
  }

  void obrisi() {
    if (prvi == nullptr)
      std::__throw_domain_error("Nema elemenata");

    if (tekuci == prvi) {
      prvi = prvi->sljedeci;
      delete tekuci;
      tekuci = prvi;
      duzina--;

      if (duzina == 0)
        posljednji = nullptr;
    } else {
      Cvor *temp = prvi;
      while (temp->sljedeci != tekuci)
        temp = temp->sljedeci;
      Cvor* ispred_tekuceg = tekuci->sljedeci;

      temp->sljedeci = ispred_tekuceg;
      delete tekuci;

      if(temp->sljedeci==nullptr)
        posljednji=tekuci=temp;
    else{
        ispred_tekuceg->prethodni=temp;
        tekuci=ispred_tekuceg;
    }

      duzina--;
    }
  }

  void dodajIspred(const TipEl &a) {
    Cvor *novi = new Cvor;
    novi->a = a;

    if (prvi == nullptr) {
      prvi = posljednji = tekuci = novi;
      prvi->sljedeci = nullptr;
      tekuci->sljedeci = nullptr;
    } else if (prvi == tekuci) {
      novi->sljedeci = prvi;
        prvi->prethodni=novi;
      prvi = novi;
    } else {
        novi->prethodni=tekuci->prethodni;
        tekuci->prethodni=novi;

        novi->sljedeci=tekuci;
        novi->prethodni->sljedeci = novi;
    }
    duzina++;
  }

  void dodajIza(const TipEl &a) {
    Cvor *novi = new Cvor;
    novi->a = a;


    if (prvi == nullptr) {
      prvi = posljednji = tekuci = novi;
      prvi->sljedeci = nullptr;
      novi->sljedeci = nullptr;
      tekuci->sljedeci = nullptr;
    } else {
      novi->sljedeci = tekuci->sljedeci;
      tekuci->sljedeci=novi;
      novi->prethodni = tekuci;
      if (tekuci == posljednji)
        posljednji = novi;
    else
        (novi->sljedeci)->prethodni=novi;
    }
    duzina++;
  }

template <typename spp1>
  friend class Iterator;

}; 

template <typename TipEl>
class Iterator{
    const DvostrukaLista<TipEl> *lista;
    Cvor<TipEl> *trenutno;
  public:
    Iterator(const DvostrukaLista<TipEl> &l){
        lista=&l;
        trenutno=l.prvi;
    }
    TipEl dajTrenutni(){
        if(!lista->brojElemenata()) throw std::domain_error("Lista prazna");
        return trenutno->a;
    }
    bool sljedeci(){
        if(!lista->brojElemenata()) throw std::domain_error("Lista prazna");
        if(!trenutno->sljedeci) return false;
        trenutno=trenutno->sljedeci;
        return true;
    }
};

template<typename TipEl>
TipEl dajMaksimum(const Lista<TipEl>& n)
{
    if(n.brojElemenata()==0)std::__throw_domain_error("Nema elemenata");

    Iterator<TipEl> p=dynamic_cast<const DvostrukaLista<TipEl>&>(n);
    TipEl max=p.dajTrenutni();

    while(p.sljedeci())
    if(p.dajTrenutni()>max)max=p.dajTrenutni(); 

    return max;
}





int main(){
    return 0;
}

