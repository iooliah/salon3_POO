#ifndef UNGHII_H
#define UNGHII_H

#include "Serviciu.h"

class Unghii : public Serviciu{
protected:
    bool gel;                    //optiune extra (durata si pret)
    bool design;                 //optiune extra (durata si pret)
    float calcPretComun(bool angajatExperimentat, plata tipPlata, bool clientFidel) const;    //functie pt calculul pretului comun la mani+pedi (ca sa nu fie repetitiv)

public:
    Unghii() = default;                                                                       //constructor
    Unghii(const std::string& nume, float pret, int durata, bool gel, bool design);

    //getters const
    bool getGel() const;
    bool getDesign() const;

    //functii virtuale suprascrise
    int durataTotala() const override;
    float calcPretFinal(bool angajatExperimentat, plata tipPlata, bool clientFidel) const override;
    std::string descriereServiciu() const override;

    std::shared_ptr<Serviciu> clone() const override;                                           //clonare polimorfica prin pointer la baza

protected:
    void afiseazaVirtual(std::ostream& os) const override;                                      //afisare virtuala suprascrisa
};


#endif
