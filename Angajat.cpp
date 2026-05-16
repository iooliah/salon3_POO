#include "Angajat.h"

int Angajat::numarAngajati = 0;             //variabila statica, contor pentru obiectele de tip Angajat

Angajat::Angajat() : Persoana(), experienta(0), specializare("necunoscuta"){         //constructor implicit
    numarAngajati++;                                                                 //incrementez contorul
}

Angajat::Angajat(const std::string& nume, const std::string& prenume, const std::string& telefon, int experienta, const std::string& specializare)  //constr cu param
: Persoana(nume, prenume, telefon), experienta(experienta),specializare(specializare){
    numarAngajati++;
}

Angajat::Angajat(const Angajat& other) : Persoana(other), experienta(other.experienta), specializare(other.specializare){       //constr copiere
    numarAngajati++;
}

Angajat::~Angajat(){            //destructor
    numarAngajati--;
}
//getter
const std::string& Angajat::getSpecializare() const{ return specializare;}
int Angajat::getNrAngajati(){ return numarAngajati; }                       //fct statica

bool Angajat::areExperienta() const{                            //daca angajatul are mai mult de 5 ani de experienta, atunci costul serviciului va fi mai mare
    return experienta>=5;
}

std::string Angajat::getRol() const{                            //suprascriere functie virtuala pura din Persoana
    return "Angajat";
}

std::shared_ptr<Persoana> Angajat::clone() const{               //clonare prin pointer la baza
    return std::make_shared<Angajat>(*this);
}


void Angajat::afiseazaVirtual(std::ostream& os) const{          //afisare virtuala
    Persoana::afiseazaVirtual(os);
    os<< ", Experienta: " <<experienta<< " ani" << ", Specializare: " <<specializare;
    if(areExperienta()){
        os<< ", Angajat experimentat";
    }
}
