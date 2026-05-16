#ifndef PROGRAMAREBUILDER_H
#define PROGRAMAREBUILDER_H
#include <optional>
#include <memory>
#include <string>
#include "Client.h"
#include "Angajat.h"
#include "Serviciu.h"
#include "Programare.h"


class ProgramareBuilder{
private:
    std::optional<Client> client_;
    std::optional<Angajat> angajat_;
    std::shared_ptr<Serviciu> serviciu_;
    std::string data_;
    std::string ora_;
    std::optional<plata> tipPlata_;

public:
    ProgramareBuilder() = default;

    //chaining: fiecare metoda intoarce *this prin referinta
    ProgramareBuilder& client(const Client& c);
    ProgramareBuilder& angajat(const Angajat& a);
    ProgramareBuilder& serviciu(std::shared_ptr<Serviciu> s);
    ProgramareBuilder& data(const std::string& d);
    ProgramareBuilder& ora(const std::string& o);
    ProgramareBuilder& tipPlata(plata p);

    Programare build() const;           //construieste obiectul Programare

    void reseteaza();                   //permite reutilizarea aceluiasi builder pt a construi mai multe obiecte
};



#endif // PROGRAMAREBUILDER_H

