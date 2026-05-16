#include "Unghii.h"

//constructor
Unghii::Unghii(const std::string& nume, float pret, int durata, bool gel, bool design) : Serviciu(nume, pret, durata), gel(gel), design(design){}

//getters
bool Unghii::getGel() const{ return gel; }
bool Unghii::getDesign() const{ return design; }

int Unghii::durataTotala() const{
    int durataFinala = durata;              //adaug la durata de baza
    if(gel) durataFinala += 20;             //daca aleg una dintre optiunile extra, vizita dureaza cu 20/15 min mai mult
    if(design) durataFinala += 15;

    return durataFinala;
}

//functie comuna de calcul pret(mani/pedi)
float Unghii::calcPretComun(bool angajatExperimentat, plata tipPlata, bool clientFidel) const{
    float cost = pret;              //adaug la pretul de baza

    if(gel) cost += 50;             //optiunile extra +20/50 lei
    if(design) cost += 20;

    if(angajatExperimentat){        //pretul creste cu 10 daca e experimentat angajatul ales
        cost += 10;
    }
    if(clientFidel){                //reducere 10% daca clientul este fidel
        cost = cost * 0.9f;
    }
    if(tipPlata == plata::CASH){    //cu 5 lei mai ieftin daca se alege plata cash
        cost -= 5;
    }
    return cost;
}

float Unghii::calcPretFinal(bool angajatExperimentat, plata tipPlata, bool clientFidel) const{
    return calcPretComun(angajatExperimentat, tipPlata, clientFidel);
}

std::string Unghii::descriereServiciu() const{          //descriere completa a serviciului ales
    std::string descriere = "Serviciu unghii";
    if(gel) descriere += " cu gel";
    if(design) descriere += " cu design";
    return descriere;
}

//clone
std::shared_ptr<Serviciu> Unghii::clone() const{
    return std::make_shared<Unghii>(*this);
}
//afisare virtuala
void Unghii::afiseazaVirtual(std::ostream& os) const{
    Serviciu::afiseazaVirtual(os);
    os<< ", Tip: Unghii" << ", Gel: "<<(gel ? "da" : "nu")<< ", Design: " <<(design ? "da" : "nu");
}
