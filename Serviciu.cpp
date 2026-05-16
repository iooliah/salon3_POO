#include "Serviciu.h"

Serviciu::Serviciu(const std::string& nume, float pret, int durata) : nume(nume), pret(pret), durata(durata){}   //constructor

//interfata non-virtuala
void Serviciu::afiseaza(std::ostream& os) const{
    afiseazaVirtual(os);
}

//implementare virtuala (apelul public este non-virtual, dar redirectioneaza catre functia virtuala)
void Serviciu::afiseazaVirtual(std::ostream& os) const{
    os<< "Serviciu: " <<nume<<", Pret baza: " <<pret<< " lei, Durata: " <<durata<<" min";
}

//operator <<
std::ostream& operator<<(std::ostream& os, const Serviciu& s){
    s.afiseaza(os);
    return os;
}
