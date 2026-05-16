#ifndef EXCEPTII_H
#define EXCEPTII_H
#include <stdexcept>
#include <string>

//clasa de baza pentru toate exceptiile
class SalonExceptii : public std::runtime_error{
public:
    explicit SalonExceptii(const std::string& mesaj);
};

class ClientInexistentExceptie : public SalonExceptii{     //exceptie cand clientul nu este gasit
public:
    ClientInexistentExceptie();
};

class AngajatInexistentExceptie : public SalonExceptii{     //exceptie cand angajatul nu este gasit sau selectat gresit
public:
    AngajatInexistentExceptie();
};

class ProgramareInvalidaExceptie : public SalonExceptii{     //exceptie pentru programari invalide(exp: ora ocupata, fara angajat disponibil)
public:
    explicit ProgramareInvalidaExceptie(const std::string& mesaj);
};



#endif
