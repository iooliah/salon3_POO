#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include "Client.h"
#include "Angajat.h"
#include "Programare.h"
#include "Manichiura.h"
#include "Pedichiura.h"
#include "Coafor.h"
#include "Cosmetica.h"
#include "Exceptii.h"

//declar functiile pe care o sa le folosesc
Client& cautaClient(std::vector<Client>& clienti, const std::string& nume, const std::string& prenume);
Angajat& cautaAngajat(std::vector<Angajat>& angajati, const std::string& nume, const std::string& prenume);
bool specializareBuna(const Angajat& angajat, const std::string& tipServiciu);
bool angajatDisponibil(const std::vector<Programare>& programari, const Angajat& angajat, const std::string& data, const std::string& ora);
plata plataFinal(const std::string& text);

float pretFix(const std::string& tipServiciu){                          //stabilesc pretul de baza al fiecarui serviciu
    if(tipServiciu == "MANICHIURA") return 100;
    if(tipServiciu == "PEDICHIURA") return 90;
    if(tipServiciu == "COAFOR") return 70;
    if(tipServiciu == "COSMETICA") return 90;
    return 0;
}
int durataFixa(const std::string& tipServiciu){                         //stabilesc durata de baza a fiecarui serviciu
    if(tipServiciu == "MANICHIURA") return 90;
    if(tipServiciu == "PEDICHIURA") return 70;
    if(tipServiciu == "COAFOR") return 40;
    if(tipServiciu == "COSMETICA") return 80;
    return 0;
}

void citesteClienti(std::vector<Client>& clienti, const std::string& fis){          //citesc clientii din fisier
    std::ifstream fin(fis);
    std::string nume, prenume, telefon;
    int nrVizite;

    while(fin >> nume >> prenume >> telefon >> nrVizite){
        clienti.emplace_back(nume, prenume, telefon, nrVizite);                 //creez direct un obiect Client in vector
    }
}

void citesteAngajati(std::vector<Angajat>& angajati, const std::string& fis){          //citesc angajatii din fisier
    std::ifstream fin(fis);
    std::string nume, prenume, telefon, specializare;
    int experienta;

    while(fin >> nume >> prenume >> telefon >> experienta >> specializare){
        angajati.emplace_back(nume, prenume, telefon, experienta, specializare);          //creez direct un obiect Angajat in vector
    }
}


void citesteProgramari(std::vector<Programare>& programari, std::vector<Client>& clienti, std::vector<Angajat>& angajati, const std::string& fis){
    std::ifstream fin(fis);
    std::string linie;

    while(std::getline(fin, linie)){            //cat pot citi o linie intreaga din fisier
        if(linie.empty()) continue;             //ignor liniile goale din fisier
        std::istringstream iss(linie);
        std::string numeClient, prenumeClient, numeAngajat, prenumeAngajat, tipServiciu, data, ora, plataText;

        if(!(iss >> numeClient >> prenumeClient >> numeAngajat >> prenumeAngajat >> tipServiciu >> data >> ora >> plataText)){
            continue;
        }try{                                       //pret si data fixate la inceput
            float pret = pretFix(tipServiciu);
            int durata = durataFixa(tipServiciu);

            Client& client = cautaClient(clienti, numeClient, prenumeClient);           //caut existenta clientului
            Angajat& angajat = cautaAngajat(angajati, numeAngajat, prenumeAngajat);     //caut exisdtenta angajatului

            if(specializareBuna(angajat, tipServiciu) == 0){                            //daca nu am ales specializarea corecta a angajatului
                throw ProgramareInvalidaExceptie("angajatul nu are specializarea potrivita"); //eroare
            }

            std::shared_ptr<Serviciu> serviciu;     //creez serviciul concret in functie de tipul citit
            //creez obiectul derivat corespunzator serviciului citit din fisier
            if(tipServiciu == "MANICHIURA"){
                bool gel, design, crema;
                iss>> gel >> design >> crema;             //citesc optiunile extra ale serviciului
                //creez obiect de tip Manichiura prin pointer la baza
                serviciu = std::make_shared<Manichiura>("Manichiura", pret, durata, gel, design, crema);
            }else if(tipServiciu == "PEDICHIURA"){
                bool gel, design, masaj;
                iss>> gel >> design >> masaj;             //citesc optiunile extra ale serviciului
                //creez obiect de tip Pedichiura prin pointer la baza
                serviciu = std::make_shared<Pedichiura>("Pedichiura", pret, durata, gel, design, masaj);
            }else if(tipServiciu == "COAFOR"){
                bool vopsit;
                std::string lungimePar;
                iss>> vopsit >> lungimePar;             //citesc optiunile extra ale serviciului
                //creez obiect de tip Coafor prin pointer la baza
                serviciu = std::make_shared<Coafor>(pret, durata, vopsit, lungimePar);
            }else if(tipServiciu == "COSMETICA"){
                bool masca;
                std::string tipTratament;
                iss>> masca >> tipTratament;             //citesc optiunile extra ale serviciului
                //creez obiect de tip Cosmetica prin pointer la baza
                serviciu = std::make_shared<Cosmetica>(pret, durata, masca, tipTratament);
            }else{
                throw ProgramareInvalidaExceptie("tip serviciu invalid");     //daca tipul serviciului nu exista, programare invalida
            }

            if(!angajatDisponibil(programari, angajat, data, ora)){         //verific daca angajatul este disponibil la data si ora cerute
                throw ProgramareInvalidaExceptie("angajat ocupat");
            }
            programari.emplace_back(client, angajat, serviciu, data, ora, plataFinal(plataText));          //creez direct un obiect Programare in vector
        }
        catch(const SalonExceptii& e){
            std::cout<< "Programare ignorata: " << e.what() << std::endl;
        }
    }
}
//caut un client dupa nume si prenume; daca nu exista, atunci exceptie
Client& cautaClient(std::vector<Client>& clienti, const std::string& nume, const std::string& prenume){
    for(auto& c : clienti){
        if(c.getNume() == nume && c.getPrenume() == prenume){
            return c;
        }
    }
    throw ClientInexistentExceptie();
}
//caut un angajat dupa nume si prenume; daca nu exista, atunci exceptie
Angajat& cautaAngajat(std::vector<Angajat>& angajati, const std::string& nume, const std::string& prenume){
    for(auto& a : angajati){
        if(a.getNume() == nume && a.getPrenume() == prenume)
            return a;
    }
    throw AngajatInexistentExceptie();
}
//verific daca angajatul are specializarea necesara serviciului ales
bool specializareBuna(const Angajat& angajat, const std::string& tipServiciu){
    if((tipServiciu == "MANICHIURA" || tipServiciu == "PEDICHIURA") && angajat.getSpecializare() == "unghii"){
        return true;
    }
    if(tipServiciu == "COAFOR" && angajat.getSpecializare() == "coafor"){
        return true;
    }
    if(tipServiciu == "COSMETICA" && angajat.getSpecializare() == "cosmetica"){
        return true;
    }
    return false;
}
//verifica daca angajatul este liber la aceeasi data si ora
bool angajatDisponibil(const std::vector<Programare>& programari, const Angajat& angajat, const std::string& data, const std::string& ora){
    for(const auto& p : programari){
        if(p.getData() == data && p.getOra() == ora && p.getAngajat().getNume() == angajat.getNume() && p.getAngajat().getPrenume() == angajat.getPrenume()){
            return false;
        }
    }
    return true;
}
//transforma textul citit din fisier/tastatura in enum-ul plata
plata plataFinal(const std::string& text){
    if(text == "CASH") return plata::CASH;
    if(text == "CARD") return plata::CARD;
    if(text == "TRANSFER") return plata::TRANSFER;
    throw ProgramareInvalidaExceptie("tip de plata invalid");
}


void adaugaClient(std::vector<Client>& clienti){
    std::string nume, prenume, telefon;
    int nrVizite;
    std::cout<< "Nume: ";                                           //adaug datele clientului nou
    std::cin>> nume;
    std::cout<< "Prenume: ";
    std::cin>> prenume;
    std::cout<< "Telefon: ";
    std::cin>> telefon;
    std::cout<< "Numar vizite: ";
    std::cin>> nrVizite;

    clienti.emplace_back(nume, prenume, telefon, nrVizite);        //creez un obiect de tip Client in vector

    std::ofstream fout("clienti.txt", std::ios_base::app);         //scriu in fisier noul client
    fout<< nume << " " << prenume << " " << telefon << " " << nrVizite <<std::endl;
    std::cout<< "Client adaugat.\n";
}

void adaugaProgramare(std::vector<Programare>& programari, std::vector<Client>& clienti, std::vector<Angajat>& angajati){
    std::string numeClient, prenumeClient;
    std::string numeAngajat, prenumeAngajat;
    std::string tipServiciu, data, ora, plataText;
    //adaug datele noii programari pt client,angajat,serviciu

    std::cout<< "Nume: ";
    std::cin>> numeClient;
    std::cout<< "Prenume: ";
    std::cin>> prenumeClient;
    Client& client =cautaClient(clienti, numeClient, prenumeClient);      //verific daca exista deja clientul

    std::cout<< "Nume angajat: ";
    std::cin>> numeAngajat;
    std::cout<< "Prenume angajat: ";
    std::cin>> prenumeAngajat;
    Angajat& angajat = cautaAngajat(angajati, numeAngajat, prenumeAngajat);      //verific existenta angajatului

    std::cout<< "Tip serviciu: ";
    std::cin>> tipServiciu;

    if(specializareBuna(angajat, tipServiciu)== 0){                              //verific daca angajatul ales are specializarea buna
        throw ProgramareInvalidaExceptie("angajatul nu are specializarea potrivita");
    }

    std::shared_ptr<Serviciu> serviciu;         //retin ce tip de serviciu s-a ales
    float pret = pretFix(tipServiciu);
    int durata = durataFixa(tipServiciu);

    //pt serviciul ales, se bifeaza optiunile extra
    if(tipServiciu == "MANICHIURA"){
        bool gel, design, crema;
        std::cout<< "Gel (0/1): ";
        std::cin>> gel;
        std::cout<< "Design (0/1): ";
        std::cin>> design;
        std::cout<< "Crema (0/1): ";
        std::cin>> crema;
        //creez obiect de tip Manichiura
        serviciu = std::make_shared<Manichiura>("Manichiura", pret, durata, gel, design, crema);
    }else if(tipServiciu == "PEDICHIURA"){
        bool gel, design, masaj;
        std::cout<< "Gel (0/1): ";
        std::cin>> gel;
        std::cout<< "Design (0/1): ";
        std::cin>> design;
        std::cout<< "Masaj (0/1): ";
        std::cin>> masaj;
        //creez obiect de tip Pedichiura
        serviciu = std::make_shared<Pedichiura>("Pedichiura", pret, durata, gel, design, masaj);
    }else if(tipServiciu == "COAFOR"){
        bool vopsit;
        std::string lungimePar;
        std::cout<< "Vopsit (0/1): ";
        std::cin>> vopsit;
        std::cout<< "Lungime par: ";
        std::cin>> lungimePar;
        //creez obiect de tip Coafor
        serviciu = std::make_shared<Coafor>(pret, durata, vopsit, lungimePar);
    }else if(tipServiciu == "COSMETICA"){
        bool masca;
        std::string tipTratament;
        std::cout<< "Masca (0/1): ";
        std::cin>> masca;
        std::cout<< "Tip tratament: ";
        std::cin>> tipTratament;
        //creez obiect de tip Cosmetica
        serviciu = std::make_shared<Cosmetica>(pret, durata, masca, tipTratament);
    }else{
        throw ProgramareInvalidaExceptie("tip serviciu invalid");
    }

    std::cout<< "Data: ";
    std::cin>> data;
    std::cout<< "Ora: ";
    std::cin>> ora;

    if(!angajatDisponibil(programari, angajat, data, ora)){  //verific daca angajatul e valabil atunci
        throw ProgramareInvalidaExceptie("angajat ocupat");
    }

    std::cout<< "Plata (CASH/CARD/TRANSFER): ";          //aleg metoda plata
    std::cin>> plataText;

    programari.emplace_back(client, angajat, serviciu, data, ora, plataFinal(plataText));          //creez un obiect de tip Programare in vector

    std::ofstream fout("programari.txt", std::ios_base::app);                       //adaug in fisier noua programare
    fout<<client.getNume()<< " " <<client.getPrenume()<< " " <<angajat.getNume()<< " " <<angajat.getPrenume()<< " " <<
    tipServiciu<< " " <<data<< " " <<ora<< " " << plataText<<std::endl;
    std::cout<<"Programare adaugata.\n";
}

int main()
{
    std::vector<Client> clienti;
    std::vector<Angajat> angajati;
    std::vector<Programare> programari;

    try{
        citesteClienti(clienti, "clienti.txt");
        citesteAngajati(angajati, "angajati.txt");
        citesteProgramari(programari, clienti, angajati, "programari.txt");

        int optiune;
        do{
            std::cout<< "\n======== SALON BRB ========\n";
            std::cout<< "1. Afiseaza clientii\n";
            std::cout<< "2. Afiseaza angajatii\n";
            std::cout<< "3. Afiseaza programarile\n";
            std::cout<< "4. Afiseaza costul fiecarei programari\n";
            std::cout<< "5. Calculeaza incasarile unei zile\n";
            std::cout<< "6. Calculeaza totalul platit de un client intr-o zi\n";
            std::cout<< "7. Adauga client nou\n";
            std::cout<< "8. Adauga programare noua\n";
            std::cout<< "9. Afiseaza programarile cu timp suplimentar\n";
            std::cout<< "10. Iesire\n";
            std::cout<< "Optiune (scrieti numarul optiunii dvs.): ";
            std::cin>>optiune;

            try{
                if(optiune == 1){                       //afisez clientii din fisiserul "clienti.txt"
                    for(const auto& c : clienti){
                        std::cout<< c <<std::endl;
                    }
                }else if(optiune == 2){                 //afisez angajatii din fisiserul "angajati.txt"
                    for(const auto& a : angajati){
                        std::cout<< a <<std::endl;
                    }
                }else if(optiune == 3){                 //afisez programarile din fisierul "programari.txt"
                    for(const auto& p : programari){
                        std::cout<< p <<std::endl;
                    }
                }else if(optiune == 4){
                    for(const auto& p : programari){
                        std::cout << p.descriereProgramare() <<std::endl;             //afisez fiecare programare cu descrierea completa
                        std::cout << "Cost final: " << p.calcCostFinal(programari) << " lei\n";      //afisez suma
                    }
                }else if(optiune == 5){
                    std::string data;
                    std::cout<< "Data: ";
                    std::cin>> data;                        //aleg data in care vreau sa vad cat s-a incasat
                    std::cout<<"Incasari in data " <<data<< ": "<< Programare::calcIncasariZi(programari, data)<<" lei\n";  //folosesc fct speciala
                }else if(optiune == 6){
                    std::string nume, prenume, data;
                    float total = 0;
                    //scriu numele, prenumele si data pentru a vedea cat a cheltuit respectivul client
                    std::cout<< "Nume client: ";
                    std::cin>>nume;
                    std::cout<< "Prenume client: ";
                    std::cin>>prenume;
                    std::cout<< "Data: ";
                    std::cin>>data;
                    Client& client = cautaClient(clienti, nume, prenume);   //verific daca exista clientul in fisier; de nu, afisez eroare

                    for(const auto& p : programari){                        //daca gasesc in programari data aleasa si numele exact al clientului cautat
                        if(p.getData() == data && p.getClient().getNume() == client.getNume() && p.getClient().getPrenume() == client.getPrenume()){
                            total += p.calcCostFinal(programari);           //calculez suma
                        }
                    }
                    std::cout<< "Suma plata: " << total <<" lei\n";
                }else if(optiune == 7){             //creez client nou
                    adaugaClient(clienti);
                }else if(optiune == 8){             //creez programare noua
                    adaugaProgramare(programari, clienti, angajati);
                }else if(optiune == 9){             //afisez ce servicii necesita timp suplimentar
                    for(const auto& p : programari){
                        if(p.areServiciuCuTimpSuplimentar()){
                            std::cout<< p.descriereProgramare()<<std::endl;
                        }
                    }
                }else if(optiune == 10){
                    std::cout<< "La revedere!\n";
                }else{
                    std::cout<< "Optiunea nu exista\n";                     //daca nu aleg optiune existenta
                }
            }
            catch(const SalonExceptii& e){                                  //exceptie
                std::cout<< "Eroare: " <<e.what()<<std::endl;
            }

        }while(optiune!=10);                                                //continui pana citesc optiunea 10, adica de iesire

        std::cout<< "\nTotal clienti: "<< Client::getNrClienti() <<std::endl;           //afisez numarul total de clienti si angajati, care creste daca creez ceva nou
        std::cout<< "Total angajati: "<< Angajat::getNrAngajati() <<std::endl;
    }
    catch(const SalonExceptii& e){
        std::cout<< "Eroare salon: " << e.what() <<std::endl;               //trateaza erorile specificate
    }
    catch(const std::exception& e){                                         //trateaza orice alta eroare standard
        std::cout<< "Eroare generala: " << e.what() <<std::endl;
    }
    return 0;
}
