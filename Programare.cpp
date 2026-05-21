#include <utility>
#include "Programare.h"
#include "Manichiura.h"
#include "Pedichiura.h"
#include "Unghii.h"
#include "Coafor.h"
#include "SalonSingleton.h"

Programare::Programare(const Client& client, const Angajat& angajat, std::shared_ptr<Serviciu> serviciu, const std::string& data, const std::string& ora, plata tipPlata)
: client(client), angajat(angajat), serviciu(serviciu), data(data), ora(ora), tipPlata(tipPlata){}   //constructor

//constructor copiere
Programare::Programare(const Programare& other) : client(other.client), angajat(other.angajat), serviciu(other.serviciu ? other.serviciu->clone() : nullptr),data(other.data), ora(other.ora), tipPlata(other.tipPlata) {}

//copy and swap
Programare& Programare::operator=(Programare other){        //operator =
    swap(*this, other);
    return *this;
}
void swap(Programare& a, Programare& b){            //fct folosita pt copy and swap
    using std::swap;
    swap(a.client, b.client);
    swap(a.angajat, b.angajat);
    swap(a.serviciu, b.serviciu);
    swap(a.data, b.data);
    swap(a.ora, b.ora);
    swap(a.tipPlata, b.tipPlata);
}

//getters
const Client& Programare::getClient() const{ return client; }
const Angajat& Programare::getAngajat() const{ return angajat; }
const std::string& Programare::getData() const{ return data; }
const std::string& Programare::getOra() const{ return ora; }

bool Programare::esteAcelasiClient(const Client& c1, const Client& c2){
    if((c1.getNume()==c2.getNume()) && (c1.getPrenume()==c2.getPrenume()) && (c1.getTelefon()==c2.getTelefon())){
        return true;            //daca numele,prenumele si telefonul a 2 programari sunt la fel, atunci este acelasi client programat
    }
    return false;
}
int Programare::getDurataTotala() const{         //apel virtual prin pointer la baza Serviciu
    return serviciu->durataTotala();
}

//functii statice
int Programare::numaraProgramariClientZi(const std::vector<Programare>& programari, const Client& client, const std::string& data){
    int nr=0;
    for(const Programare& programare : programari){
        if(programare.getData()==data && esteAcelasiClient(programare.getClient(), client)){        //pt a numara cate programari/zi pt un client
            nr++;                                                                                   //daca in aceeasi data gasesc acelasi client, incrementez nr
        }
    }
    return nr;
}
float Programare::calcIncasariZi(const std::vector<Programare>& programari, const std::string& data){
    float suma = 0;                                                     //calcul incasari dintr-o zi
    for(const Programare& programare : programari){
        if(programare.getData() == data){                               //daca o programare are data aleasa, adaug costul programarii
            suma += programare.calcCostFinal(programari);
        }
    }
    return suma;
}

float Programare::calcCostFinal(const std::vector<Programare>& toateProgramarile) const{        //calcul cost final pt un client/zi
    bool angajatExperimentat = angajat.areExperienta();
    bool clientFidel = client.esteClientFidel();
    float cost = serviciu->calcPretFinal(angajatExperimentat, tipPlata, clientFidel);           //apelare virtuala prin pointer la clasa de baza
    int nrProgramariZi = numaraProgramariClientZi(toateProgramarile, client, data);

    const auto& configurare = SalonSingleton::getInstance();

    if(data == configurare.dataAniversara()){                                            //folosesc din SalonSingleton
        cost = cost * configurare.reducereAniversara();
    }
    if(nrProgramariZi >= configurare.pragProgramariMultiple()){
        cost = cost * configurare.reducereProgramariMultiple();
    }
    return cost;
}


//dynamic_pointer_cast
bool Programare::areServiciuCuTimpSuplimentar() const{
    //downcast de la pointer la baza Serviciu la clase derivate pentru a verifica tipul real al serviciului
    auto manichiura = std::dynamic_pointer_cast<Manichiura>(serviciu);
    auto pedichiura = std::dynamic_pointer_cast<Pedichiura>(serviciu);
    auto unghii = std::dynamic_pointer_cast<Unghii>(serviciu);
    auto coafor = std::dynamic_pointer_cast<Coafor>(serviciu);

    //verific daca serviciul are optiuni extra care cresc durata programarii
    if(manichiura && (manichiura->getCrema() || manichiura->getGel() || manichiura->getDesign()) ){
        return true;
    }
    if(pedichiura && (pedichiura->getMasaj() || pedichiura->getGel() || pedichiura->getDesign())){
        return true;
    }
    if(unghii && (unghii->getGel() || unghii->getDesign())){
        return true;
    }
    if(coafor && coafor->getVopsit()){
        return true;
    }
    return false;
}

//fct pt descrierea programarii
std::string Programare::descriereProgramare() const{
    return client.getNumeComplet()+ " are programare la " + serviciu->descriereServiciu() + " cu " + angajat.getNumeComplet() + " pe data de " + data+ " la ora " +ora;
}

//operator <<
std::ostream& operator<<(std::ostream& os, const Programare& p){
    os<< "Client: " << p.client<< "\nAngajat: " << p.angajat<< "\nServiciu: ";
    os<<*p.serviciu;
    os<<"\nDescriere serviciu: " <<p.serviciu->descriereServiciu();
    os<<"\nDurata totala: " <<p.serviciu->durataTotala() << " minute";
    os<< "\nData: "<<p.data<< "\nOra: " <<p.ora<< "\nTip plata: ";

    if(p.tipPlata == plata::CASH){
        os<< "CASH";
    }else if(p.tipPlata == plata::CARD){
        os<< "CARD";
    }else {
        os<< "TRANSFER";
    }
    return os;
}
