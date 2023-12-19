#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

template <typename T>
class  Stek{
struct Cvor{
    T element;
    Cvor* sljedeci;
};
Cvor *vrhcina=nullptr;
int br_elemenata;

public:

Stek():vrhcina(nullptr),br_elemenata(0){}

~Stek(){
    while(vrhcina!=nullptr){
        auto pomocni=vrhcina;
        vrhcina=vrhcina->sljedeci;
        delete pomocni;
    }
    br_elemenata=0;
}
void brisi(){
    while(vrhcina!=nullptr){
        auto pomocni=vrhcina;
        vrhcina=vrhcina->sljedeci;
        delete pomocni;
    }
    br_elemenata=0;
}
void stavi(const T &a){
    Cvor *novi= new Cvor;
    novi->element=a;
    if(vrhcina==nullptr)
    {
        vrhcina=novi;
        novi->sljedeci=nullptr;

    }else
    {
        novi->sljedeci=vrhcina;
        vrhcina=novi;
    }
    br_elemenata++;
}

int brojElemenata() const { return br_elemenata; }

Stek<T>(const Stek<T> &s){
    br_elemenata=0;
    if(s.br_elemenata==0)
    {
        vrhcina=nullptr;
    }else
    {
        auto pomocni=s.vrhcina;
        while(pomocni!=nullptr){
            stavi(pomocni->element);
            pomocni=pomocni->sljedeci;
        }
        pomocni=s.vrhcina; Cvor *tekuci=vrhcina;
        while (pomocni != nullptr) {
        tekuci->element=pomocni->element;
        pomocni=pomocni->sljedeci;
        tekuci=tekuci->sljedeci;
    } 
    br_elemenata=s.br_elemenata;
    }
}
Stek<T> &operator=(Stek<T> s){
    swap(vrhcina,s.vrhcina);
    swap(br_elemenata,s.br_elemenata);
    return *this;
}

T skini(){
    if(vrhcina==nullptr)
        throw logic_error("Greska stek je prazan");
    T rez=vrhcina->element;
    auto pomocni=vrhcina;
    vrhcina=vrhcina->sljedeci;
    delete pomocni;
    br_elemenata--;
    return rez;
}

T &vrh(){
    if(vrhcina==nullptr)
        throw logic_error("greska");
    return vrhcina->element;
}
};

void pretraga(Stek<vector<int> >& s, int trazeni)
{
    static int lol=0;
    if(s.brojElemenata()==0){
       std::cout<<"Nema elementa";
        return;
    }
    std::vector<int> v = s.vrh();
    if(v.size()==0 || v.at(0)>trazeni){
        s.skini();
        lol++;
        pretraga(s,trazeni);
        s.stavi(v);
    }else{
        //v=s.vrh();
        int donja=0,gornja=v.size();
        while(donja<=gornja-1){
            long int sredina=(donja+gornja)/2;
            if(v.at(sredina)==trazeni){
                std::cout<<sredina<<" "<<s.brojElemenata()-1;
                return;            
            }
            if(v.at(sredina)<trazeni)
                donja=sredina+1;
            else
                gornja=sredina-1;
        }
        std::cout<<"Nema elementa";
        return;
    }
    
}


int main(){


    Stek<std::vector<int>> s;
    std::vector<int> t1 = {1, 2, 3, 4, 5};
    std::vector<int> t2 = {6, 8};
    std::vector<int> t3 = {9, 10, 130};
    std::vector<int> t4 = {157, 226, 3424};

    s.stavi(t1);
    s.stavi(t2);
    s.stavi(t3);
    s.stavi(t4);

    std::cout << "Rezultat pretrage za element 5: ";
    pretraga(s, 5);
    std::cout << std::endl;

    std::cout << "Rezultat pretrage za element 130: ";
    pretraga(s, 130);
    std::cout << std::endl;

    std::cout << "Rezultat pretrage za element 157: ";
    pretraga(s, 157);
    std::cout << std::endl;

    std::cout << "Rezultat pretrage za element 7: ";
    pretraga(s, 7);
    std::cout << std::endl;

    std::cout << "Rezultat pretrage za element 1000: ";
    pretraga(s, 1000);
    std::cout << std::endl;


return 0;
}