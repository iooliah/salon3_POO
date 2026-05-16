#ifndef ANGAJAT_H
#define ANGAJAT_H
#include <string>
#include <iostream>
#include <memory>

#include "Persoana.h"

class Angajat : public Persoana{
private:
    int experienta;
    std::string specializare;
    static int numarAngajati;                                        //pentru numararea angajatilor
    void afiseazaVirtual(std::ostream& os) const override;           //afisare virtuala suprascrisa in clasa derivata

public:
    Angajat();                                                       //constructor
    Angajat(const std::string& nume, const std::string& prenume, const std::string& telefon, int experienta, const std::string& specializare);
    Angajat(const Angajat& other);                                   //constructor copiere
    ~Angajat() override;                                             //destructor virtual suprascris din Persoana

    //getters
    const std::string& getSpecializare() const;
    static int getNrAngajati();

    bool areExperienta() const;                             //functie care verifica experienta; >= 5 ani => +10 lei
    std::string getRol() const override;                    //functie virtuala suprascrisa din Persoana
    std::shared_ptr<Persoana> clone() const override;       //clonare polimorfica prin pointer la baza
};



#endif // ANGAJAT_H

