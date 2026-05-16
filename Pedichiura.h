#ifndef PEDICHIURA_H
#define PEDICHIURA_H

#include "Unghii.h"

class Pedichiura : public Unghii{
protected:
    bool masaj;         //optiune extra

public:
    Pedichiura() = default;                                                                             //constructor
    Pedichiura(const std::string& nume, float pret, int durata, bool gel, bool design, bool masaj);     //constructor cu param

    bool getMasaj() const;

    //functii virtuale suprascrise
    int durataTotala() const override;
    float calcPretFinal(bool angajatExperimentat, plata tipPlata, bool clientFidel) const override;
    std::string descriereServiciu() const override;

    std::shared_ptr<Serviciu> clone() const override;                     //clonare polimorfica prin pointer la baza

protected:
    void afiseazaVirtual(std::ostream& os) const override;                //afisare virtuala suprascrisa
};

#endif

