#ifndef COAFOR_H
#define COAFOR_H

#include "Serviciu.h"

class Coafor : public Serviciu{
private:
    bool vopsit;                                                                    //optiune extra
    std::string lungimePar;                                                         //"scurt", "mediu", "lung"
    void afiseazaVirtual(std::ostream& os) const override;                          //afisare virtuala suprascrisa

public:
    Coafor() = default;                                                             //constructor
    Coafor(float pret, int durata, bool vopsit, const std::string& lungimePar);     //constructor cu parametri

    bool getVopsit() const;      //getter

    //functii virtuale suprascrise
    int durataTotala() const override;
    float calcPretFinal(bool angajatExperimentat, plata tipPlata, bool clientFidel) const override;
    std::string descriereServiciu() const override;
    std::shared_ptr<Serviciu> clone() const override;                                               //clonare polimorfica prin pointer la baza

};

#endif
