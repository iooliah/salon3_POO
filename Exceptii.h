#ifndef EXCEPTII_H
#define EXCEPTII_H
#include <stdexcept>
#include <string>
#include <vector>

class Client;
class Angajat;
class Programare;

class SalonExceptii : public std::runtime_error{            //clasa de baza pentru toate exceptiile
public:
    explicit SalonExceptii(const std::string& mesaj);
};
class ProgramareInvalidaExceptie : public SalonExceptii{        //exceptie pentru programari invalide
public:
    explicit ProgramareInvalidaExceptie(const std::string& mesaj);
};


template <typename T>                   //functie template care intoarce numele
std::string numeEntitate();

template <>
inline std::string numeEntitate<Client>(){
    return "client";
}
template <>
inline std::string numeEntitate<Angajat>(){
    return "angajat";
}
template <>
inline std::string numeEntitate<Programare>(){
    return "programare";
}

//clasa template care generealizeaza exceptiile de tip "persoana inexistenta"
template <typename T>
class EntitateInexistentaExceptie : public SalonExceptii{
private:
    std::string criteriu_;

public:
    //construiesc mesajul exceptiei in functie de tipul T
    explicit EntitateInexistentaExceptie(const std::string& criteriu = "") : SalonExceptii("Nu exista " + numeEntitate<T>() + ": " + criteriu), criteriu_(criteriu) {}

    const std::string& getCriteriu() const{
        return criteriu_;
    }

};

//pastrez numele vechi din proiect
using ClientInexistentExceptie  = EntitateInexistentaExceptie<Client>;
using AngajatInexistentExceptie = EntitateInexistentaExceptie<Angajat>;

#endif // EXCEPTII_H
