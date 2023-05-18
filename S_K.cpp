#include <iostream>
#include <cstring>
#include <list>
#include <cxxabi.h>
#include <memory>
#include <limits>


// 'K' stands for killer


template<typename T>
class ITF{

public:

    virtual std::ostream& print(std::ostream&) const = 0;
    virtual std::istream& read(std::istream&) = 0;
    //virtual SerialKiller& equal(const SerialKiller& K) = 0;

    virtual  T& EQUAL(const T& K) = 0;

};

enum class Sex { male, female, unknown};

class SerialKiller : public virtual ITF<SerialKiller> {


private:
    Sex sex;
  char* Name;
  int killcount;
  float IQ;
  //std::string Nationality;
  const char* Type;

protected:
    bool DoesItReads;
    mutable bool DoesItPrints;

public:

  char* getName() const { return this->Name; }
  int getKillCount() const { return this -> killcount; }
  float getIQ() const { return this -> IQ; }
  Sex getSex() const { return this -> sex; }
 // const char* getType() const { return this-> SType;}

  const char* getType() const{

      int status;
      char* demangledName = abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, &status);
      if(status == 0){
          const char* typeName = demangledName;
          return typeName;
      }else {
          return typeid(*this).name();
      }
  }

  void SetReads(bool reads)
  {
      this -> DoesItReads =reads;
  }

  SerialKiller(char* name, int killcount ) : killcount(killcount), IQ(0), Type(getType()) {

      Name = new char[strlen(name) + 1];
      strcpy(Name, name);

      if (getKillCount() >= 3)
          std::cout <<  this-> getName()<<" is a Serial Killer."<<std::endl;
      else
          std::cout <<  this -> getName()<<" is not a Serial Killer."<<std::endl;

  }

  SerialKiller(char* name, int killcount, float iq, Sex sex ) :killcount(killcount), IQ(iq), sex(sex) {

      Name = new char[strlen(name) + 1];
      strcpy(Name, name);

      if(getKillCount() >= 3)
          if(getIQ() >= 150)
              std::cout << getName() <<" is a SerialKiller with an IQ of at least 150 making him a possible fit for the MissionOriented or Visionary type"<<std::endl;
          else
              {std::cout<< getName() <<" is a SerialKiller with an IQ under 150 so probably a ThrillSeeker or a ControlSeeker type."<<std::endl;}
      else
          std::cout<< getName() << " is not a Serial Killer."<<std::endl;

  }

///-------------DEFAULT CONSTRUCTOR-------------///

  SerialKiller()
  {
      Name = new char[strlen("Anonim") + 1];
      strcpy(Name, "Anonim");
      killcount = 0;
      IQ = 0;
      sex = Sex::unknown;
      std::cout<<"Name: "<<getName()<<std::endl;
      std::cout<<"Kill count: unspecified"<<std::endl;
      std::cout<<"IQ: unknown"<<std::endl;
      std::cout<<"Sex: " << static_cast<int>(Sex::unknown)<<std::endl;
      std::cout<<"Type: impossible to determine"<<std::endl;
      std::cout<<"Additional information required to determine whether or not this person represents a danger."<<std::endl;

  }

    SerialKiller(bool silent) {
        Name = new char[strlen("Anonim") + 1];
        strcpy(Name, "Anonim");
        killcount = 0;
        IQ = 0;
        sex = Sex::unknown;
    }


      SerialKiller(const char* n)
    {
        Name = new char[strlen(n) + 1];
        strcpy(Name, n);
    }

    virtual ~SerialKiller()
    {
      //std::cout<<"DESTRUCTOR";
      if(Name == nullptr)
          delete[] Name;
    }

    SerialKiller(const SerialKiller& K):
        killcount(K.killcount),
        IQ(K.IQ),
        sex(K.sex)
    {
      Name = new char[strlen(K.Name) + 1];
        strcpy(Name, K.Name);
    }


    SerialKiller(int x){}

    std::istream& read(std::istream&) override;
    std::ostream& print(std::ostream&) const override;

    friend std::istream& operator >> (std::istream& in, SerialKiller& K);
    friend std::ostream& operator << (std::ostream& out, const SerialKiller& K);

    SerialKiller& operator = (const SerialKiller& K);

    //SerialKiller& equal(const SerialKiller& K) override;

    SerialKiller& EQUAL(const SerialKiller& K) override;

};

//bool SerialKiller::DoesItReads(false);

SerialKiller& SerialKiller::EQUAL(const SerialKiller &K){

    if(this != &K)
    {
        if(this -> Name != nullptr)
        {
            delete[] Name;
            (*this).Name = nullptr;
        }

        this -> Name = new char[strlen(K.Name) + 1];
        strcpy(Name, K.Name);

        killcount = K.killcount;
        IQ = K.IQ;
        sex = K.sex;
    }

    return *this;

}

//SerialKiller& SerialKiller::equal(const SerialKiller &K) {
//
//    if(this != &K)
//    {
//        if(this -> Name != nullptr)
//        {
//            delete[] Name;
//            (*this).Name = nullptr;
//        }
//
//        this -> Name = new char[strlen(K.Name) + 1];
//        strcpy(Name, K.Name);
//
//        killcount = K.killcount;
//        IQ = K.IQ;
//    }
//
//    return *this;
//
//}

SerialKiller& SerialKiller::operator = (const SerialKiller& K){
    return (*this).EQUAL(K);
}

std::istream& SerialKiller::read(std::istream& in){

    DoesItReads = true;

    std::cout<<"Insert the name: ";
    in >> this ->Name;
    std::cout<<"Insert the kill count: ";
    in >> this -> killcount;
    std::cout<<"Insert the IQ: ";
    in>>this -> IQ;

    std::string input;
    bool valid_input = false;

    while(!valid_input) {
        std::cout << "Insert the sex: ";
        in >> input;
        if (input == "male" || input == "Male") {
            sex = Sex::male;
            valid_input = true;
        } else if (input == "female" || input == "Female") {
            sex = Sex::female;
            valid_input = true;
        } else if (input == "unknown" || input == "Unknown") {
            sex = Sex::unknown;
            valid_input = true;
        } else {
            // Handle invalid input
            std::cerr
                    << "Invalid input. Please try again and input a viable response(male/Male or female/Female or unknown/Unknown)."
                    << std::endl
                    <<"Please insert a valid information for this field: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            //exit(1);
        }
    }

    return in;
}

std::istream& operator >> (std::istream& in, SerialKiller& K){
    return K.read(in);
}

//bool SerialKiller::DoesItPrints = false;

std::ostream& SerialKiller::print(std::ostream& out) const{

    DoesItPrints = true;

    out<<"Name: " << this -> Name <<std::endl;
    out<<"Kill count: " << this -> killcount<<std::endl;
    out<<"IQ: "<< this -> IQ<<std::endl;
    out<<"Sex: ";
    switch (SerialKiller::sex) {
        case Sex::male:
            out << "male";
            break;
        case Sex::female:
            out << "female";
            break;
        case Sex::unknown:
            out << "unknown";
            break;
    }
    out<<std::endl;
    out<<"Type: "<<getType()<<std::endl;
    out<<std::endl;
    return out;
}

std::ostream &operator << (std::ostream& out, const SerialKiller& K){
    return K.print(out);
}

///-------------------------------------------------(DERIVED CLASSES)----------------------------------------------------------------///

class MissionOriented : virtual public SerialKiller{

private:
    bool RacialMot;
    bool ReligiousMot;
    bool EthnicityMot;

public:

    bool getRA() const { return this -> RacialMot;}
    bool getRE() const { return this -> ReligiousMot;}
    bool getET() const { return this -> EthnicityMot;}

    MissionOriented():SerialKiller(){}

    MissionOriented(char* name, int killcount, float iq, Sex sex, bool RA, bool RE, bool ET) :
        SerialKiller(name, killcount, iq, sex), RacialMot(RA), ReligiousMot(RE), EthnicityMot(ET){

        if(getRA()) {std::cout<<getName()<<" has racial reasons."<<std::endl;}

        if(getRE()){std::cout<<getName()<<" has religious reasons."<<std::endl;}

        if(getET()){std::cout<<getName()<<" has ethnicity reasons."<<std::endl;}

        if(!getRA() && !getRE() && !getET())
        {std::cout << getName() << " doesn't have reasons associated with the MissionOriented's ones ";}
    }

    MissionOriented(const MissionOriented& M) :
    SerialKiller(M),
    RacialMot(M.RacialMot),
    ReligiousMot(M.ReligiousMot),
    EthnicityMot(M.EthnicityMot)
    {

    }

    MissionOriented(bool silent) : SerialKiller(silent), RacialMot(false), ReligiousMot(false), EthnicityMot(false){}

    virtual ~MissionOriented()
    {
        if(SerialKiller::getName() == nullptr)
        {
            delete[] getName();
        }
    }


    std::istream& read(std::istream&) override;
    std::ostream& print(std::ostream&) const override;

    friend std::istream& operator >>(std::istream& in, MissionOriented& M);
    friend std::ostream& operator <<(std::ostream& out, const MissionOriented& M);

    //SerialKiller& equal(const SerialKiller& K) override;
    MissionOriented& EQUAL(const MissionOriented& M);

    MissionOriented &operator=(const MissionOriented &M);

};

MissionOriented& MissionOriented::EQUAL(const MissionOriented& M){
    SerialKiller::EQUAL(M);
    RacialMot = M.RacialMot;
    ReligiousMot = M.ReligiousMot;
    EthnicityMot = M.EthnicityMot;

    return *this;
}

MissionOriented& MissionOriented::operator=(const MissionOriented &M) {
    return (*this).EQUAL(M);
}


std::istream& MissionOriented::read(std::istream& in) {

    if(!DoesItReads){
        SerialKiller::read(in);
    }
    std::cout<<"Racial Motivations: ";
    in>>this->RacialMot;
    std::cout<<"Religious Motivations: ";
    in>>this->ReligiousMot;
    std::cout<<"Ethnicity Motivations: ";
    in>>this->EthnicityMot;

    return in;
}

std::istream& operator >>(std::istream& in, MissionOriented& M){
    return M.read(in);
}

std::ostream& MissionOriented::print(std::ostream& out) const{
    if(!DoesItPrints){
        SerialKiller::print(out);
    }
    out<<"Racial motivations: " <<(!getRA() ? "NO" : "YES")<<std::endl;
    out<<"Religious motivations: "<<(!getRE() ? "NO" : "YES")<<std::endl;
    out<<"Ethnicity motivations: "<<(!getET() ? "NO" : "YES")<<std::endl;

    return out;
}

std::ostream& operator <<(std::ostream& out, const MissionOriented& M){
    return M.print(out);
}

class Visionary : virtual public SerialKiller{

private:
    bool Randomness;
    bool CoverUp;

public:

    bool getRandomness() const { return this -> Randomness;}
    bool getCoverUp() const { return this -> CoverUp;}

    Visionary():SerialKiller(){}

    Visionary(char* name, int killcount, float iq, Sex sex, bool rand, bool coverup) :
    SerialKiller(name, killcount, iq, sex), Randomness(rand), CoverUp(coverup){

        if(getRandomness()) { std::cout<<"The victims are chosen at random, often in a disorganized manner."<<std::endl;}
        else {std::cout<<"An organized choice of victims is not usually in a Visionary's character"<<std::endl;}

        if(getCoverUp()) {std::cout<<"Little to no effort to cover up crimes is usually part of a Visionary's pattern."<<std::endl;}
        else{std::cout<<"Covering up the crime is more suited to the ControlSeeker type"<<std::endl;}

        if(!getCoverUp() && !getRandomness())
        {std::cout<<"Based on the lack of pattern like behaviour this killer doesn't seems to fall in the Visionary category"<<std::endl;}
    }

    Visionary(const Visionary& V) :
        SerialKiller(V),
        Randomness(V.Randomness),
        CoverUp(V.CoverUp)
    {

    }
    Visionary(bool silent) : SerialKiller(silent){}

    virtual ~Visionary(){
        if(SerialKiller::getName() == nullptr){
            delete getName();
        }
    }


    std::istream& read(std::istream&) override;
    std::ostream& print(std::ostream&) const override;

    friend std::istream& operator >> (std::istream& in, Visionary& V);
    friend std::ostream& operator << (std::ostream& out, const Visionary& V);

    Visionary& EQUAL(const Visionary& V);
    Visionary& operator = (const Visionary& V);

};

Visionary& Visionary::EQUAL(const Visionary &V) {
    SerialKiller::EQUAL(V);
    Randomness = V.Randomness;
    CoverUp = V.CoverUp;

    return *this;
}

Visionary& Visionary::operator=(const Visionary &V) {
    return (*this).EQUAL(V);
}

    std::istream& Visionary::read(std::istream& in){
        if(!DoesItReads){
            SerialKiller::read(in);
        }
        std::cout<<"Random choice of victims: ";
        in>>this->Randomness;
        std::cout<<"Cover up: ";
        in>>this->CoverUp;

        return in;
    }

    std::istream& operator >> (std::istream& in, Visionary& V){
        return V.read(in);
    }

    std::ostream& Visionary::print(std::ostream & out) const {
        if(!DoesItPrints){
            SerialKiller::print(out);
        }
        std::cout<<"Random choice of victims: "<<(!getRandomness() ? "NO" : "YES")<<std::endl;
        std::cout << "Marks of a cover up: " << (!getCoverUp() ? "NO" : "YES") << std::endl;

        return out;
    }

    std::ostream& operator << (std::ostream& out, const Visionary& V){
        return V.print(out);
    }

class ThrillSeeker : virtual public SerialKiller {

private:
        bool HedonisticActs;

public:

        bool getH() const {return this -> HedonisticActs;}

        ThrillSeeker():SerialKiller(){}

        ThrillSeeker(char* name, int killcount, float IQ, Sex sex, bool H) : SerialKiller(name, killcount, IQ, sex), HedonisticActs(H){
            if(getH()) {std::cout<<"Hedonistic acts are common in ThrillSeekers.";}
            else {std::cout<<"The absence of hedonistic acts strongly implies that we are not dealing with a ThrillSeeker";}
        }

        ThrillSeeker(const ThrillSeeker& T):
            SerialKiller(T),
            HedonisticActs(T.HedonisticActs)
        {

        }

    ThrillSeeker(bool silent) : SerialKiller(silent){}

    virtual ~ThrillSeeker(){
        if(SerialKiller::getName() == nullptr){
            delete getName();
        }
    }


        std::istream& read(std::istream&) override;
        std::ostream& print(std::ostream&) const override;

        friend std::istream& operator >>(std::istream& in, ThrillSeeker& T);
        friend std::ostream& operator <<(std::ostream& out, const ThrillSeeker& T);

        ThrillSeeker& EQUAL(const ThrillSeeker& T);
        ThrillSeeker& operator =(const ThrillSeeker& T);

};

    ThrillSeeker& ThrillSeeker::EQUAL(const ThrillSeeker &T) {
        SerialKiller::EQUAL(T);
        HedonisticActs = T.HedonisticActs;

        return *this;
    }

    ThrillSeeker& ThrillSeeker::operator=(const ThrillSeeker &T) {
        return (*this).EQUAL(T);
    }


    std::istream& ThrillSeeker::read(std::istream& in){
        if(!DoesItReads){
            SerialKiller::read(in);
        }
        std::cout<<"Are any hedonistic acts present: ";
        in>>this -> HedonisticActs;

        return in;
    }

    std::istream& operator >> (std::istream& in, ThrillSeeker& T){
        return T.read(in);
    }

    std::ostream& ThrillSeeker::print(std::ostream& out) const{

        if(!DoesItPrints){
            SerialKiller::print(out);
        }
        out<<"Are any hedonistic acts present: "<<(!getH() ? "NO" : "YES")<<std::endl;

        return out;
    }

    std::ostream& operator << (std::ostream& out, const ThrillSeeker& T){
        return T.print(out);
    }

class ControlSeeker : virtual public SerialKiller {

private:
        bool Souvenirs;

public:

        bool getS() const { return this -> Souvenirs; }

        ControlSeeker():SerialKiller(){};

        ControlSeeker(char* name, int killcount, float iq, Sex sex, bool S) :
        SerialKiller(name, killcount, iq, sex), Souvenirs(S){

            if(getS()){std::cout<<"Taking souvenirs is highly present in ControlSeekers."<<std::endl;}
            else{std::cout<<"Note that a souvenir might be something we wouldn't consider important so keep searching."<<std::endl;}
        }

        ControlSeeker(const ControlSeeker& C):
            SerialKiller(C),
            Souvenirs(C.Souvenirs)
        {

        }

    ControlSeeker(bool silent) : SerialKiller(silent){}

    virtual ~ControlSeeker(){
        if(SerialKiller::getName() == nullptr){
            delete getName();
        }
    }


        std::istream& read(std::istream&) override;
        std::ostream& print(std::ostream&) const override;

        friend std::istream& operator >> (std::istream& in, ControlSeeker& C);
        friend std::ostream& operator << (std::ostream& out, const ControlSeeker& C);

        ControlSeeker& EQUAL(const ControlSeeker& C);
        ControlSeeker& operator = (const ControlSeeker& C);

};

    ControlSeeker& ControlSeeker::EQUAL(const ControlSeeker &C) {
        SerialKiller::EQUAL(C);
        Souvenirs = C.Souvenirs;

        return *this;
    }

    ControlSeeker& ControlSeeker::operator=(const ControlSeeker &C) {
        return (*this).EQUAL(C);
    }


    std::istream& ControlSeeker::read(std::istream& in){
        if(!DoesItReads){
            SerialKiller::read(in);
        }
        std::cout<<"Does anything seems to miss, a possible souvenir: ";
        in >> this ->Souvenirs;

        return in;
    }

    std::istream& operator >> (std::istream& in, ControlSeeker& C){
        return C.read(in);
    }

    std::ostream& ControlSeeker::print(std::ostream& out) const {

        if(!DoesItPrints){
            SerialKiller::print(out);
        }
        std::cout<<"Does anything seems to miss, a possible souvenir: "<<(!getS() ? "NO" : "YES")<<std::endl;

        return out;
    }

    std::ostream& operator << (std::ostream& out, const ControlSeeker& C ){
        return C.print(out);
    }

class Hybrid : public MissionOriented, public Visionary, public ThrillSeeker, public ControlSeeker {

    public:


        Hybrid():SerialKiller()
        {
//            std::cout<<"DEFAULT";
        }

        Hybrid(char* name, int kc, float iq, Sex sex, bool ra, bool re, bool et, bool rd, bool c, bool h, bool s) :
        SerialKiller(name, kc, iq, sex),
        MissionOriented(name, kc, iq, sex, ra, re, et),
        ThrillSeeker(name, kc, iq, sex,  h),
        Visionary(name, kc, iq, sex, rd, c),
        ControlSeeker(name, kc, iq, sex, s)
        { std::cout<<"HYBRID";}

        Hybrid(const Hybrid& H):
            SerialKiller(H),
            MissionOriented(H),
            Visionary(H),
            ThrillSeeker(H),
            ControlSeeker(H)
        {

        }

    Hybrid(bool silent) : SerialKiller(silent){}

     ~Hybrid(){

        if(SerialKiller::getName() == nullptr){
            delete getName();
        }
    }


        std::istream& read(std::istream&) override;
        std::ostream& print(std::ostream&) const override;

        friend std::istream& operator >> (std::istream& in, Hybrid& H);
        friend std::ostream& operator << (std::ostream& out, const Hybrid& H);

        Hybrid& EQUAL(const Hybrid& H);
        Hybrid& operator = (const Hybrid& H);
    };

    Hybrid& Hybrid::EQUAL(const Hybrid &H) {
        SerialKiller::EQUAL(H);
        MissionOriented::EQUAL(H);
        Visionary::EQUAL(H);
        ThrillSeeker::EQUAL(H);
        ControlSeeker::EQUAL(H);
    }

    Hybrid& Hybrid::operator=(const Hybrid &H) {
        return (*this).EQUAL(H);
    }

    std::istream& Hybrid::read(std::istream& in){
//        SerialKiller::read(in);
        ThrillSeeker::read(in);
        MissionOriented::read(in);
        Visionary::read(in);
        ControlSeeker::read(in);
        DoesItReads = false;
        return in;
    }

    std::istream& operator>>(std::istream& in, Hybrid& H){
        return H.read(in);
    }

    std::ostream& Hybrid::print(std::ostream& out) const{
//        if(!DoesItPrints){
//            SerialKiller::print(out);
//        }
        ThrillSeeker::print(out);
        MissionOriented::print(out);
        Visionary::print(out);
        ControlSeeker::print(out);

        DoesItPrints = false;
        return out;
    }

    std::ostream& operator << (std::ostream& out, const Hybrid& H){
        return H.print(out);
    }

class WantedList{

    private:
        std::list<SerialKiller*> wantedList;

    public:

        WantedList(){ this -> wantedList = {};}

        void addWanted(SerialKiller* K);
        void printWanted();
        void delloc();
    };

void WantedList::addWanted( SerialKiller* K) {
    wantedList.push_back(K);
}

void WantedList::printWanted() {

    if(wantedList.empty()){std::cout<<"The list is empty."<<std::endl;}

    for(auto K : wantedList){
        std::cout<<"Name: "<<K -> getName()<<std::endl;
        //std::cout<<std::endl;
        //std::cout<<"Is a "<< typeid(*K).name()<<std::endl;
        std::cout<<"Type: "<<K -> getType()<<std::endl;
        std::cout<<std::endl;
    }
}

void WantedList::delloc() {

    if(!wantedList.empty())
    {
        for(auto* K : wantedList)
            delete K;
    }
}

struct KILLER{

    static std::unique_ptr<SerialKiller> CREATE(const std::string& killertype)
    {
        if(killertype == "Plane serial killer")
        {
            return std::make_unique<SerialKiller>();
        }
        else if(killertype == "MissionOriented")
        {
            return std::make_unique<MissionOriented>();
        }
        else if(killertype == "Visionary")
        {
            return std::make_unique<Visionary>();
        }
        else if(killertype == "ThrillSeeker")
        {
            return std::make_unique<ThrillSeeker>();
        }
        else if(killertype == "ControlSeeker")
        {
            return std::make_unique<ControlSeeker>();
        }
        else if(killertype == "Hybrid")
        {
            return std::make_unique<Hybrid>();
        }
        else
        {
            return nullptr;
        }
    }
};

void Menu(){
    int k = 1;
    WantedList W;

    while (k) {
        std::cout << "This is the official FDI MOST WANTED page." << std::endl;
        std::cout << "Press 1 for requesting to add someone to the list." << std::endl;
        std::cout << "Press 2 for a rudimentary diagnosis." << std::endl;
        std::cout << "Press 3 to see the complete list." << std::endl;

        std::cout << "Your option: ";
        std::cin >> k;

        switch (k) {
            case 1: {

                int p = 1;
                while (p) {
                    ///-----///
                    std::cout << std::endl;
                    std::cout
                            << "If you don't have many information about this person press 1 to input a plain Serial Killer."
                            << std::endl;
                    std::cout << "Press 2 if you think this person might be the Mission Oriented type." << std::endl;
                    std::cout << "Press 3 if you think this person might be the Visionary type." << std::endl;
                    std::cout << "Press 4 if you think this person might be the Thrill Seeker type." << std::endl;
                    std::cout << "Press 5 if you think this person might be the Control Seeker type." << std::endl;
                    std::cout << "If it seems that this person fits multiple types press 6." << std::endl;
                    std::cout << std::endl;
                    std::cout << "Press 0 to return to the previous menu.";
                    std::cout << std::endl;
                    std::cout << "Your option: ";

                    std::cin >> p;

                    switch (p) {
                        case 1: {

                            auto *aux = new SerialKiller(false);
                            std::cin >> *aux;
                            W.addWanted(aux);
                            aux->SetReads(false);
                            break;
                        }

                        case 2: {
                            auto *aux = new MissionOriented(false);
                            std::cin >> *aux;
                            W.addWanted(aux);
                            aux->SetReads(false);
                            break;
                        }

                        case 3: {
                            auto *aux = new Visionary(false);
                            std::cin >> *aux;
                            W.addWanted(aux);
                            aux->SetReads(false);
                            break;
                        }

                        case 4: {
                            auto *aux = new ThrillSeeker(false);
                            std::cin >> *aux;
                            W.addWanted(aux);
                            aux->SetReads(false);
                            break;
                        }

                        case 5: {
                            auto *aux = new ControlSeeker(false);
                            std::cin >> *aux;
                            W.addWanted(aux);
                            aux->SetReads(false);
                            break;
                        }

                        case 6: {
                            auto *aux = new Hybrid(false);
                            std::cin >> *aux;
                            W.addWanted(aux);
                            break;
                        }

                        default: {
                            p = 0;
                            break;
                        }

                    }
                }

            }

            case 2: {
                int q = 1;

                while (q) {
                    std::cout << std::endl;
                    std::cout << "There are 4 specific types of serial killers: " << std::endl;
                    std::cout << "Mission Oriented(press 1 if you believe this person fits here)" << std::endl;
                    std::cout << "Visionary(press 2 if you believe this person fits here)" << std::endl;
                    std::cout << "Thrill Seeker(press 3 if you believe this person fits here)" << std::endl;
                    std::cout << "Control Seeker(press 4 if you believe this person fits here)" << std::endl;
                    std::cout << "If this person seems to fit in multiple types press 5." << std::endl;
                    std::cout << std::endl;
                    std::cout << "Press 0 to return to the previous menu.";
                    std::cout << std::endl;

                    std::cout << "Your option: ";
                    std::cin >> q;

                    switch (q) {
                        case 1: {
                            MissionOriented aux(false);
                            std::cin >> aux;
                            std::cout << aux;
                            aux.SetReads(false);
                            break;

                        }

                        case 2: {
                            Visionary aux(false);
                            std::cin >> aux;
                            std::cout << aux;
                            aux.SetReads(false);
                            break;
                        }

                        case 3: {
                            ThrillSeeker aux(false);
                            std::cin >> aux;
                            std::cout << aux;
                            aux.SetReads(false);
                            break;
                        }

                        case 4: {
                            ControlSeeker aux(false);
                            std::cin >> aux;
                            std::cout << aux;
                            aux.SetReads(false);
                            break;
                        }

                        case 5: {
                            Hybrid aux(1);
                            std::cin >> aux;
                            std::cout << aux;
                            break;
                        }

                        default: {
                            q = 0;
                            break;
                        }
                    }
                }
                break;
            }///case 2;

            case 3: {
                W.printWanted();
                break;
            }

            default: {
                k = 0;
                break;
            }
        }
    }

    W.delloc();
}
int main() {

    Menu();
  //  std::unique_ptr<SerialKiller> JEFF = KILLER::CREATE("Visionary");


    return 0;
}
