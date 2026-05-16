#include "ProgramareBuilder.h"
#include "Exceptii.h"


ProgramareBuilder& ProgramareBuilder::client(const Client& c){
    client_ = c;
    return *this;
}
ProgramareBuilder& ProgramareBuilder::angajat(const Angajat& a){
    angajat_ = a;
    return *this;
}
ProgramareBuilder& ProgramareBuilder::serviciu(std::shared_ptr<Serviciu> s){
    serviciu_ = s;
    return *this;
}
ProgramareBuilder& ProgramareBuilder::data(const std::string& d){
    data_ = d;
    return *this;
}
ProgramareBuilder& ProgramareBuilder::ora(const std::string& o){
    ora_ = o;
    return *this;
}
ProgramareBuilder& ProgramareBuilder::tipPlata(plata p){
    tipPlata_ = p;
    return *this;
}

Programare ProgramareBuilder::build() const{        //construieste obiectul Programare si verifica daca au fost completate toate datele
    if(!client_) throw ProgramareInvalidaExceptie("builder: lipseste clientul");
    if(!angajat_) throw ProgramareInvalidaExceptie("builder: lipseste angajatul");
    if(!serviciu_) throw ProgramareInvalidaExceptie("builder: lipseste serviciul");
    if(data_.empty()) throw ProgramareInvalidaExceptie("builder: lipseste data");
    if(ora_.empty()) throw ProgramareInvalidaExceptie("builder: lipseste ora");
    if(!tipPlata_) throw ProgramareInvalidaExceptie("builder: lipseste tipul platii");

    return Programare(*client_, *angajat_, serviciu_, data_, ora_, *tipPlata_);
}

void ProgramareBuilder::reseteaza(){        //permite reutilizarea aceluiasi builder pt a construi mai multe obiecte
    client_.reset();
    angajat_.reset();
    serviciu_.reset();
    data_.clear();
    ora_.clear();
    tipPlata_.reset();
}
