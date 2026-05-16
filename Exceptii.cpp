#include "Exceptii.h"

SalonExceptii::SalonExceptii(const std::string& mesaj) : std::runtime_error(mesaj){}

ClientInexistentExceptie::ClientInexistentExceptie() : SalonExceptii("Client inexistent"){}

AngajatInexistentExceptie::AngajatInexistentExceptie() : SalonExceptii("Angajat inexistent"){}

ProgramareInvalidaExceptie::ProgramareInvalidaExceptie(const std::string& mesaj): SalonExceptii(mesaj){}
