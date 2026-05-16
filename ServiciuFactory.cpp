#include "ServiciuFactory.h"
#include "SalonSingleton.h"
#include "Manichiura.h"
#include "Pedichiura.h"
#include "Coafor.h"
#include "Cosmetica.h"
#include "Exceptii.h"
#include <iostream>


//verific daca tipul de serviciu introdus este valid
void ServiciuFactory::valideazaTip(const std::string& tipServiciu){
    if(tipServiciu!="MANICHIURA" && tipServiciu!="PEDICHIURA" && tipServiciu!="COAFOR" && tipServiciu!="COSMETICA"){
        throw ProgramareInvalidaExceptie("tip serviciu invalid: " + tipServiciu);
    }
}

//creez un serviciu folosind date citite din fisier si folosesc Factory Pattern pentru a crea obiectul derivat corect
std::shared_ptr<Serviciu> ServiciuFactory::creeazaDinFisier(const std::string& tipServiciu, std::istringstream& iss){
    valideazaTip(tipServiciu);
    const auto& configurare = SalonSingleton::getInstance();            //configuratii globale prin Singleton
    const float pret = configurare.pretFix(tipServiciu);
    const int durata = configurare.durataFixa(tipServiciu);

    //in fct de tipul serviciului, creez obiectul derivat prin pointer la baza
    if(tipServiciu == "MANICHIURA"){
        bool gel, design, crema;
        iss>> gel >> design >> crema;
        return std::make_shared<Manichiura>("Manichiura", pret, durata, gel, design, crema);
    }else if(tipServiciu == "PEDICHIURA"){
        bool gel, design, masaj;
        iss>> gel >> design >> masaj;
        return std::make_shared<Pedichiura>("Pedichiura", pret, durata, gel, design, masaj);
    }else if(tipServiciu == "COAFOR"){
        bool vopsit;
        std::string lungimePar;
        iss>> vopsit >> lungimePar;
        return std::make_shared<Coafor>(pret, durata, vopsit, lungimePar);
    } else if(tipServiciu == "COSMETICA"){
        bool masca;
        std::string tipTratament;
        iss>> masca >> tipTratament;
        return std::make_shared<Cosmetica>(pret, durata, masca, tipTratament);
    }

}


//creez un serviciu folosind date introduse la tastatura
std::shared_ptr<Serviciu> ServiciuFactory::creeazaInteractiv(const std::string& tipServiciu){
    valideazaTip(tipServiciu);
    const auto& configurare = SalonSingleton::getInstance();            //configuratii globale prin Singleton
    const float pret = configurare.pretFix(tipServiciu);
    const int durata = configurare.durataFixa(tipServiciu);

    if(tipServiciu == "MANICHIURA"){
        bool gel, design, crema;
        std::cout<< "Gel (0/1): ";
        std::cin>> gel;
        std::cout<< "Design (0/1): ";
        std::cin>> design;
        std::cout<< "Crema (0/1): ";
        std::cin>> crema;
        return std::make_shared<Manichiura>("Manichiura", pret, durata, gel, design, crema);
    }else if(tipServiciu == "PEDICHIURA"){
        bool gel, design, masaj;
        std::cout<< "Gel (0/1): ";
        std::cin>> gel;
        std::cout<< "Design (0/1): ";
        std::cin>> design;
        std::cout<< "Masaj (0/1): ";
        std::cin>> masaj;
        return std::make_shared<Pedichiura>("Pedichiura", pret, durata, gel, design, masaj);
    }else if(tipServiciu == "COAFOR"){
        bool vopsit;
        std::string lungimePar;
        std::cout<< "Vopsit (0/1): ";
        std::cin>> vopsit;
        std::cout<< "Lungime par: ";
        std::cin>> lungimePar;
        return std::make_shared<Coafor>(pret, durata, vopsit, lungimePar);
    }else if(tipServiciu == "COSMETICA"){
        bool masca;
        std::string tipTratament;
        std::cout<< "Masca (0/1): ";
        std::cin >> masca;
        std::cout<< "Tip tratament: ";
        std::cin >> tipTratament;
        return std::make_shared<Cosmetica>(pret, durata, masca, tipTratament);
}
}
