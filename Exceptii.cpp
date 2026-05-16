#include "Exceptii.h"

SalonExceptii::SalonExceptii(const std::string& mesaj) : std::runtime_error(mesaj){}

ProgramareInvalidaExceptie::ProgramareInvalidaExceptie(const std::string& mesaj): SalonExceptii(mesaj){}
