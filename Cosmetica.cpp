#include "Cosmetica.h"

//constructor
Cosmetica::Cosmetica(float pret, int durata, bool masca, const std::string& tipTratament)
    : Serviciu("Cosmetica", pret, durata), masca(masca), tipTratament(tipTratament){}

int Cosmetica::durataTotala() const {
    int durataFinala = durata;
    if(masca){                          //durata mai mare pt optiune extra si in functie de tipul de tratament
        durataFinala += 15;
    }
    if(tipTratament == "corp"){
        durataFinala += 20;
    }else if(tipTratament == "par"){
        durataFinala += 10;
    }
    return durataFinala;
}

//calcul pret final
float Cosmetica::calcPretFinal(bool angajatExperimentat, plata tipPlata, bool clientFidel) const{
    float cost = pret;
    if(masca){                              //pret in plus pt optiune extra si pt tipul de tratament
        cost += 25;
    }
    if(tipTratament =="corp"){
        cost += 40;
    }else if(tipTratament == "par"){
        cost += 20;
    }

    if(angajatExperimentat){            //cu 10 lei in plus pt experienta angajatului
        cost += 10;
    }
    if(clientFidel){                    //10% reducere daca clientul este fidel
        cost =cost * 0.9f;
    }
    if(tipPlata == plata::CASH){        //-5 lei pt plata cash
        cost -= 5;
    }

    return cost;
}

std::string Cosmetica::descriereServiciu() const{       //descriere completa a serviciului de tratamente
    std::string descriere = "Cosmetica";
    descriere += tipTratament;
    if(masca){
        descriere+= " + masca";
    }
    return descriere;
}

//clone
std::shared_ptr<Serviciu> Cosmetica::clone() const {
    return std::make_shared<Cosmetica>(*this);
}
//afisare virtula
void Cosmetica::afiseazaVirtual(std::ostream& os) const {
    Serviciu::afiseazaVirtual(os);
    os << ", Tip: Cosmetica" << ", Tratament: " << tipTratament << ", Masca: " << (masca ? "da" : "nu");
}
