#ifndef COSMETICA_H
#define COSMETICA_H

#include "Serviciu.h"

class Cosmetica : public Serviciu {
private:
    bool masca;                                                             //optiune extra
    std::string tipTratament;                                               //"facial", "corp", "par"
    void afiseazaVirtual(std::ostream& os) const override;                  //afisare virtuala suprascrisa

public:
    Cosmetica() = default;                                                            //constructor
    Cosmetica(float pret, int durata, bool masca, const std::string& tipTratament);   //constructor cu parametri

    //functii virtuale suprascrise
    int durataTotala() const override;
    float calcPretFinal(bool angajatExperimentat, plata tipPlata, bool clientFidel) const override;
    std::string descriereServiciu() const override;

    std::shared_ptr<Serviciu> clone() const override;                                  //clonare polimorfica prin pointer la baza
};

#endif

