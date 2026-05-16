#ifndef PROGRAMARE_H
#define PROGRAMARE_H
#include <vector>
#include "Client.h"
#include "Angajat.h"
#include "Serviciu.h"

class Programare{
private:
    Client client;
    Angajat angajat;

    //pointer la clasa de baza cu derivate; permite apel virtual prin pointer de baza
    std::shared_ptr<Serviciu> serviciu;

    std::string data;    //data programarii
    std::string ora;     //ora programarii
    plata tipPlata;      //modul de plata

    static bool esteAcelasiClient(const Client& c1, const Client& c2);         //functie statica

public:
    Programare() = default;             //constructor
    Programare(const Client& client, const Angajat& angajat, std::shared_ptr<Serviciu> serviciu, const std::string& data, const std::string& ora, plata tipPlata);

    //copy and swap
    Programare(const Programare& other);                 //constructor de copiere
    Programare& operator=(Programare other);             //operator= implementat prin copy and swap
    friend void swap(Programare& a, Programare& b);      //fct friend folosita de copy and swap
    ~Programare() = default;                             //destructor implicit

    //getters
    const Client& getClient() const;
    const Angajat& getAngajat() const;
    const std::string& getData() const;
    const std::string& getOra() const;

    int getDurataTotala() const;
    bool areServiciuCuTimpSuplimentar() const;             //pentru dynamic_pointer_cast
    std::string descriereProgramare() const;               //descrierea completa a programarii

    //calcul cu apel virtual prin pointer de baza
    float calcCostFinal(const std::vector<Programare>& toateProgramarile) const;

    //functie statica pentru numararea programarilor unui client intr-o zi si functie statica pentru calculul incasarilor dintr-o zi
    static int numaraProgramariClientZi(const std::vector<Programare>& programari, const Client& client, const std::string& data);
    static float calcIncasariZi(const std::vector<Programare>& programari, const std::string& data);

    friend std::ostream& operator<<(std::ostream& os, const Programare& p);         //supraincarcare operator <<
};


#endif // PROGRAMARE_H
