#include "SalonSingleton.h"

//Meyers Singleton: initializare lazy (la prima apelare), thread-safety, distrugere automata la sfarsitul programului

SalonSingleton& SalonSingleton::getInstance(){              //singura instanta a clasei
    static SalonSingleton instance;
    return instance;
}

//functie care intoarce pretul de baza al serviciului ales; inlocuieste pretFix() din salon2
float SalonSingleton::pretFix(const std::string& tipServiciu) const{
    if(tipServiciu == "MANICHIURA") return 100.0f;
    if(tipServiciu == "PEDICHIURA") return 90.0f;
    if(tipServiciu == "COAFOR") return 70.0f;
    if(tipServiciu == "COSMETICA") return 90.0f;
    return 0.0f;
}
//functie care intoarce durata de baza a serviciului ales; inlocuieste durataFixa() din salon2
int SalonSingleton::durataFixa(const std::string& tipServiciu) const{
    if(tipServiciu == "MANICHIURA") return 90;
    if(tipServiciu == "PEDICHIURA") return 70;
    if(tipServiciu == "COAFOR") return 40;
    if(tipServiciu == "COSMETICA") return 80;
    return 0;
}

//getters const
const std::string& SalonSingleton::dataAniversara() const{ return dataAniversara_; }
float SalonSingleton::reducereAniversara() const{ return reducereAniversara_; }
float SalonSingleton::reducereProgramariMultiple() const{ return reducereProgramariMultiple_; }
int SalonSingleton::pragProgramariMultiple() const{return pragProgramariMultiple_; }


