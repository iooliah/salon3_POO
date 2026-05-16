#include "Client.h"

int Client::numarClienti = 0;             //variabila statica, contor pentru obiectele de tip Client

Client::Client() : Persoana(), nrVizite(0){         //constr implicit
    numarClienti++;                                 //incrementez contor
}

Client::Client(const std::string& nume, const std::string& prenume, const std::string& telefon, int nrVizite) : Persoana(nume, prenume, telefon), nrVizite(nrVizite){  //constr cu param
    numarClienti++;
}
Client::Client(const Client& other) : Persoana(other), nrVizite(other.nrVizite){        //constr copiere
    numarClienti++;
}

Client::~Client(){               //destructor
    numarClienti--;
}

bool Client::esteClientFidel() const{ return nrVizite >= 5;}    //daca un client vine de mai mult de 5 ori, primeste reducere
int Client::getNrClienti(){ return numarClienti; }              //fct statica

std::string Client::getRol() const{return "Client"; }           //override fct virtuala

std::shared_ptr<Persoana> Client::clone() const{               //clonare prin pointer la baza
    return std::make_shared<Client>(*this);
}

void Client::afiseazaVirtual(std::ostream& os) const{          //afisare virtuala
    Persoana::afiseazaVirtual(os);
    os<< ", Numar vizite: " <<nrVizite;
    if(esteClientFidel()){
        os<< ", Client fidel";
    }
}
