#ifndef SERVICIU_H
#define SERVICIU_H
#include <memory>
#include <string>
#include <iostream>

enum class plata{CASH, CARD, TRANSFER};

class Serviciu {
protected:
    std::string nume;
    float pret;
    int durata;

public:
    Serviciu() = default;                                                 //constructor
    Serviciu(const std::string& nume, float pret, int durata);            //constructor cu parametri
    virtual ~Serviciu() = default;                                        //destructor virtual

    void afiseaza(std::ostream& os) const;

    //functii virtuale pure
    virtual float calcPretFinal(bool angajatExperimentat, plata tipPlata, bool clientFidel) const = 0;      //suma finala dupa reduceri si optiuni extra
    virtual std::string descriereServiciu() const = 0;
    virtual int durataTotala() const = 0;                                                                   //durata finala, incluzand optiunile extra

    virtual std::shared_ptr<Serviciu> clone() const = 0;                   //clonare polimorfica prin pointer de baza(in Programare)

    friend std::ostream& operator<<(std::ostream& os, const Serviciu& s);  //operator<<

protected:
    virtual void afiseazaVirtual(std::ostream& os) const;                  //functie virtuala apelata din interfata non-virtuala
};


#endif // SERVICIU_H
