## Tema aleasa: Salon de infrumusetare

## Scurta descriere
Salonul ofera patru tipuri de servicii: manichiura, pedichiura, coafor si cosmetica. Fiecare programare leaga un client de un angajat si un serviciu, la o anumita data si ora, fiind platita prin numerar, card sau transfer.

Am creat o lista de clienti (fiecare cu nume, prenume, telefon, numar de vizite), o lista de angajati (cu nume, prenume, telefon, ani de experienta, specializare) si o lista de programari, toate citite din fisiere text. Pentru fiecare serviciu exista un pret si o durata fixa, modificate prin optiuni extra: vopsit/lungime par la coafor, tip tratament/masca la cosmetica, gel/design + crema la manichiura, gel/design + masaj la pedichiura.

Ce am realizat: sa se valideze fiecare programare (clientul si angajatul exista, angajatul are specializarea potrivita, nu e suprapus pe alt slot). Sa se calculeze pentru fiecare programare pretul final, tinand cont de experienta angajatului, fidelitatea clientului (>=5 vizite), tipul platii (cash => reducere) si orarul zilei. Sa se afiseze: lista clientilor, a angajatilor, a programarilor, costul fiecarei programari, incasarile unei zile, suma platita de un client intr-o zi, si programarile care necesita timp suplimentar (servicii cu optiuni adaugate).


## Structura. Ierarhii de mostenire:

* Persoana (clasa de baza proprie, abstracta) -> Client, Angajat
* Serviciu (clasa de baza proprie, abstracta) -> Coafor, Cosmetica, Unghii -> Manichiura, Pedichiura
* Programare


Functii virtuale pure specifice temei (in Serviciu):
* calcPretFinal(angajatExperimentat, tipPlata, clientFidel) - calcul pret cu modificatori
* durataTotala() - durata reala incluzand optiunile extra
* descriereServiciu() - descriere
* clone() - pentru copiere prin pointer de baza

Afisare cu interfata non-virtuala: metoda publica afiseaza() apeleaza metoda virtuala protected afiseazaVirtual(), suprascrisa in derivate.

Atribut pointer la baza + apel virtual prin acesta: clasa Programare contine std::shared_ptr<Serviciu> serviciu si apeleaza serviciu->calcPretFinal(...), serviciu->durataTotala(), serviciu->descriereServiciu() - apel virtual prin pointer de baza.

Copy-and-swap: Programare are constructor de copiere (care cloneaza serviciul prin clone()), operator= care primeste prin valoare si apeleaza swap, plus functia prietena swap.

std::dynamic_pointer_cast cu sens: Programare::areServiciuCuTimpSuplimentar() face downcast de la shared_ptr<Serviciu> la fiecare derivata, ca sa verifice optiunile specifice(vopsit, gel, masaj etc).

Exceptii - ierarhie proprie: SalonExceptii cu trei specializari distincte: ClientInexistentExceptie, AngajatInexistentExceptie, ProgramareInvalidaExceptie.

Date si functii statice: Client::numarClienti si Angajat::numarAngajati, Programare::calcIncasariZi, Programare::numaraProgramariClientZi, Programare::esteAcelasiClient.

operator<<: definit ca friend in Persoana, Serviciu si Programare. In Persoana/Serviciu apeleaza interfata non-virtuala.

Citire date din fisiere: clienti.txt, angajati.txt, programari.txt. 

Const: toate metodele care nu modifica starea sunt const (getters, calcule, afisare).


## Bibliografie

-Curs si laborator POO 
-https://codesignal.com/learn/courses/fundamentals-of-text-data-manipulation-in-cpp/lessons/writing-text-files-in-cpp (pentru a invata cum sa fac update din program fisierelor 'txt')
-https://www.geeksforgeeks.org/cpp/stringstream-c-applications/   (pentru a putea rezolva o eroare ce tinea de citirea programarilor)
