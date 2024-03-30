#include <iostream>
#include <cstring>
#include <vector>


///-----------CLASS(1)_PLANETS-----------///

class Sat;

class Planet {

private:

    ///----VARIABILE (int, bool, char, char*, double) ----////

    char* name;
    float Diametru;
    static const float PI;
    bool Habitabila;
    double LifeSpan;//Perioada de viata a planetei
    double S_P;//Distanta de la planeta la stea
    float ROT;//viteza de rotatie
    //int* BigTimeStamps;

public:

    ///--- CONSTRUCTORUL fara parametrii ---///

    Planet()
    {
        std::cout<<"PRANK THEM JHON :D"<<std::endl;
    }

    ///--- CONSTRUCTOR cu un parametru---///

    Planet(const char* n)
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);

    }

    Planet(float ROT) : ROT(ROT){};


    ///--- CONSTRUCTORI cu parametrii ---///


    Planet(float R, float rot)
    {
        (*this).Diametru = R;
        std::cout<< "Viteza de rotatie in radiani per secunda este de: "<< rot/R;
        std::cout<<std::endl;
        std::cout<< "Factorul de conversie pentru km/h este de 3.6 iar pentru MACH este de 0.003018.";
    }//daca apelezi Planet cu constructorul asta iti returneaza viteza in rad/s

    Planet(float R, float rot, double factor)
    {
        (*this).Diametru = R;
        (*this).ROT = rot;
        std::cout<< "Viteza de rotatie este de: "<< ((rot/R)*R)*factor;
        if(factor == 3.6) std::cout<< " km/h.";
        if(factor == 0.003018) std::cout<< " MACH.";
    }//daca apelezi Planet cu constructorul asta iti returneaza viteza in functie de factor


    ///--- CONSTRUCTORUL cu toti parametrii ---///

    Planet(const char* n, float diametru, bool habitabila, double lifespan, double s_p, float rot)
    {
        name = new char[strlen(n) + 1];
        strcpy(name, n);

        this->Diametru = diametru;
        this->Habitabila = habitabila;
        (*this).LifeSpan = lifespan;
        this->S_P = s_p;
        this->ROT = rot;

    }

    ///--- CONSTRUCTORUL DE  COPIERE ---///

    Planet(const Planet& pother) :
            name(pother.name),
            Diametru(pother.Diametru),
            Habitabila(pother.Habitabila),
            LifeSpan(pother.LifeSpan),
            S_P(pother.S_P),
            ROT(pother.ROT)
    {
        name = new char[strlen(pother.name) + 1];
        strcpy(name, pother.name);
    }


    ///--- GETTERI ---///
    char* getName() const { return name;}
    float getDiametru() const { return Diametru;}
    bool getHabitabila() const {return Habitabila;}
    double getLifeSpan() const {return LifeSpan;}
    double getS_P() const {return S_P;}
    float getRot() const {return ROT;}

    ///--- DESTRUCTOR ---///
    ~Planet()
    {
        if(name == nullptr)
            delete[] name;
    }

    ///--- SETTERI ---//

    void SetName(const char* nameP)
    {
        if(name != nullptr)
        {
            delete[] name;
        }
        int L = strlen(nameP);
        name = new char[L + 1];
        strcpy(name, nameP);
    }

    void SetDiametru(float diaP)
    {
        Diametru = diaP;
    }

    void SetHabitabila(bool life)
    {
        Habitabila = life;
    }

    void SetLifeSpan(double LS)
    {
        LifeSpan = LS;
    }

    void SetS_P(double S_P)
    {
        this -> S_P = S_P;
    }

    void SetRot (float ROT)
    {
        (*this).ROT = ROT;
    }

    ///--- FUNCTIE PRINT ---////

    void printPlanet() const
    {
        std::cout << "Statusurile planetei: " << std::endl;
        std::cout << "~ Nume: " << getName() << std::endl;
        std::cout << "~ Diametru: " << getDiametru() << std::endl;
        std::cout << "~ Capabila sa sustina viata:  " << getHabitabila() << std::endl;
        std::cout << "~ Durata asteptata de viata a planetei: " << getLifeSpan() << std::endl;
        std::cout << "~ Distanta de la planeta la steua pe care o orbiteaza: " << getS_P() << std::endl;
        std::cout << "~ Viteza de rotatie in jurul propiei axe: " << getRot() << std::endl;

    }


    ///---- Supraincarcare (-) ----///
    //calculeaza distanta dintre doua planete astfel:
    // verifica care e mai departe de soare
    //returneaza difrenta dintre ele
    double operator - (const Planet& other) const
    {
        if(S_P >= other.S_P)
            return S_P - other.S_P;
        else
            return other.S_P - S_P;
    }

    ///--- Supraincarcare (/) ---///
    //Diametru relativ(elseul e optional)
    float operator / (const Planet& other) const
    {
        if(Diametru >= other.Diametru)
            return Diametru / other.Diametru;
        else
            return other.Diametru / Diametru;
    }

    ///--- Supraincarcare (>) ---///
    //verifica care are zilele mai lungi
    bool operator > (const Planet& other) const
    {
        if(ROT > other.ROT)
            return true;
        else
            return false;
    }

    ///--- Supraincarcare (==) ---//
    //verifica daca doua planete sunt "echivalent"
    //Sunt echivalente daca au valorile din if egale intre ele
    bool operator == (const Planet& other) const
    {
        if(Diametru == other.Diametru && Habitabila == other.Habitabila && LifeSpan == other.LifeSpan)
            return true;
        else
            return false;
    }

    ///--- Supraincarcare (=) ---//

    Planet& operator = (const Planet& pother)
    {
        if(this != &pother)
        {
            if(this -> name != nullptr)
            {
                delete[] name;
                (*this).name = nullptr;
            }
            this -> name = new char[strlen(pother.name) + 1];
            strcpy(name , pother.name);
            Diametru  = pother.Diametru;
            Habitabila = pother.Habitabila;
            LifeSpan = pother.LifeSpan;
            S_P = pother.S_P;
            ROT = pother.ROT;
        }

        return *this;
    }

    ///--- FRIENDS ---///
    friend std::ostream& operator <<(std::ostream& out, const Planet& obj);
    friend std::istream& operator >>(std::istream& in, Planet& obj);

    friend Planet operator+(const Planet& L, const Planet& R);
    friend Planet operator+(const Planet& L, const Sat& R);
    friend Sat operator + (const Sat& L, const Planet& R);
};

std::istream& operator >>(std::istream& in, Planet& planet)
{

    std::cout<< "Introduceti nume pentru planeta: " << std::endl;
    char* name = new char[100];
    in >> name;
    planet.name = name;
    std::cout<< "Intoduceti Diametru: "<<std::endl;
    in >> planet.Diametru;
    std::cout<< "Intoduceti Habitabilitatea: "<<std::endl;
    in >> planet.Habitabila;
    std::cout<< "Intoduceti Durata de viata asteptata: "<<std::endl;
    in >> planet.LifeSpan;
    std::cout<< "Intoduceti distanta de la planeta la steau centrala: "<<std::endl;
    in >> planet.S_P;
    std::cout<< "Intoduceti viteza de rotatie a planetei: "<<std::endl;
    in >> planet.ROT;

    return in;
}

///--- Supraincarcare (<<) ---///
std::ostream& operator <<(std::ostream& out, const Planet& obj){

    out<<"Statusurile planetei: "<<std::endl;
    out<<"  -Nume: " << obj.name <<std::endl;
    out<<"  -Diametru: "<<obj.Diametru<<" km"<<std::endl;
    out<<"  -Habitabila: "<<obj.Habitabila<<std::endl;
    out<<"  -Durata asteptata de viata: "<<obj.LifeSpan<<" miliarde de ani"<<std::endl;
    out<<"  -Distanta de la planeta la steau centrala: " << obj.S_P <<std::endl;
    out<<"  -Viteza de rotatie a planetei: " << obj.ROT <<std::endl;

    return out;
}

///---- PI -----///
const float Planet::PI = 3.141592;

///----------CLASA(2)_STELE----------///



class Star {
private:
    std::string nameS;
public:

    ///--- CONSTRUCTOR cu un parametru ---///
    Star(const std::string& n) : nameS(n) {}
    std::string getName() const { return nameS; }
    void setName(const char* name) {this -> nameS = name;};
};



///----------CLASA(3)_SISTEME----------///



class System {

private:

    ///---- VARIABILE (static) ----///
    char* NameSys;
    Star* star;
    std::vector<Planet*> planets; //vector de pointeri la variabile de tip Planet
    static bool Center;
    //asta e folosita pentru a verifica daca o stea deja
    //si ca sa nu permitem adaugarea a mai multor stele in acelasi sistem
    static bool exist; // asta verific tine cont daca un sistem a fost creat
    static Star* centerStar; //un pointer specific pt obiectul stea cand devine "centerStar"

public:

    ///CONSTRUTCOR cu doi parametrii ---///
    System(char* nume, Star* s) :  star(s), NameSys(nume)
    {
        if(exist)
        {
            throw std::logic_error("Deja exista un sistem in procesul de creare.");
        }
        exist = true;
        centerStar = s;
        Center = true;
    }

    ///--- COPY CONSTRUCTOR ---///
    System(const System& other) :
            NameSys(other.NameSys),
            star(new Star(*(other.star))),
            planets() {
        NameSys = new char[strlen(other.NameSys + 1)];
        strcpy(NameSys,  other.NameSys);
        for (auto planet : other.planets) {
            planets.push_back(new Planet(*planet));
        }
    }


    System& operator=(const System& other) {
        if (this != &other) {
            delete star;
            for (auto planet : planets) {
                delete planet;
            }
            NameSys = other.NameSys;
            star = new Star(*(other.star));
            planets.clear();
            for (auto planet : other.planets) {
                planets.push_back(new Planet(*planet));
            }
        }
        return *this;
    }

    const char* getNameSys() const {
        return NameSys;
    }


    ///--- DESTRUCTOR ---///
    ~System() {
        if(NameSys == nullptr)///???///
            delete[] NameSys;
        delete star;
        for (auto planet  : planets) {
            delete planet;
        }
    }

    void addPlanet(Planet* planet) {

        if(!Center)
        {
            throw std::logic_error("O stea centrala nu a fost inca adaugata sistemului.");
        }
        planets.push_back(planet);
    }

    void removePlanet(int index) {
        if (index >= 0 && index < planets.size()) {
            delete planets[index];
            planets.erase(planets.begin() + index);
        }
    }

    void replaceStar(Star* newStar) {
        delete star;
        star = newStar;
    }



    ///--- FUNCTIE PRINT ---///
    void printSystem() {
        std::cout << " Sistemul planetar: "<< getNameSys() << std::endl;
        std::cout << " Star: " << star->getName() << std::endl;
        std::cout << " Planets: " << std::endl;
        for (auto planet : planets) {
            std::cout << " - Nume: " << planet -> getName() << std::endl;
            std::cout<< " Informatii despre planeta: "<<std::endl;
            std::cout<< " - Diametry: "<<planet -> getDiametru() << " km." << std::endl;
            std::cout<< " - Habitabila: "<<planet -> getHabitabila() << std::endl;
            std::cout<< " - Lifa-Span:  "<<planet -> getLifeSpan() << std::endl;
            std::cout<< " - Distanta de la planetala steaua centrala: "<<planet -> getS_P() << std::endl;
            std::cout<< " - Viteza de rotatie: "<<planet -> getRot() << std::endl;
        }
    }

    ///---SUPRAINCARCARE (+) ENABLE + operations for class objects ---///(FRIEND)
    friend System operator + (const System& sother, const Planet& pother);


};

bool System::Center = false;
bool System::exist = false;
Star* System::centerStar = nullptr;

/////---SUPRAINCARCARE (+) ENABLE + operations for class objects ---///
//System operator + (const System& sother, const Planet& pother) //tre sa folosesc pointeri pt planete
//{
//    System newSystem = sother;
//    Planet *newPlanet = new Planet(pother);
//    newSystem.addPlanet(newPlanet);
//    return newSystem;
//}



///----------CLASA(4)_SATELITI----------///

class Sat {

private:
    char* name;
    float G;
    int ImpLVL = 0 ;

public:;
    // float G;
    Sat(char* Nume)
    {
        this->name = Nume;
        std::cout<<"MOON TYPE";
    }

    Sat(float G) : G(G) {}
    float getG() const { return G; }

    Sat( char* Nume, float G)
    {
        std::cout<<"MOON TYPE G";
    }

    ///--- COPY CONSTRUCTORUL ---///
    Sat(const Sat& sother) :
            name(sother.name),
            G(sother.G),
            ImpLVL(sother.ImpLVL)
    {
        name = new char[strlen(sother.name) + 1];
        strcpy(name, sother.name);
    }


    Sat& operator = (const Sat& sother) {
        if (this != &sother) {
            if (this->name != nullptr) {
                delete[] name;
                (*this).name = nullptr;
            }
            this->name = new char[strlen(sother.name) + 1];
            strcpy(name, sother.name);
            G = sother.G;
            ImpLVL = sother.ImpLVL;
        }
    }

    ///--- DESTRUCTOR ---///
    ~Sat()
    {
        if(name == nullptr)
            delete name;
    }

    operator int() const {
        return static_cast<int>(G);
    }

    Sat& operator++();
    Sat operator++(int);

    friend std::ostream& operator<<(std::ostream& os, const Sat& sat);
    friend std::istream& operator>>(std::istream& is, Sat& sat);

    bool operator == (const Sat& satother) const;

    friend Sat operator+(const Sat& obj1, const Sat& obj2);


    Sat operator * (const int& value) const;


    friend Sat operator + (const Sat& L, const Sat& R);
    friend Planet operator + (const Planet& L, const Sat& R);
    friend Sat operator + (const Sat& L, const Planet& R);


};

///--- Supraincarcare (++post) ---///

Sat& Sat::operator++()
{
    ++ImpLVL;
    return *this;
}

///--- Supraincarcare (++pre) ---///

Sat Sat::operator++(int)
{
    Sat aux(*this);
    this->ImpLVL++;
    return aux;
}

///--- Supraincarcare (<<) ---///

std::ostream& operator <<(std::ostream& os, const Sat& sat )
{
    os << "Name: " << sat.name << ", G: " << sat.G << ", ImpLVL: " << sat.ImpLVL;
    return os;
}

///--- Supraincarcare (>>) ---///

std::istream& operator >>(std::istream& is, Sat& sat)
{
    std::cout<< "Introduceti nume pentru satelit: " << std::endl;
    char* name = new char[100];
    is >> name;
    sat.name = name;
    std::cout<< "Intoduceti G: ";
    is >> sat.G;

    return is;
}

///--- Supraincarcare (==) ---///

bool Sat::operator==(const Sat& other) const {
    return this->G == other.G;
}

///--- Supraincarcare (+) ---///


///--- Supraincarcare (*) ---///
Sat Sat::operator*(const int& value) const {
    Sat result(*this);
    result.G *= value;
    return result;
}

///------ Cerinta 9 ------///
Planet operator + (const Planet& L, const Planet& R) {
    return Planet(L.ROT + R.ROT);
}

Planet operator + (const Planet& L, const Sat& R) {
    return Planet(L.ROT + R.G);
}

Sat operator + (const Sat& L, const Sat& R) {
    return Sat(L.G + R.G);
}

Sat operator + (const Sat& L, const Planet& R) {
    return Sat(L.G + R.ROT);
}
///----------MAIN----------///



int main() {

    ///--- Nu are Meniu interactiv ---///

//    Planet P(2);
//    Sat Sac(3);
//    Planet R1 = P + Sac + P + P + Sac;
//    Sat R2 = Sac + P + Sac;
//
//    std::cout << R1.getRot() << std::endl;
//    std::cout << R2.getG() << std::endl;

//    Sat sat("MOOn", 12.3);
//
//    std::cout<<sat;
//    Sat sut("titan");
//    std::cin>> sut;
//    std::cout<<sut;
//    Sat ee = sat++;
//    std::cout<<std::endl;

//    Planet P1;
//    std::cin>>P1;
//    std::cout<<P1;


//    Planet P(10, 2.3, 0.003018);
//    Planet P1("EARTH", 5000, true, 10, 2.3, 100);
//    Planet P2 = P1;
//    Planet P3;
//    P3 = P1;
//    P1.printPlanet();
//    P2.printPlanet();
//    P3.printPlanet();

//    Star* star1 = new Star("Sun");
//
//    System *system1 = new System("Solar System", star1);
//
//    Planet *P1 = new Planet("Mercury", 10, false, 3.2, 1.122, 150);
//    Planet *P2 = new Planet("Venus", 15, true, 5.5, 2.33, 100);
//
//
//
//    system1 -> addPlanet(P1);
//    system1 -> addPlanet(P2);
//    system1->printSystem();
//
//    System* system2 = system1;
//
//    system1 -> addPlanet(new Planet("Mars", 6779.0f, false, 50000, 687.0f, 10));
//
//    std::cout << "System 1:" << std::endl;
//    system1 -> printSystem();
//    std::cout << std::endl;
//
//    std::cout << "System 2:" << std::endl;
//    system2 -> printSystem();
//    std::cout << std::endl;

//
//    Star *sun = new Star("Sun");
//
//    System *solarSystem = new System("Sistemul Solar", sun);
//    Planet *P1 = new Planet("Mercury", 10, false, 3.2, 1.122, 150);
//    Planet *P2 = new Planet("Venus", 15, true, 5.5, 2.33, 100);
//    Planet *P3 = new Planet("Earth", 20, true, 2.2, 2.2112, 30);
//    Planet *P4 = new Planet("Mars", 40, false , 2.9, 7.33, 500);
//
//
//
//    solarSystem->addPlanet(P1);
//    solarSystem->addPlanet(P2);
//    solarSystem->addPlanet(P3);
//    solarSystem->addPlanet(P4);
//    solarSystem->printSystem();
//    solarSystem->removePlanet(2);
//    solarSystem->printSystem();
//
//    Star *alphaCentauri = new Star("Alpha Centauri");
//    solarSystem->replaceStar(alphaCentauri);
//    solarSystem->printSystem();
//
//    delete solarSystem;

//    std::cout<<P7<<std::endl;
//    std::cout<<P5 - P6<<std::endl; //calculeaza distanta dintre doua planete;
//    std::cout<<P5/P6;
//    std::cout<<std::endl;
//
//    if(P5 > P6)
//        std::cout<<"Zielele sunt mai scurte pe ";//<<P5.getName()<<" decat pe "<<P6.getName()<<std::endl;
//    else
//        std::cout<<"INVERS";
//
//    if(P5 == P6)
//        std::cout<<"echi";
//    else
//        std::cout<<"NU";

    return 0;
}

/// ·͙*̩̩͙˚̩̥̩̥*̩̩̥͙　✩　*̩̩̥͙˚̩̥̩̥*̩̩͙‧͙ ˚*•̩̩͙✩•̩̩͙*˚＊ /// :D
