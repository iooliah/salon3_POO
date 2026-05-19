#ifndef CATALOG_H
#define CATALOG_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <optional>
#include "Exceptii.h"                 //pt EntitateInexistentaExceptie<T>


template <typename T>
class Catalog{
private:
    std::vector<T> items;              //vector care retine toate obiectele din catalog, iar tipul elementelor depinde de T
                                       //atribut care depinde de T
    std::optional<T> ultimAdaugat;


public:
    Catalog() = default;                //constructor

    //functii membre care depind de T
    void adauga(const T& item){                                 //adauga un element nou in catalog
        items.push_back(item);
        ultimAdaugat = item;
    }
    size_t numar() const { return items.size(); }           //returneaza nr de elemente din catalog
    bool gol() const { return items.empty(); }              //verifica daca vectorul este gol


//am nevoie pt a putea face for(const auto& x : catalog)
//astfel, catalogul poate fi parcurs ca un vector normal
    auto begin(){
        return items.begin();
    }
    auto end(){
        return items.end();
    }

    auto begin() const{                 //variante const
        return items.begin();
    }
    auto end() const{
        return items.end();
    }

    const std::vector<T>& toate() const{ return items;}        //returneaza vectorul intern al catalogului
    const std::optional<T>& getUltimAdaugat() const{return ultimAdaugat; }

    //functii template
    //Predicat = functie/lambda care intoarce true sau false
    template <typename Predicat>
    T& cauta(Predicat p, const std::string& criteriu = ""){            //cauta un element care respecta o anumita conditie
        auto it = std::find_if(items.begin(), items.end(), p);
        if(it == items.end()) throw EntitateInexistentaExceptie<T>(criteriu);
        return *it;
    }
    template <typename Predicat>
    const T& cauta(Predicat p, const std::string& criteriu = "") const{         //varianta const
        auto it = std::find_if(items.begin(), items.end(), p);
        if(it == items.end()) throw EntitateInexistentaExceptie<T>(criteriu);
        return *it;
    }
    template <typename Predicat>
    std::vector<T> filtreaza(Predicat p) const{                                //returneaz aelementele care respecta o conditie
        std::vector<T> rez;
        std::copy_if(items.begin(), items.end(), std::back_inserter(rez), p);
        return rez;
    }
    template <typename Predicat>
    bool exista(Predicat p) const{                           //verifica daca exista macar un element care respecta conditia cu ajutorul lui any_of
        return std::any_of(items.begin(), items.end(), p);
    }

    //functie libera template - friend
    friend std::ostream& operator<<(std::ostream& os, const Catalog<T>& c){         //operator <<
        os<< "=== Catalog cu " << c.items.size() << " elemente ===\n";
        for(const auto& it : c.items){
            os<< it << "\n----\n";
        }
        return os;
    }
};



#endif // CATALOG_H

