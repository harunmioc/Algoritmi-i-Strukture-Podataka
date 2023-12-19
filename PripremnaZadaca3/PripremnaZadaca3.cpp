/*
    Pripremna Zadaća za vježbu 3
                                    */
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename TipEl> class Stek{
    private:
        struct Cvor{
            TipEl a;
            Cvor* sljedeci;};
            
        int broj_elemenata;
        Cvor *vrh_steka;
    public:
//konstruktor i destruktor
    Stek():vrh_steka(nullptr), broj_elemenata(0){};
    ~Stek(){
        while(vrh_steka!=nullptr){
            Cvor* temp=vrh_steka;
            vrh_steka=vrh_steka->sljedeci;
            delete temp;
        }
        broj_elemenata=0;
    };
//konstruktor kopije i operator dodjele
    Stek(const Stek& s){
        broj_elemenata=0;
        vrh_steka=nullptr;

        if (s.broj_elemenata == 0) { vrh_steka = nullptr; 
        } else {
          Cvor* temp= s.vrh_steka;

                    while(temp!=nullptr){
                        stavi(temp->a);
                        temp=temp->sljedeci;
                    } 

        temp=s.vrh_steka;
        Cvor* trenutni_pravog_steka = this->vrh_steka;
        while(temp!=nullptr){
            trenutni_pravog_steka->a=temp->a;
            temp=temp->sljedeci;
            trenutni_pravog_steka=trenutni_pravog_steka->sljedeci;
        }
      }
    };
    Stek &operator = (const Stek &s){
        if (this == &s)
            return *this;

        while(vrh_steka!=nullptr){
            Cvor* temp=vrh_steka;
            vrh_steka=vrh_steka->sljedeci;
            delete temp;
        }

        broj_elemenata=0;
        if(s.broj_elemenata==0)
            vrh_steka=nullptr;
        else{
            Cvor* temp=s.vrh_steka;

            while(temp!=nullptr){
                stavi(temp->a);
                temp=temp->sljedeci;   
            }

        //pomocni pokazviaci/kretaci kroz stek da se ne izgubi prvi
            temp=s.vrh_steka; 
            Cvor* trenutni_pravog_steka=this->vrh_steka;
            while(temp!=nullptr){
                trenutni_pravog_steka->a = temp->a;
                temp=temp->sljedeci;
                trenutni_pravog_steka=trenutni_pravog_steka->sljedeci;
            }
        }
    return *this;
    };
//metode
    void brisi(){
        while(vrh_steka!=nullptr){
            Cvor* temp=vrh_steka;
            vrh_steka=vrh_steka->sljedeci;
            delete temp;
        }
        broj_elemenata=0;
    };
    void stavi(const TipEl& el){
        Cvor *novi = new Cvor;
        novi->a=el;
    if(vrh_steka==nullptr){
        vrh_steka=novi;
        vrh_steka->sljedeci=nullptr;
    }else{
        novi->sljedeci=vrh_steka;
        vrh_steka=novi;
    }
    broj_elemenata++;
    };
    TipEl skini(){
        if(broj_elemenata==0)
            throw std::range_error("Nema elemenata");

        TipEl temp= vrh_steka->a;
        Cvor* brisi = vrh_steka;
        vrh_steka=vrh_steka->sljedeci;
        delete brisi;
        broj_elemenata--;
    return temp;
    };
    TipEl& vrh(){
        if(broj_elemenata==0)
            throw std::range_error("Nema elemenata");
        return vrh_steka->a;
    };
    int brojElemenata(){return broj_elemenata;}
};

int main(){
    Stek<int> stack;

    stack.stavi(5);
    stack.stavi(10);
    stack.stavi(15);

    std::cout << "Top steka: " << stack.vrh() << std::endl;

    std::cout << "izbaceni element: " << stack.skini() << std::endl;

    std::cout << "Top steka nakon izbacivanja: " << stack.vrh() << std::endl;

    Stek<int> kopiraniStek = stack;

    std::cout << "Broj elemenata u kopiji steka: " << kopiraniStek.brojElemenata() << std::endl;

    Stek<int> Stek3;
    Stek3 = kopiraniStek;

    std::cout << "Vrh Steka 3 (operator =)  " << Stek3.vrh() << std::endl;

    Stek3.brisi();
    std::cout << "Broj el u steku 3 nakon brisanja: " << Stek3.brojElemenata() << std::endl;
    std::cout<< "Kraj";
    return 0;
}