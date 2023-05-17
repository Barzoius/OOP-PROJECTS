#include <iostream>
#include <fstream>
#include <cstring>
#include <cxxabi.h>
#include <limits>

///-------------------------------(ENUMS)-------------------------------///
enum class Water_Species {Squirtle, Blastoise, Seel, Horsea, Vaporeon};
enum class Fire_Species { Charmander, Magmar, Tepig, Litten, Raboot};
enum class Steel_Species { Klink, Klang, Meltan, Melmetal};
enum class Electric_Species { Pikachu,  Raichu,  Manectric, Electivire};
///---------------------------------------------------------------------///

template <class P>
struct ITF{
    virtual std::ostream& print(std::ostream&) const = 0;
    virtual std::istream& read(std::istream&) = 0;
};

class POKEMON : public virtual ITF<POKEMON>{

private:
    char* Name;
    int HP;
    float WEIGHT;
    float CP;

public:

    POKEMON(char* N, int HP, float W, float CP) : HP(HP), WEIGHT(W), CP(CP)
    {
        Name = new char[strlen(N) + 1];
        strcpy(Name, N);
    }

    virtual ~POKEMON()
    {
        if(Name == nullptr)
            delete[] Name;
    }

    POKEMON(const POKEMON& P) : HP(P.HP), WEIGHT(P.WEIGHT), CP(P.CP) {
        Name = new char[strlen(P.Name) + 1];
        strcpy(Name, P.Name);
    }

    char* getName() const { return Name; }

    void SETCP(float cp){ CP = cp; };

    float getCP() const {
        return CP;
    }

    const char* getType() const{

        int status;
        char* demangledName = abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, &status);
        if(status == 0){
            const char* typeName = demangledName;
            return typeName;
        }else{
            return typeid(*this).name();
        }
    }

    std::ostream& print(std::ostream&) const override;
    std::istream& read(std::istream&) override;

    friend std::ostream& operator << (std::ostream& out, const POKEMON& P);
    friend std::istream& operator >> (std::istream& in, POKEMON& P);

};

std::ostream& POKEMON::print(std::ostream& out) const {

    out<<"Name: " << this->Name << std::endl;
    out<<"STATS: " << std::endl;
    out<<"-HP = " << this->HP << std::endl;
    out<<"-WEIGHT = " << this->WEIGHT << std::endl;
    out<<"-CP = " << this ->CP << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out, const POKEMON& P){
    return P.print(out);
}

std::istream& POKEMON::read(std::istream& in){
    std::cout<<"Remember, a pokemon is a real friend so chose an appropriate name!"<<std::endl;
    std::cout<<"Chose a name: "<<std::endl;
    in >> this -> Name;
    std::cout<<"Insert the Hit Points(HP): "<<std::endl;
    in >> this -> HP;
    std::cout<<"Insert the weight of the pokemon: "<<std::endl;
    in >> this -> WEIGHT;
    std::cout<<"Insert the Combat Power(CP) of your pokemon: " << std::endl;
    in >> this -> CP;

    return in;
}

std::istream& operator >> (std::istream& in, POKEMON& P){
    return P.read(in);
}

///-------------------------------------------(WATER)-------------------------------------------///

class WATER_TYPE : virtual public POKEMON{

private:

    Water_Species WS;

public:
    WATER_TYPE(char* N, int HP, float W, float CP, Water_Species Wt) : POKEMON(N, HP, W, CP), WS(Wt)
    { std::cout<<"WATHA."<<std::endl;}

    WATER_TYPE(const WATER_TYPE& W) : POKEMON(W), WS(W.WS){}

    virtual ~WATER_TYPE()
    {
        if(POKEMON::getName() == nullptr)
        {
            delete[] getName();
        }
    }

    Water_Species getSpecies() const {
        return WS;
    };

    void operator + (WATER_TYPE& other)  {

        if(this -> WS == other.WS) {
            float W1 = this->getCP();
            float AddedCP = other.getCP() + W1;
            if (AddedCP >= 1500) {
                this->SETCP(1500);
                other.SETCP(AddedCP - 1500);
            } else {
                this->SETCP(AddedCP);
                other.SETCP(0);
            }
        } else std::cout<<"IUCANT"<<std::endl;
    }

    static std::string WaterSpeciesToString(Water_Species species) {
    switch (species) {
        case Water_Species::Squirtle:
            return "Squirtle";
        case Water_Species::Blastoise:
            return "Blastoise";
        case Water_Species::Seel:
            return "Seel";
        case Water_Species::Horsea:
            return "Horsea";
        case Water_Species::Vaporeon:
            return "Vaporeon";
        default:
            return "Unknown";
    }
}


    std::istream& read(std::istream& in) override;
    std::ostream& print(std::ostream& out) const override;

    friend std::istream& operator >> (std::istream& in, WATER_TYPE& W);
    friend std::ostream& operator << (std::ostream& out, const WATER_TYPE& W);

};

std::istream& WATER_TYPE::read(std::istream &in) {

    POKEMON::read(in);
    bool valid_input = false;
    std::string input;

    while(!valid_input){
        std::cout<<"Insert the species: " <<std::endl;
        in >> input;

        if(input == "Squirtle"){
            WS = Water_Species::Squirtle;
            valid_input = true;
        }
        else if(input == "Blastoise"){
            WS = Water_Species::Blastoise;
            valid_input = true;
        }
        else if(input == "Seel"){
            WS = Water_Species::Seel;
            valid_input = true;
        }
        else if(input == "Horsea"){
            WS = Water_Species::Horsea;
            valid_input = true;
        }
        else if(input == "Vaporeon"){
            WS = Water_Species::Vaporeon;
            valid_input = true;
        }
        else
            std::cerr
                    << "Invalid input. Please try a valid water species"
                    << std::endl
                    <<"Please insert a valid information for this field: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return in;
}

std::istream& operator >> (std::istream& in, WATER_TYPE& W){
    return W.read(in);
}

std::ostream& WATER_TYPE::print(std::ostream &out) const {
    POKEMON::print(out);
    out<<"Species: ";
    switch (WATER_TYPE::WS) {
        case Water_Species::Squirtle:
            out << "Squirtle";
            break;
        case Water_Species::Blastoise:
            out << "Blastoise";
            break;
        case Water_Species::Seel:
            out << "Seel";
            break;
        case Water_Species::Horsea:
            out << "Horsea";
            break;
        case Water_Species::Vaporeon:
            out << "Vaporeon";
            break;
    }
    out<<std::endl;

    return out;
}

std::ostream& operator << (std::ostream& out, const WATER_TYPE& W){
    return W.print(out);
}

///-------------------------------------------(STEEL)-------------------------------------------///

class STEEL_TYPE : virtual public POKEMON{
private:

    //const char* Weakness = "Fire_Type";
    Steel_Species SS;

public:
    STEEL_TYPE(char* N, int HP, float W, float CP, Steel_Species ss) : POKEMON(N, HP, W, CP), SS(ss){std::cout<<"STEEL."<<std::endl;}

    STEEL_TYPE(const STEEL_TYPE& S) : POKEMON(S), SS(S.SS){}

    virtual ~STEEL_TYPE()
    {
        if(POKEMON::getName() == nullptr)
        {
            delete[] getName();
        }
    }

   static std::string SteelSpeciesToString(Steel_Species species) {
    switch (species) {
        case Steel_Species::Klink:
            return "Klink";
        case Steel_Species::Klang:
            return "Klang";
        case Steel_Species::Meltan:
            return "Meltan";
        case Steel_Species::Melmetal:
            return "Melmetal";
        default:
            return "Unknown";
    }
}

    std::istream& read(std::istream& in) override;
    std::ostream& print(std::ostream& out) const override;

    friend std::istream& operator >> (std::istream& in, STEEL_TYPE& S);
    friend std::ostream& operator << (std::ostream& out, const STEEL_TYPE& S);

};

std::istream& STEEL_TYPE::read(std::istream &in) {
    POKEMON::read(in);
    bool valid_input = false;
    std::string input;

    while(!valid_input){
        std::cout<<"Insert the species: " <<std::endl;
        in >> input;

        if(input == "Klink"){
            SS = Steel_Species::Klink;
            valid_input = true;
        }
        else if(input == "Klang"){
            SS = Steel_Species::Klang;
            valid_input = true;
        }
        else if(input == "Meltan"){
            SS = Steel_Species::Meltan;
            valid_input = true;
        }
        else if(input == "Melmetal"){
            SS = Steel_Species::Melmetal;
            valid_input = true;
        }
        else
            std::cerr
                << "Invalid input. Please try a valid steel species"
                << std::endl
                <<"Please insert a valid information for this field: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return in;
}

std::istream& operator >> (std::istream& in, STEEL_TYPE& S){
    return S.read(in);
}

std::ostream& STEEL_TYPE::print(std::ostream &out) const {
    POKEMON::print(out);
    out<<"Species: ";
    switch (STEEL_TYPE::SS) {
        case Steel_Species::Klink:
            out << "Klink";
            break;
        case Steel_Species::Klang:
            out << "Klang";
            break;
        case Steel_Species::Meltan:
            out << "Meltan";
            break;
        case Steel_Species::Melmetal:
            out << "Melmetal";
            break;
    }
    out<<std::endl;

    return out;
}

std::ostream& operator << (std::ostream& out, const STEEL_TYPE& S){
    return S.print(out);
}

///-------------------------------------------(WATER_STEEL)-------------------------------------------///

class WATER_STEEL_TYPE : public WATER_TYPE, public STEEL_TYPE{

private:
    std::string WaterSteelSpecies;
public:
    WATER_STEEL_TYPE(char* N, int HP, float W, float CP, Water_Species WS, Steel_Species SS) :
            POKEMON(N, HP, W, CP),
            WATER_TYPE(N, HP, W, CP, WS),
            STEEL_TYPE(N, HP, W, CP, SS)
    {
        std::string waterString = WaterSpeciesToString(WS);
        std::string steelString = SteelSpeciesToString(SS);
        WaterSteelSpecies = waterString.substr(0, waterString.size() / 2) +
                                      steelString.substr(steelString.size() / 2);
    }

    std::string GetSpecies() const {
        return WaterSteelSpecies;
    }

    std::istream& read(std::istream&) override;
    std::ostream& print(std::ostream&) const override;

    friend std::istream& operator >> (std::istream& in, WATER_STEEL_TYPE& WS);
    friend std::ostream& operator << (std::ostream& out, const WATER_STEEL_TYPE& WS);
};

std::istream& WATER_STEEL_TYPE::read(std::istream& in){
    WATER_TYPE::read(in);
    return in;
}

std::istream& operator >> (std::istream& in, WATER_STEEL_TYPE& WS){
    return WS.read(in);
}

std::ostream& WATER_STEEL_TYPE::print(std::ostream& out) const{
    WATER_TYPE::print(out);
    return out;
}

std::ostream& operator << (std::ostream& out, const WATER_STEEL_TYPE& WS){
    return WS.print(out);
}


class FIRE_TYPE{};
class ELECTRIC_TYPE{};
class FIRE_ELECTRIC_TYPE : public FIRE_TYPE, public ELECTRIC_TYPE{};

//template <class W, class S>
//class MORF : public WATER_STEEL_TYPE, public FIRE_ELECTRIC_TYPE{
//
//    MORF(char* N, int HP, float WA, float CP) : POKEMON(N, HP, WA, CP){}
//
//    MORF& morfing(W&, S&){
//
//    }
//};




int main() {
    std::cout << "Welcome to the Pokemon world!!" << std::endl;
    std::cout << "I see you already caught a pokemon, well done!" << std::endl;
    std::cout << "You have to add it to your POKEDEX" << std::endl;
    std::cout << "What is a POKEDEX?..." << std::endl;
    std::cout << "A POKEDEX is like your own pokemon map that holds all your pokemons." << std::endl;
    std::cout << "Every page of a POKEDEX can hold up to 5 different pokemons, and every page is specific to only one type." << std::endl;
    std::cout << "You can have as many POKEDEX as you can carry." << std::endl;
    std::cout << "So what type is your pokemon?" << std::endl;
    std::cout << "You don't know??" << std::endl;
    std::cout << "Well firs of all there ary 4 basic types: FIRE, WATER, STEEL and ELECTRIC." << std::endl;
    std::cout << "And there are also 2 combination types: FIRE_STEEL type and WATER_ELECTRIC type." << std::endl;
    std::cout << "Now that you know all of this your set to go. Good luck!!" << std::endl;

//    std::string input;
//    std::cin>>input;
//    if(input == "water"){WATER_TYPE BULB("POKITON", 123, 12.2, 1234.4);}
//
//    if(input == "Vaporeon"){WATER_TYPE TRUID("POKassaON", 113, 1212,1234.4 /*Water_Species::Vaporeon*/);
//                 std::cin>>TRUID;
//                 std::cout<<TRUID;}
//
    WATER_TYPE BULB("POKITON", 123, 12.2, 234.4, Water_Species::Squirtle);
    WATER_TYPE TRUID("POKassaON", 113, 1212,1000.2, Water_Species::Vaporeon);
                   TRUID + BULB;
                   std::cout<<BULB.getCP()<<std::endl;
                   std::cout<<TRUID.getCP()<<std::endl;
                   std::cout<<BULB.getType();
//    if(input == "Squirtle"){WATER_TYPE<Water_Species> TRUID("POKassaON", 113, 1212, 1234.4,Water_Species::Squirtle);}
//    if(input == "Blastoise"){WATER_TYPE<Water_Species> TRUID("POKassaON", 113, 1212, 1234.4,Water_Species::Blastoise);}
//    if(input == "Seel"){WATER_TYPE<Water_Species> TRUID("POKassaON", 113, 1212, 1234.4,Water_Species::Seel);}
//    if(input == "Horsea"){WATER_TYPE<Water_Species> TRUID("POKassaON", 113, 1212, 1234.4,Water_Species::Horsea);}

    return 0;
}

/////FA clasa POKEDEX templated ca sa faca adugare bazat pe class obiectului////////////




