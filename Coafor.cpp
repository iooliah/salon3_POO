#include "Coafor.h"

//constructor
Coafor::Coafor(float pret, int durata, bool vopsit, const std::string& lungimePar) : Serviciu("Coafor", pret, durata), vopsit(vopsit), lungimePar(lungimePar) {}
//getter
bool Coafor::getVopsit() const{ return vopsit; }

int Coafor::durataTotala() const{
    int durataFinala = durata;
    if(vopsit){                         //durata mai mare pt optiune extra si pt cu cat este mai lung parul
        durataFinala += 50;
    }
    if(lungimePar=="mediu"){
        durataFinala += 10;
    } else if(lungimePar == "lung"){
        durataFinala += 20;
    }
    return durataFinala;
}

//calcul pret final
float Coafor::calcPretFinal(bool angajatExperimentat, plata tipPlata, bool clientFidel) const{
    float cost = pret;
    if(vopsit){                     //pret mai mare pt optiune extra si pt cu cat este mai lung parul
        cost += 70;
    }
    if(lungimePar== "mediu"){
        cost += 10;
    } else if(lungimePar == "lung"){
        cost += 20;
    }

    if(angajatExperimentat){        //daca angajatul este experimentat -> +15lei
        cost += 15;
    }
    if(clientFidel){                //reducere 10% daca clientul este fidel
        cost = cost * 0.9f;
    }
    if(tipPlata == plata::CASH){    //cu 5 lei mai ieftin pt plata cash
        cost -= 5;
    }
    return cost;
}

std::string Coafor::descriereServiciu() const{          //descriere completa a serviciului de coafat
    std::string descriere = "Coafor";
    if(vopsit) descriere += " + vopsit";
    descriere += " (" + lungimePar + ") ";

    return descriere;
}

//clone
std::shared_ptr<Serviciu> Coafor::clone() const{
    return std::make_shared<Coafor>(*this);
}

//afisare virtuala
void Coafor::afiseazaVirtual(std::ostream& os) const{
    Serviciu::afiseazaVirtual(os);
    os<< ", Tip: Coafor" << ", Vopsit: " <<(vopsit ? "da" : "nu")<< ", Lungime par: " <<lungimePar;
}
