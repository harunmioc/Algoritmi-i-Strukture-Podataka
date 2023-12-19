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

/* 2.
   Zadatak
            */

template <typename TipEl> class NizLista : public Lista<TipEl> {
protected:
  int kapacitet; // Kapacitet liste
  int duzina;    // Dužina liste
  int tekuci;    // Pozicija tekućeg elementa
  TipEl **niz;   // Niz za elemente liste
  // void provjera() {}
  void alokacija(int a) {
    if (a < 0)
      return;
    TipEl **pom = new TipEl *[kapacitet * 2] { nullptr };

    for (int i{}; i < duzina; i++)
      pom[i] = niz[i];
    delete[] niz;

    niz = pom;
    duzina = a;
    kapacitet *= 2;
  }

public:  

    NizLista(int br = 0)
      : niz(nullptr), kapacitet(1000), duzina(0), tekuci(0) {
    alokacija(br);
  };
  ~NizLista() {
    for (int i = 0; i < duzina; i++)
      delete niz[i];
    delete[] niz;
  }

  NizLista(const NizLista &a) {
    duzina = a.duzina;
    kapacitet = a.kapacitet;
    niz = new TipEl *[kapacitet] { nullptr };
    for (int i = 0; i < a.duzina; i++)
      niz[i] = new TipEl(*a.niz[i]);
    tekuci = a.tekuci;
  }

  NizLista<TipEl> &operator=(NizLista<TipEl> a) {
    if (this == &a)
      return *this;
    for (int i = 0; i < duzina; i++) {
      delete niz[i];
    }
    delete[] niz;

    duzina = a.duzina;
    kapacitet = a.kapacitet;
    niz = new TipEl *[a.kapacitet] { nullptr };
    for (int i = 0; i < a.duzina; i++)
      niz[i] = new TipEl(*a.niz[i]);
    tekuci = a.tekuci;
    return *this;
  }

  int brojElemenata() const override { return duzina; }


  // metoda    trenutni()
  TipEl trenutni() const override {
    if (duzina == 0)
      throw std::range_error("Nema elemenata");
    return *(niz[tekuci]);
  }

  TipEl &trenutni() override {
    if (duzina == 0)
      throw std::range_error("Nema elemenata");
    return *(niz[tekuci]);
  }
  // metoda    prethodni() i sljedeci()
  bool sljedeci() override {
    if (duzina == 0)
      throw std::range_error("Nema sljedeceg");
    else if (tekuci == duzina - 1)
      return false;
    else {
      tekuci++;
      return true;
    }
  }
  bool prethodni() override {
    if (duzina == 0)
      throw std::range_error("Nema prethodnog");
    else if (tekuci == 0)
      return false;
    else {
      tekuci--;
      return true;
    }
  }
  // metode    pocetak() i kraj()
  void pocetak() override {
    if (duzina == 0)
      throw std::range_error("Nema elemenata");
    tekuci = 0;
  }
  void kraj() override {
    if (duzina == 0)
      throw std::range_error("Nema elemenata");
    tekuci = duzina - 1;
  }
  // moguca greska
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! zbog
  // duzina--
  void obrisi() override {
    if (duzina == 0)
      throw std::range_error("Nema elemenata");

    delete niz[tekuci];
    if (tekuci == duzina - 1) {
      duzina--;
      tekuci--;
    } else {
      for (int i = tekuci; i < duzina - 1; i++) {
        niz[i] = niz[i + 1];}
      // problem viseceg pokazivaca; stavljamo na nullptr
      niz[duzina - 1] = nullptr;
      duzina--;
    }
  }

  // metode dodaj
  void dodajIza(const TipEl &a) override {
    if (duzina >= kapacitet) {
      alokacija(duzina + 1);
    } else {
      duzina++;
    }

    if (duzina == 1) {
      niz[0] = new TipEl(a);
      tekuci = 0;
    } else if (kapacitet > duzina) {
      for (int i = duzina - 1; i > tekuci; i--) {
        niz[i + 1] = niz[i];
      }
      niz[tekuci + 1] = new TipEl(a);
    }
  }

  void dodajIspred(const TipEl &a) override {
    if (duzina >= kapacitet) {
      alokacija(duzina + 1);
    } else {
      duzina++;
    }

    if (duzina == 1) {
      niz[0] = new TipEl(a);
      tekuci = 0;
    } else if (kapacitet > duzina) {
      for (int i = duzina - 1; i >= tekuci; i--) {
        niz[i + 1] = niz[i];
      }
      niz[tekuci] = new TipEl(a);
      tekuci++;
    }
  }

  TipEl &operator[](int i) override {
    if (i < 0 || i > duzina - 1) {
      throw std::range_error("Greska");
    }
    return *niz[i];
  }
  const TipEl operator[](int i) const override {
    if (i < 0 || i > duzina - 1) {
      throw std::range_error("Greska");
    }
    return *niz[i];
  }
};

template <typename TipEl> class JednostrukaLista : public Lista<TipEl> {
private:
  struct Cvor {
    TipEl a;
    Cvor *sljedeci;
  };
  Cvor *prvi, *posljednji, *tekuci;
  int duzina;

public:
  JednostrukaLista<TipEl>()
      : duzina(0), prvi(nullptr), tekuci(nullptr), posljednji(nullptr) {}
  ~JednostrukaLista<TipEl>() {
    while (prvi != nullptr) {
      tekuci = prvi;
      prvi = prvi->sljedeci;
      delete tekuci;
    }
    duzina = 0;
  }
  int brojElemenata() const { return duzina; }

  JednostrukaLista(const JednostrukaLista<TipEl> &a) {
    duzina = 0;
    prvi = nullptr;
    tekuci = nullptr;
    posljednji = nullptr;

    if (a.duzina == 0) {
      prvi = nullptr;
      posljednji = nullptr;
      tekuci = nullptr;
    } else {
      Cvor *temp(a.prvi);
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
  JednostrukaLista<TipEl> &operator=(const JednostrukaLista<TipEl> &a) {

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
      Cvor *temp(a.prvi);

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
      std::__throw_range_error("Nema elemenata");
    Cvor *temp(prvi);
    for (int j = 0; j < i; j++)
      temp = temp->sljedeci;
    return temp->a;
  }

  const TipEl operator[](int i) const {
    if (i < 0 || i >= duzina)
      std::__throw_range_error("Nema elemenata");
    Cvor *temp(prvi);
    for (int j = 0; j < i; j++)
      temp = temp->sljedeci;
    return temp->a;
  }

  TipEl &trenutni() {
    if (prvi == nullptr)
      std::__throw_range_error("Nema elemenata");
    return tekuci->a;
  }

  TipEl trenutni() const {
    if (prvi == nullptr)
      std::__throw_range_error("Nema elemenata");
    return tekuci->a;
  }

  bool prethodni() {
    if (prvi == nullptr)
      std::__throw_range_error("Nema elemenata");

    if (tekuci == prvi)
      return false;

    Cvor *temp(prvi);
    while (temp->sljedeci != tekuci)
      temp = temp->sljedeci;

    tekuci = temp;
    return true;
  }

  bool sljedeci() {
    if (prvi == nullptr)
      std::__throw_range_error("Nema elemenata");

    if (tekuci->sljedeci == nullptr)
      return false;

    tekuci = tekuci->sljedeci;
    return true;
  }

  void pocetak() {
    if (prvi == nullptr)
      std::__throw_range_error("Nema elemenata");
    tekuci = prvi;
  }

  void kraj() {
    if (prvi == nullptr)
      std::__throw_range_error("Nema elemenata");

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

      temp->sljedeci = tekuci->sljedeci;
      delete tekuci;
      tekuci = temp->sljedeci;

      if (tekuci == nullptr)
        posljednji = tekuci = temp;

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
      prvi = novi;
    } else {
      Cvor *temp = prvi;
      while (temp->sljedeci != tekuci)
        temp = temp->sljedeci;
      temp->sljedeci = novi;
      novi->sljedeci = tekuci;
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
      tekuci->sljedeci = novi;
      if (tekuci == posljednji)
        posljednji = novi;
    }
    duzina++;
  }
};
    
int main() {
    
    NizLista<int> nizLista;

    nizLista.dodajIza(5);
    nizLista.dodajIspred(10);
    nizLista.dodajIza(15);
    nizLista.dodajIspred(20);

    std::cout << "Element na indexu 2: " << nizLista[2] << std::endl;

    nizLista.pocetak();
    std::cout << "Trenutni element: " << nizLista.trenutni() << std::endl;
    nizLista.sljedeci();
    std::cout << "Sljedeci element: " << nizLista.trenutni() << std::endl;

    nizLista.obrisi();
    std::cout << "Trenutni element nakon brisanja: " << nizLista[1] << std::endl;

  ///////////////////////////////////////////////////////////////////////////////////////
    JednostrukaLista<std::string> jednostrukaLista;

    jednostrukaLista.dodajIspred("Hello");
    jednostrukaLista.dodajIza("World");
    jednostrukaLista.dodajIza("!");

    std::cout << "Element na indexu 1: " << jednostrukaLista[1] << std::endl;

    jednostrukaLista.kraj();
    std::cout << "Trenutni element na kraju: " << jednostrukaLista.trenutni() << std::endl;
    jednostrukaLista.prethodni();
    std::cout << "Prethodni element: " << jednostrukaLista.trenutni() << std::endl;

    jednostrukaLista.obrisi();
    std::cout << "Element na indexu 1 nakon brisanja: " << jednostrukaLista[1] << std::endl;
    std::cout<<"Kraj";
  return 0;
}