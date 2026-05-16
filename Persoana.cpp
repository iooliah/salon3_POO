#include "Persoana.h"
//constructor cu parametri
Persoana::Persoana(const std::string& nume, const std::string& prenume, const std::string& telefon) : nume(nume), prenume(prenume), telefon(telefon) {}

//getters
const std::string& Persoana::getNume() const{ return nume; }
const std::string& Persoana::getPrenume() const{ return prenume; }
const std::string& Persoana::getTelefon() const{ return telefon; }
std::string Persoana::getNumeComplet() const{ return nume + " " + prenume; }

void Persoana::afiseaza(std::ostream& os) const{                        //interfata non-virtuala
    afiseazaVirtual(os);
}

//functie virtuala folosita pentru polimorfism
//getRol() este virtuala pura => apel dinamic
void Persoana::afiseazaVirtual(std::ostream& os) const{
    os<< "Rol: " <<getRol()<< ", Nume: " <<nume<< ", Prenume: " <<prenume<< ", Telefon: " <<telefon;
}

std::ostream& operator<<(std::ostream& os, const Persoana& p){           //operator << care foloseste interfata non-virtuala
    p.afiseaza(os);
    return os;
}
