#include "Pedichiura.h"

//constructor
Pedichiura::Pedichiura(const std::string& nume,float pret, int durata, bool gel, bool design, bool masaj) : Unghii(nume, pret, durata, gel, design), masaj(masaj){}

//getter
bool Pedichiura::getMasaj() const{ return masaj;}

int Pedichiura::durataTotala() const{
    int durataFinala = Unghii::durataTotala();      //calculez durara finala incepand cu cea din clasa de baza Unghii
    if(masaj){                                      //dureaza cu 15 min mai mult daca se alege optiunea extra de masaj
        durataFinala += 15;
    }
    return durataFinala;
}

//functie comuna de calcul pret
float Pedichiura::calcPretFinal(bool angajatExperimentat, plata tipPlata, bool clientFidel) const{
    float cost = calcPretComun(angajatExperimentat, tipPlata, clientFidel); //reutilizeaza calculul comun pentru servicii de unghii
    if(masaj){                                                              //+25 lei pentru masaj, optiune extra
        cost += 25;
    }
    return cost;
}

std::string Pedichiura::descriereServiciu() const{          //descriere completa serviciu
    std::string descriere = "Pedichiura";
    if(getGel()) descriere += " cu gel";
    if(getDesign()) descriere += " cu design";
    if(masaj) descriere += " + masaj";
    return descriere;
}

//clone
std::shared_ptr<Serviciu> Pedichiura::clone() const{
    return std::make_shared<Pedichiura>(*this);
}
//afisare virtuala
void Pedichiura::afiseazaVirtual(std::ostream& os) const{
    Unghii::afiseazaVirtual(os);
    os<<", Tip: Pedichiura" << ", Masaj: "<<(masaj ? "da" : "nu");
}
