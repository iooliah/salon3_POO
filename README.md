## Tema aleasa: Salon de infrumusetare

## Descriere
Salonul ofera patru tipuri de servicii: manichiura, pedichiura, coafor si cosmetica. Fiecare programare leaga un client de un angajat si un serviciu, la o anumita data si ora, fiind platita prin numerar, card sau transfer.

Am creat o lista de clienti (fiecare cu nume, prenume, telefon, numar de vizite), o lista de angajati (cu nume, prenume, telefon, ani de experienta, specializare) si o lista de programari, citite din fisiere text. Pentru fiecare serviciu exista un pret si o durata fixa, modificate prin optiuni extra: vopsit/lungime par la coafor, tip tratament/masca la cosmetica, gel/design + crema la manichiura, gel/design + masaj la pedichiura.

Ce am creat: validarea fiecarei programari(clientul si angajatul exista, angajatul are specializarea potrivita, nu e suprapusa programarea). Se poate calcula pentru fiecare programare pretul final, tinand cont de experienta angajatului, fidelitatea clientului (>=5 vizite), tipul platii (cash => reducere 10%) si orarul zilei. Se poate afisa: lista clientilor, a angajatilor, a programarilor, costul fiecarei programari, incasarile unei zile, suma platita de un client intr-o zi, si programarile care necesita timp suplimentar (servicii cu optiuni adaugate).

## Structura. Ierarhii de mostenire:
* Persoana (clasa de baza proprie, abstracta) -> Client, Angajat
* Serviciu (clasa de baza proprie, abstracta) -> Coafor, Cosmetica, Unghii -> Manichiura, Pedichiura
* Programare

Functii virtuale pure specifice temei (in Serviciu):
* calcPretFinal(angajatExperimentat, tipPlata, clientFidel) - calcul pret dupa anumite optiuni care pot micsora/mari suma finala
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


## Ce am adaugat in proiectul 3: templates si design patterns

Clase template adaugate:
* EntitateInexistentaExceptie<T> (in Exceptii.h) - transformarea unei clase existente, izolata. A inlocuit ClientInexistentExceptie si AngajatInexistentExceptie care erau aproape identice. Clasa retine criteriul cautat prin atributul std::string criteriu_, iar mesajul exceptiei este construit in functie de tipul T, folosind functia libera template numeEntitate<T>(), specializata pentru Client, Angajat si Programare. Numele vechi sunt pastrate prin alias cu "using".
* Catalog<T> (in Catalog.h) - container pentru clienti/angajati/programari.  Inlocuieste folosirea directa a mai multor std::vector din main. Are atribute dependente de T: std::vector<T> items si std::optional<T> ultimAdaugat. Metoda adauga(const T& item) adauga un element si actualizeaza ultimul element adaugat. Metodele template cauta, filtreaza si exista folosesc predicate/lambda pentru cautare si filtrare. Clasa are si operator<< definit ca functie friend pentru afisarea intregului catalog.

Design patterns folosite:
* Singleton: SalonSingleton - configurarile salonului (preturi, durate, data aniversara)
* Factory: ServiciuFactory - creeaza serviciul concret pe baza tipului(creeazaDinFisier si creeazaInteractiv)
* Builder: ProgramareBuilder - construieste obiectul Programare prin chaining, cu validare in build()

## Review

### Tema

Tema aleasa pentru acest proiect a fost simularea unui salon de infrumusetare. Un salon din viata reala are servicii de manichiura, pedichiura, coafor si cosmetica, fiecare cu pret si durata, dar fiecare avand si optiuni extra care modifica pretul si timpul necesar, existand o ierarhie clara intre tipurile de servicii, care au proprietati comune, dar si particulare. Fiecare programare realizata in proiectul meu leaga un client de un angajat si un serviciu, la o anumita data si ora, cu un anumit tip de plata. Programul citeste datele initiale din fisiere text, permite cautari, calcule si adaugarea interactiva de clienti noi si programari noi, salvand modificarile inapoi in fisiere.

### Proiectul 1

In proiectul 1 am pornit cu o solutie de baza: clasele Client, Angajat, Serviciu si Programare erau independente, fara nicio relatie de mostenire intre ele. Sirurile de caractere erau gestionate manual prin char* cu alocare dinamica, ceea ce a insemnat ca a trebuit sa scriu constructorii de copiere, operatorul de atribuire si destructorul pentru fiecare clasa care avea atribute char*. Stocarea datelor am facut-o in vectori statici de dimensiune fixa, precum Programare programari[100], ceea ce limita aplicatia si crea risc posibil de overflow.

Operatiile de baza in proiectul 1 erau cautarea clientilor existenti, realizarea unei programari, afisarea angajatilor disponibili pentru un serviciu si calculul incasarilor dintr-o zi. Validarile erau facute prin verificari simple de string cu strcmp, iar erorile erau semnalate prin mesaje afisate in terminal, fara tratarea exceptiilor.

Prima parte a proiectului a fost un exercitiu bun pentru baza programarii orientate pe obiecte, intrucat necesita cod repetitiv pentru gestionarea memoriei, lipsa de flexibilitate, si imposibilitatea de a trata erorile mai usor.

### Proiectul 2 (mostenire, polimorfism si exceptii)

In proiectul 2 am facut mai multe schimbari mai complexe. Prima a fost trecerea de la char* la std::string, ceea ce a eliminat aproape integral codul de gestionare manuala a memoriei. Constructorii de copiere si operatorii de atribuire au devenit mai putin importanti sau au putut fi inlocuiti cu cei generati automat de compilator.

A doua transformare a fost introducerea ierarhiilor de mostenire. Am creat clasa abstracta Persoana ca baza pentru Client si Angajat si clasa abstracta Serviciu ca baza pentru serviciile din salon: Serviciu este baza, Coafor, Cosmetica si Unghii sunt derivate directe, iar Manichiura si Pedichiura sunt derivate din Unghii. Manichiura si pedichiura sunt amandoua servicii de unghii, deci impart proprietati comune.

Polimorfismul a fost o alta schimbare. In clasa Programare, atributul serviciu este de tip std::shared_ptr<Serviciu>, ceea ce permite stocarea oricarei derivate prin pointer la baza. Apelurile precum serviciu->calcPretFinal() sau serviciu->durataTotala() sunt apeluri virtuale care selecteaza automat implementarea corecta in functie de tipul concret. Pentru afisare, am folosit interfata non-virtuala (NVI): metoda publica afiseaza() este non-virtuala si apeleaza metoda virtuala protected afiseazaVirtual() suprascrisa in derivate. 

dynamic_pointer_cast a fost folosit cu un scop concret: metoda areServiciuCuTimpSuplimentar() din Programare verifica daca serviciul ales are optiuni extra(vopsit, gel, masaj etc.) prin downcast la fiecare derivata. Daca o derivata are activata vreo optiune care necesita timp suplimentar fata de durata de baza, metoda intoarce true.

In sfarsit, am construit o ierarhie proprie de exceptii: SalonExceptii este clasa de baza care foloseste std::runtime_error, iar ClientInexistentExceptie, AngajatInexistentExceptie si ProgramareInvalidaExceptie sunt derivate care trateaza categorii distincte de erori si, de asmenea, am schimbat meniul interactiv.

### Proiectul 3 (templates si design patterns)

Proiectul 3 a presupus mai multe schimbari ale codului, nu doar adaugari. Cerintele principale: minimum o clasa template, minimum o functie template, modificarea unei clase existente intr-o clasa template, si minimum doua design patterns folosite cu sens.

Pentru partea de template, am ales sa transform clasele de exceptii ClientInexistentExceptie si AngajatInexistentExceptie intr-o singura clasa template, EntitateInexistentaExceptie<T>. Aceasta a fost cea mai potrivita clasa pentru transformare, pentru ca era izolata,fiind folosita doar in throw si catch, fara dependente complexe de restul codului. Cele doua clase originale erau extrem de asemanatoare, doar mesajele erau putin diferite ("Client inexistent" si "Angajat inexistent"). Am pastrat numele vechi ca alias (using ClientInexistentExceptie = EntitateInexistentaExceptie<Client>) ca sa nu fiu nevoita sa modific in fiecare loc unde se aruncau aceste exceptii.
Clasa template are o functie libera template numeEntitate<T>() cu diverse mesaje particulare pentru Client, Angajat si Programare. Specializarile sunt cele care personalizeaza mesajul exceptiei in functie de tipul cautat: pentru Client mesajul devine "Nu exista client:...", pentru Angajat "Nu exista angajat:....".

A doua clasa template este Catalog<T>. Aceasta inlocuieste folosirea directa a std::vector<Client>, std::vector<Angajat> si std::vector<Programare> din main. Catalog<T> are un atribut std::vector<T> items si metode template membru pentru cautare si filtrare cu lambda ca predicat. Operatorul << este definit ca friend in interiorul clasei, ceea ce inseamna ca fiecare instantiere de Catalog<T> are propria versiune generata de compilator.

Pentru design patterns, am implementat trei exemple:

SalonSingleton este un Singleton de tip Meyers care contine configurarile globale ale salonului: preturile de baza pentru fiecare serviciu, duratele de baza, data aniversara, reducerile aplicate in caz de programari multiple. Acest Singleton inlocuieste functiile libere pretFix() si durataFixa() care erau in main si aduce intr-un singur loc datele proiectului.

ServiciuFactory este un Factory care inlocuieste codul de if/else pentru crearea serviciilor concrete. In proiectul 2, aceeeasi bucata de cod cu 4 ramuri (Manichiura/Pedichiura/Coafor/Cosmetica) aparea de doua ori in main: o data la citirea programarilor din fisier si o data la adaugarea interactiva de la tastatura. ServiciuFactory creeaza doua metode statice (creeazaDinFisier, creeazaInteractiv) care inlocuiesc repetivitatea. De exemplu, daca in viitor voi adauga un serviciu nou, modific doar Factory-ul si adaug clasa derivata, nu si main-ul (principiul Open/Closed din SOLID).

ProgramareBuilder permite constructia unei Programari prin method chaining: builder.client(c).angajat(a).serviciu(s).data(d).ora(o).tipPlata(p).build(). Avantajele sunt ca argumentele sunt etichetate clar si nu mai trebuie sa retin pozitia exacta a fiecaruia in constructorul cu 6 parametri si ca validarea se face intr-un singur loc, in build(), care arunca ProgramareInvalidaExceptie daca lipseste vreun camp. Builder-ul foloseste std::optional pentru a sti daca un camp a fost setat sau nu.

In main.cpp am inlocuit: std::vector<...> cu Catalog<...>, functiile libere cautaClient si cautaAngajat cu Catalog::cauta(lambda, criteriu) care cere un predicat lambda si arunca direct EntitateInexistentaExceptie<T> daca nu gaseste, functiile pretFix si durataFixa cu apeluri prin Singleton-ul SalonSingleton, blocul de if/else pentru servicii cu un singur apel Factory, si programari.emplace_back() prin Builder. In plus, am adaugat catch-uri specializate pentru EntitateInexistentaExceptie<Client> si EntitateInexistentaExceptie<Angajat> in main, ca sa se vada vizibil ca exceptia template este folosita activ in aplicatie.



## Bibliografie

-Curs si laborator POO 
-https://github.com/mcmarius/poo 
-https://codesignal.com/learn/courses/fundamentals-of-text-data-manipulation-in-cpp/lessons/writing-text-files-in-cpp (pentru a invata cum sa fac update din program fisierelor 'txt')
-https://www.geeksforgeeks.org/cpp/stringstream-c-applications/   (pentru a putea rezolva o eroare ce tinea de citirea programarilor)
-https://refactoring.guru/design-patterns                (design patterns)
-https://en.cppreference.com/w/cpp/utility/optional      (pentru std::optional)
-https://www.geeksforgeeks.org/cpp/templates-cpp/        (pentru templates)

