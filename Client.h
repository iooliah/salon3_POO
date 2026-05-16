#ifndef CLIENT_H
#define CLIENT_H

#include "Persoana.h"

class Client : public Persoana{
private:
    int nrVizite;
    static int numarClienti;                                        //pt numararea clientilor
    void afiseazaVirtual(std::ostream& os) const override;          //afisare virtuala suprascrisa in clasa derivata

public:
    Client();                                                       //constructor
    Client(const std::string& nume, const std::string& prenume, const std::string& telefon, int nrVizite = 0);
    Client(const Client& other);                                    //constructor copiere
    ~Client() override;                                             //destructor virtual suprascris din Persoana

    bool esteClientFidel() const;                                   //functie care verifica vizitele unui client; >=5 => reducere 10%
    static int getNrClienti();

    std::string getRol() const override;                            //functie virtuala suprascrisa din Persoana
    std::shared_ptr<Persoana> clone() const override;               //clonare polimorfica prin pointer la baza
};






#endif // CLIENT_H
