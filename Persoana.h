#ifndef PERSOANA_H
#define PERSOANA_H
#include <string>
#include <iostream>
#include <memory>

class Persoana {
protected:
    std::string nume;
    std::string prenume;
    std::string telefon;

public:
    Persoana() = default;                                                                                 //constructor
    Persoana(const std::string& nume, const std::string& prenume, const std::string& telefon);            //constructor cu parametri
    virtual ~Persoana() = default;                                                                        //destructor virtual

    //getters
    const std::string& getNume() const;
    const std::string& getPrenume() const;
    const std::string& getTelefon() const;
    std::string getNumeComplet() const;

    //interfata non-virtuala
    void afiseaza(std::ostream& os) const;

    virtual std::string getRol() const = 0;                                                                 //functie virtuala pura
    virtual std::shared_ptr<Persoana> clone() const = 0;                                                    //copiere polimorfica prin pointer de baza

    friend std::ostream& operator<<(std::ostream& os, const Persoana& p);                                   //operator <<

protected:
    virtual void afiseazaVirtual(std::ostream& os) const;                                                 //functie virtuala apelata din interfata non-virtuala
};

#endif // PERSOANA_H
