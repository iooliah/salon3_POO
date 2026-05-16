#ifndef MANICHIURA_H
#define MANICHIURA_H

#include "Unghii.h"

class Manichiura : public Unghii{
protected:
    bool crema;        //optiune extra

public:
    Manichiura() = default;                                                                         //constructor
    Manichiura(const std::string& nume, float pret, int durata, bool gel, bool design, bool crema);

    bool getCrema() const;
    //functii virtuale suprascrise
    int durataTotala() const override;
    float calcPretFinal(bool angajatExperimentat, plata tipPlata, bool clientFidel) const override;
    std::string descriereServiciu() const override;

    std::shared_ptr<Serviciu> clone() const override;                     //clonare polimorfica prin pointer la baza

private:
    void afiseazaVirtual(std::ostream& os) const override;                //afisare virtuala suprascrisa
};

#endif
