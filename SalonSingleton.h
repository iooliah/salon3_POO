#ifndef SALONSINGLETON_H
#define SALONSINGLETON_H
#include <string>

//SINGLETON: exista un singur set de configurari ale salonului in toata aplicatia

class SalonSingleton{
private:
    SalonSingleton() = default;
    std::string dataAniversara_ = "11.09";
    float reducereAniversara_ = 0.9f;
    float reducereProgramariMultiple_ = 0.9f;
    int pragProgramariMultiple_ = 2;

public:
    static SalonSingleton& getInstance();       //singura instanta a clasei

    //dezactivez copierea si atribuirea ca sa nu se poata duplica singletonul
    SalonSingleton(const SalonSingleton&) = delete;
    SalonSingleton& operator=(const SalonSingleton&) = delete;

    //inlocuiesc functiile  pretFix()/durataFixa() din main
    float pretFix(const std::string& tipServiciu) const;
    int durataFixa(const std::string& tipServiciu) const;

    //adaug data aniversara si si reducerea aplicata pt mai multe programari in aceeasi zi (>=2)
    const std::string& dataAniversara() const;
    float reducereAniversara() const;
    float reducereProgramariMultiple() const;
    int pragProgramariMultiple() const;
};





#endif //SALONSINGLETON_H

