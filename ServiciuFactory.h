#ifndef SERVICIUFACTORY_H
#define SERVICIUFACTORY_H
#include <memory>
#include <string>
#include <sstream>
#include "Serviciu.h"

//SOLID:
//  S: Single Responsibility: factory face un singur lucru, nu mai multe
//  O: Open/Closed: extensibil prin adaugarea de noi tipuri fara a modifica main

class ServiciuFactory{
public:
    static std::shared_ptr<Serviciu> creeazaDinFisier(const std::string& tipServiciu, std::istringstream& iss);     //construieste un serviciu citind optiunile extra
    static std::shared_ptr<Serviciu> creeazaInteractiv(const std::string& tipServiciu);                      //construieste interactiv un serviciu cu optiunile extra

private:
    static void valideazaTip(const std::string& tipServiciu);                        //verifica daca tipul de serviciu este recunoscut
};



#endif // SERVICIUFACTORY_H
