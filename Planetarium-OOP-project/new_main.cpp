#include <iostream>
#include <vector>
#include <cstring>

//----------------(info)----------------//
// First year of college                 |
// OOP used concepts: -Encapsulation     |
// Classes: -Planet                      |
//          -Satellite                   |
//          -PlanetSys                   |
//          -Star                        |
//          -System                      |
//--------------------------------------//

class Planet{

private:

    char* m_Name;
    int m_Diameter;
    long long m_S_P; //m_S_P represents the Sun to Planet distance

public:

    Planet()
    {
        m_Name = new char[(strlen("PRIME") + 1)];
        strcpy(m_Name, "PRIME");
        this -> m_Diameter = -100;
        this -> m_S_P = -100;
    }

    Planet(const char* n, int d, long long sp)
    {
        m_Name = new char[strlen(n) + 1];
        strcpy(m_Name, n);
        this -> m_Diameter = d;
        this -> m_S_P = sp;
    }

    const char* getName() const{ return m_Name; }
    int getDiameter() const { return m_Diameter; }
    long long getSP() const { return m_S_P; }

    void Stats() const
    {
        std::cout<<"Planet name: "<<getName()<<std::endl;
        std::cout<<"Planet diameter: "<<getDiameter()<<std::endl;
        std::cout<<"The distance between this planet and the m_star that is orbitating is: "<<getSP()<<" km"<<std::endl;
    }

};

class Satellite{

private:

    char* m_Name;
    int m_Diameter;
    int m_P_S;

public:

    Satellite()
    {
        m_Name = new char[strlen("BETA") + 1];
        strcpy(m_Name, "BETA");

    }

    Satellite(const char* n, int d, int ps)
    {
        m_Name = new char[strlen(n) + 1];
        strcpy(m_Name, n);
        this -> m_Diameter = d;
        this -> m_P_S = ps;
    }

    const char* getName() const { return m_Name; }
    int getDiameter() const { return m_Diameter; }
    int getPS() const { return m_P_S; }

    void Stats() const
    {
        std::cout<<"Satellite m_Name: "<<getName()<<std::endl;
        std::cout<<"Satellite m_Diameter: "<<getDiameter()<<std::endl;
        std::cout<<"The distance between this satellite and the planet that is orbitating is: "<<getPS()<<" km"<<std::endl;
    }

};

//----------------(PlanetSys)----------------//
// Name:           PlanetSys                  |
// Description:    This class represents the  |
// system created by a planet and the         |
// satellites that oribit it.                 |
//-------------------------------------------//
class PlanetSys{

private:

    Planet* m_oPlanet;
    std::vector<Satellite*> m_satellites;
    static bool m_Center;
    static bool m_exist;
    static Planet* m_CenterPlanet;

public:

    PlanetSys(Planet* P) : m_oPlanet(P)
    {
        if(m_exist)
        {
            throw std::logic_error("Such a planetary system already exists or is in creation.");
        }
        m_exist = true;
        m_CenterPlanet =  P;
        m_Center = true;
    }

    void addSatellite(Satellite* sat)
    {
        if(!m_Center)
        {
            throw std::logic_error("An central planet hasn't been added yet.");
        }

        m_satellites.push_back(sat);
    }

//    const Planet* getCentralPlanet() const
//    {
//        return m_oPlanet;
//    }

    std::vector<Satellite*> getSatellites() const
    {
        return m_satellites;
    }

    void printPlanetSys() const
    {
        std::cout << "The Central Planet is: " << m_oPlanet ->getName() << std::endl;
        for(auto sat : m_satellites)
            std::cout<<"Satellite name: "<<sat -> getName()<<std::endl;
    }

};

bool PlanetSys::m_Center = false;
bool PlanetSys::m_exist = false;
Planet* PlanetSys::m_CenterPlanet = nullptr;


class Star{

private:
    char* m_Name;
    long long m_life_span;
    int m_Diameter;

public:

    Star() : m_Diameter(-100), m_life_span(0)
    {
        m_Name = new char[strlen("Sparky") + 1];
        strcpy(m_Name, "Sparky");
    }

    Star(const char* n, int d, long long ls) : m_Diameter(d), m_life_span(ls)
    {
        m_Name = new char[strlen(n) + 1];
        strcpy(m_Name, n);
    }

    const char* getName() const { return m_Name; }
    int getDiameter() const { return m_Diameter; }
    long long getLS() const { return m_life_span;}

    void printStar() const
    {
        std::cout<<"The name of the m_star: "<<getName()<<std::endl;
        std::cout<<"The diameter of the m_star is: "<<getDiameter()<<std::endl;
        std::cout<<"The life span of this m_star is: "<<getLS()<<std::endl;
    }
};

//------------------(System)------------------//
// Name:             System                    |
// Description:    This class represents the   |
// system created by a Star and the            |
// planet systems that orbit it.               |
//--------------------------------------------//
class System{

private:
    char* m_Name;
    Star* m_star;
    std::vector<PlanetSys*> m_Sys;
    static bool m_Center;
    static bool m_exist;
    static Star* m_CentralStar;

public:
    System(const char* n, Star* s) : m_star(s)
    {
        if(m_exist)
        {
            throw std::logic_error("Such a stellar system already exists or is in creation.");
        }
        m_Name = new char[strlen(n) + 1];
        strcpy(m_Name, n);

        m_exist = true;
        m_CentralStar = s;
        m_Center = true;

    }

    void addStarSys(PlanetSys* s)
    {
        if(!m_Center)
        {
            throw std::logic_error("A central m_star hasn't been added yet.");
        }

        m_Sys.push_back(s);
    }

    void printStarSys()
    {
        std::cout<<this->m_Name;
        for(auto s : m_Sys)
            std::cout<<"X"; ///will need to add a getter for a PlanetSys object
    }


};

bool System::m_exist = false;
bool System::m_Center = false;
Star* System::m_CentralStar = nullptr;

int main() {

    Planet* P1 = new Planet("EARTH", 5000, 15000000);

    PlanetSys* sys = new PlanetSys(P1);

    Satellite* S1 = new Satellite("MOON", 1000, 13223);
    Satellite* S2 = new Satellite("TITAN", 1230, 23223);

    sys->addSatellite(S1);
    sys->addSatellite(S2);

    sys->printPlanetSys();

    Star* Star1 = new Star("SUN", 100, 45);

    System* Sys = new System("SOLARSYSTEM", Star1);

    Sys ->addStarSys(sys);

    Sys -> printStarSys();

    return 0;
}
