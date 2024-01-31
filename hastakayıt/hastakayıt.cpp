#include <list>
#include <queue>
#include <iostream>

using namespace std;

class Insan {
protected:
    string ad;
    int yas;
    bool engelliMi;

public:
    Insan(string ad, int yas, bool engelliMi=false) : ad(ad), yas(yas),engelliMi(engelliMi){    }
    void yazdir()const {
        cout << "Ad:" << ad << endl
            << "yas :" << yas << endl
            << "engellilik durumu : ";
        if (engelliMi)
            cout << "evet";
        else
            cout << "hayir"; 
        cout << endl;
    }
};

class Hasta :public Insan {
    int hastaNo;
    int oncelikPuani;
public:
    Hasta(int hastaNo, Insan& i) : hastaNo(hastaNo), Insan(i), oncelikPuani(0) {
        oncelikPuaniHesapla();
    }
    Hasta(int hastaNo, string ad, int yas, bool engelliMi=false) : hastaNo (hastaNo), Insan(ad, yas, engelliMi), oncelikPuani(0) {
        oncelikPuaniHesapla();
    }
    void oncelikPuaniHesapla() {
        if (engelliMi)
            oncelikPuani += 30;
        if (yas > 65)
            oncelikPuani += yas - 65; 
    }

    bool operator <(const Hasta& h) const {
        return oncelikPuani < h.oncelikPuani;
    }
    void yazdir() const {
        cout << "Hasta No :" << hastaNo << endl;
        Insan::yazdir();
        cout << "Oncelik Puani :" << oncelikPuani << endl;

    }

};
class HastaKayit {
    list<Hasta> kayitSirasi;
    priority_queue <Hasta> muayeneSirasi;
public:
    void kayit(Insan& i) {
        Hasta hasta(kayitSirasi.size() + 1, i);
        kayitSirasi.push_back(hasta);
        muayeneSirasi.push(hasta);

    }

    void kayitSirasiYazdir() {
        cout << "### Hasta kayit sirasi ###" << endl;
        if (kayitSirasi.empty())
            cout << "kayitli hasta yok" << endl;
        else {
            list <Hasta> ::iterator iter = kayitSirasi.begin();
            while (iter != kayitSirasi.end()) {
                Hasta hasta = *iter;
                hasta.yazdir();
                iter++;
                cout << endl;
            }
          
        }
        cout << "### Hasta kayit sirasi sonu ###" << endl;
    }
    void muayeneSirasiYazdir() {
        cout << "### muayene kayit sirasi ###" << endl;
        if (muayeneSirasi.empty())
            cout << "muayene bekleyen hasta yok." << endl;
        else {
            priority_queue<Hasta> kuyruk = muayeneSirasi;
            while(!kuyruk.empty()){
                Hasta hasta = kuyruk.top();
                hasta.yazdir();
                kuyruk.pop();
                if (!kuyruk.empty())
                    cout << endl;
            }

        }
        cout << "### muayene kayit sirasi sonu ###" << endl;
    }

    void hastaCagir() {
        cout << "muayeneye cagirilan hasta bilgileri" << endl;
        if (muayeneSirasi.empty())
            cout << "muayene icin bekleyen hasta yok" << endl;
        else {
            Hasta hasta = muayeneSirasi.top();
            hasta.yazdir();
            muayeneSirasi.pop();
          
        }
        cout << endl;
    }
};

int main()
{
    Insan insanlar[] = {
   Insan("arif", 30),
   Insan("ahmet", 35, 1),
   Insan("mehmet", 70),
   Insan("veli", 75, 1),
   Insan("ayse", 65,1),
   Insan("ferdi", 45)
    };

    HastaKayit banko;

    banko.kayit(insanlar[0]);
    banko.kayit(insanlar[1]);
    banko.kayit(insanlar[2]);
    banko.kayitSirasiYazdir();
    cout << endl;
    banko.muayeneSirasiYazdir();


  // banko.muayeneSirasiYazdir();
  return 0;
}

