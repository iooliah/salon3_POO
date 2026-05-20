#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include "Client.h"
#include "Angajat.h"
#include "Programare.h"
#include "Exceptii.h"
#include "Catalog.h"                       //clasa template generica pt stocare
#include "SalonSingleton.h"                //singleton pentru configurari salon
#include "ServiciuFactory.h"               //factory pentru servicii
#include "ProgramareBuilder.h"             //builder pentru programari

//declararea functiilor
bool specializareBuna(const Angajat& angajat, const std::string& tipServiciu);
bool angajatDisponibil(const Catalog<Programare>& programari, const Angajat& angajat, const std::string& data, const std::string& ora);
plata plataFinal(const std::string& text);

//citire clienti din fisier in catalog
void citesteClienti(Catalog<Client>& clienti, const std::string& fis){
    std::ifstream fin(fis);
    std::string nume, prenume, telefon;
    int nrVizite;

    while(fin >> nume >> prenume >> telefon >> nrVizite){
        clienti.adauga(Client(nume, prenume, telefon, nrVizite));
    }
}

//citire angajati din fisier in catalog
void citesteAngajati(Catalog<Angajat>& angajati, const std::string& fis){
    std::ifstream fin(fis);
    std::string nume, prenume, telefon, specializare;
    int experienta;

    while(fin >> nume >> prenume >> telefon >> experienta >> specializare){
        angajati.adauga(Angajat(nume, prenume, telefon, experienta, specializare));
    }
}

//citire programari din fisier
void citesteProgramari(Catalog<Programare>& programari, Catalog<Client>& clienti, Catalog<Angajat>& angajati, const std::string& fis){
    std::ifstream fin(fis);
    std::string linie;

    while(std::getline(fin, linie)){
        if(linie.empty()) continue;
        std::istringstream iss(linie);
        std::string numeClient, prenumeClient, numeAngajat, prenumeAngajat;
        std::string tipServiciu, data, ora, plataText;

        if(!(iss>> numeClient >> prenumeClient >> numeAngajat >> prenumeAngajat >> tipServiciu >> data >> ora >> plataText)){
            continue;
        }
        try{
            //inlocuieste cautaClient/cautaAngajat din salon2
            Client& client = clienti.cauta([&](const Client& c){
                return c.getNume() == numeClient && c.getPrenume() == prenumeClient;
            }, numeClient + " " + prenumeClient);

            Angajat& angajat = angajati.cauta([&](const Angajat& a){
                return a.getNume() == numeAngajat && a.getPrenume() == prenumeAngajat;
            }, numeAngajat + " " + prenumeAngajat);

            if(!specializareBuna(angajat, tipServiciu)){
                throw ProgramareInvalidaExceptie("angajatul nu are specializarea potrivita");
            }


            auto serviciu = ServiciuFactory::creeazaDinFisier(tipServiciu, iss);   //factory

            if(!angajatDisponibil(programari, angajat, data, ora)){
                throw ProgramareInvalidaExceptie("angajat ocupat");
            }

            //chaining in loc de constructor cu 6 parametri
            ProgramareBuilder b;                                            //builder
            auto prog = b.client(client).angajat(angajat).serviciu(serviciu).data(data).ora(ora).tipPlata(plataFinal(plataText)).build();
            programari.adauga(prog);
        }
        catch(const SalonExceptii& e){
            std::cout<< "Programare ignorata: " << e.what() <<std::endl;
        }
    }
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

//verific daca angajatul este liber la aceeasi data si ora prin Catalog::exista
bool angajatDisponibil(const Catalog<Programare>& programari, const Angajat& angajat, const std::string& data, const std::string& ora){
    return !programari.exista([&](const Programare& p){
        return p.getData() == data && p.getOra() == ora && p.getAngajat().getNume() == angajat.getNume() && p.getAngajat().getPrenume() == angajat.getPrenume();
    });
}

//transform textul citit in enum
plata plataFinal(const std::string& text){
    if(text == "CASH") return plata::CASH;
    if(text == "CARD") return plata::CARD;
    if(text == "TRANSFER") return plata::TRANSFER;
    throw ProgramareInvalidaExceptie("tip de plata invalid");
}

void adaugaClient(Catalog<Client>& clienti){
    std::string nume, prenume, telefon;
    int nrVizite;
    std::cout<< "Nume: ";
    std::cin>> nume;
    std::cout<< "Prenume: ";
    std::cin>> prenume;
    std::cout<< "Telefon: ";
    std::cin>> telefon;
    std::cout<< "Numar vizite: ";
    std::cin>> nrVizite;

    clienti.adauga(Client(nume, prenume, telefon, nrVizite));

    std::ofstream fout("clienti.txt", std::ios_base::app);
    fout<< nume << " " << prenume << " " << telefon << " " << nrVizite <<std::endl;
    std::cout<< "Client adaugat.\n";
}

void adaugaProgramare(Catalog<Programare>& programari, Catalog<Client>& clienti, Catalog<Angajat>& angajati){
    std::string numeClient, prenumeClient;
    std::string numeAngajat, prenumeAngajat;
    std::string tipServiciu, data, ora, plataText;

    std::cout<< "Nume: ";
    std::cin>> numeClient;
    std::cout<< "Prenume: ";
    std::cin>> prenumeClient;
    Client& client = clienti.cauta([&](const Client& c){
        return c.getNume() == numeClient && c.getPrenume() == prenumeClient;
    }, numeClient + " " + prenumeClient);

    std::cout<< "Nume angajat: ";
    std::cin>> numeAngajat;
    std::cout<< "Prenume angajat: ";
    std::cin>> prenumeAngajat;
    Angajat& angajat = angajati.cauta([&](const Angajat& a){
        return a.getNume() == numeAngajat && a.getPrenume() == prenumeAngajat;
    }, numeAngajat + " " + prenumeAngajat);

    std::cout<< "Tip serviciu (MANICHIURA/PEDICHIURA/COAFOR/COSMETICA): ";
    std::cin>> tipServiciu;

    if(!specializareBuna(angajat, tipServiciu)){
        throw ProgramareInvalidaExceptie("angajatul nu are specializarea potrivita");
    }

    auto serviciu = ServiciuFactory::creeazaInteractiv(tipServiciu);        //factory interactiv

    std::cout<< "Data: ";
    std::cin>> data;
    std::cout<< "Ora: ";
    std::cin>> ora;
    if(!angajatDisponibil(programari, angajat, data, ora)){
        throw ProgramareInvalidaExceptie("angajat ocupat");
    }

    std::cout<< "Plata (CASH/CARD/TRANSFER): ";
    std::cin>> plataText;

    ProgramareBuilder b;                                                      //builder pentru constructia programarii
    auto prog = b.client(client).angajat(angajat).serviciu(serviciu).data(data).ora(ora).tipPlata(plataFinal(plataText)).build();
    programari.adauga(prog);

    std::ofstream fout("programari.txt", std::ios_base::app);
    fout<< numeClient << " " << prenumeClient << " " << numeAngajat << " " << prenumeAngajat << " " << tipServiciu << " " << data << " " << ora << " " << plataText << std::endl;
    std::cout<<"Programare adaugata.\n";
}

int main()
{
    //CATALOG<T> inlocuieste std::vector<Client>, std::vector<Angajat>, std::vector<Programare> din salon2
    Catalog<Client> clienti;
    Catalog<Angajat> angajati;
    Catalog<Programare> programari;

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
                if(optiune == 1){
                    //operator<< din Catalog<Client> afiseaza intregul catalog
                    std::cout<< clienti;
                }else if(optiune == 2){
                    std::cout<< angajati;
                }else if(optiune == 3){
                    std::cout<< programari;
                }else if(optiune == 4){
                    for(const auto& p : programari){
                        std::cout<< p.descriereProgramare() <<std::endl;
                        std::cout<< "Cost final: " << p.calcCostFinal(programari.toate()) << " lei\n";
                    }
                }else if(optiune == 5){
                    std::string data;
                    std::cout<< "Data: ";
                    std::cin>> data;
                    std::cout<< "Incasari in data " <<data<< ": " << Programare::calcIncasariZi(programari.toate(), data) <<" lei\n";
                }else if(optiune == 6){
                    std::string nume, prenume, data;
                    float total = 0;
                    std::cout<< "Nume client: ";
                    std::cin>>nume;
                    std::cout<< "Prenume client: ";
                    std::cin>>prenume;
                    std::cout<< "Data: ";
                    std::cin>>data;

                    Client& client = clienti.cauta([&](const Client& c){
                        return c.getNume() == nume && c.getPrenume() == prenume;
                    }, nume + " " + prenume);

                    //gasesc doar programarile pt clientul si data data
                    auto progClient = programari.filtreaza([&](const Programare& p){
                        return p.getData() == data && p.getClient().getNume() == client.getNume() && p.getClient().getPrenume() == client.getPrenume();
                    });
                    for(const auto& p : progClient){
                        total += p.calcCostFinal(programari.toate());
                    }
                    std::cout<< "Suma plata: " << total <<" lei\n";
                }else if(optiune == 7){
                    adaugaClient(clienti);
                }else if(optiune == 8){
                    adaugaProgramare(programari, clienti, angajati);
                }else if(optiune == 9){
                    //arat doar programarile cu timp suplimentar
                    auto extra = programari.filtreaza([](const Programare& p){
                        return p.areServiciuCuTimpSuplimentar();
                    });
                    for(const auto& p : extra){
                        std::cout<< p.descriereProgramare() <<std::endl;
                    }
                }else if(optiune == 10){
                    std::cout<< "La revedere!\n";
                }else{
                    std::cout<< "Optiunea nu exista\n";
                }
            }
            catch(const EntitateInexistentaExceptie<Client>& e){
                std::cout<< "Eroare client: " <<e.what()<< " (criteriu cautat: '" <<e.getCriteriu()<< "')" <<std::endl;
            }
            catch(const EntitateInexistentaExceptie<Angajat>& e){
                std::cout<< "Eroare angajat: " <<e.what()<< " (criteriu cautat: '" <<e.getCriteriu()<< "')" <<std::endl;
            }
            catch(const SalonExceptii& e){
                std::cout<< "Eroare: " <<e.what()<<std::endl;
            }
        }while(optiune!=10);
        std::cout<< "\nTotal clienti: "<< Client::getNrClienti() <<std::endl;
        std::cout<< "Total angajati: "<< Angajat::getNrAngajati() <<std::endl;

        if(clienti.ultimul()){
            std::cout<< "\nUltimul client:\n";
            std::cout<< *clienti.ultimul() <<std::endl;
        }
        if(programari.ultimul()){
            std::cout<< "\nUltima programare:\n";
            std::cout<< *programari.ultimul() <<std::endl;
        }

    }
    catch(const SalonExceptii& e){
        std::cout<< "Eroare salon: " << e.what() <<std::endl;
    }
    catch(const std::exception& e){
        std::cout<< "Eroare generala: " << e.what() <<std::endl;
    }
    return 0;
}

