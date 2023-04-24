#include <iostream>
#include <cstring>
#include <vector>
#include <type_traits>

// 'K' stands for killer

template<int N>
using Serial = std::integral_constant<bool, (N > 3)>;


template<typename T>
class ITF{

public:

    virtual std::ostream& print(std::ostream&) const = 0;
    virtual std::istream& read(std::istream&) = 0;
    //virtual SerialKiller& equal(const SerialKiller& K) = 0;

//    T& EQUAL(T& K){
//        static_cast<T*>(this)->EQUAL(K);
//        return static_cast<T&>(*this);
//    }
    virtual  T& EQUAL(const T& K) = 0;

};

class SerialKiller : public virtual ITF<SerialKiller> {

private:
  char* Name;
  int killcount;
  float IQ;
  const std::string Type;

protected:
    bool DoesItReads;

public:

  char* getName() const { return this->Name; }
  int getKillCount() const { return this -> killcount; }
  float getIQ() const { return this -> IQ; }
  //std::vector<SerialKiller> GetWantedList() const { return this -> WANTEDList; }

  SerialKiller(char* name, int killcount ) : killcount(killcount), IQ(0) {

      Name = new char[strlen(name) + 1];
      strcpy(Name, name);

      if (getKillCount() >= 3)
          std::cout <<  this-> getName()<<" is a Serial Killer."<<std::endl;
      else
          std::cout <<  this -> getName()<<" is not a Serial Killer."<<std::endl;
  }

  SerialKiller(char* name, int killcount, float iq ) :killcount(killcount), IQ(iq) {

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

  SerialKiller(){
      Name = new char[strlen("Anonim") + 1];
      strcpy(Name, "Anonim");
      std::cout<<getName()<<std::endl<<"Additional information required to determine whether or not this person represents a danger."<<std::endl;
  }

      SerialKiller(const char* n)
    {
        Name = new char[strlen(n) + 1];
        strcpy(Name, n);
    }

    ~SerialKiller()
    {
      //std::cout<<"DESTRUCTOR";
      if(Name == nullptr)
          delete Name;
    }

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

    return in;
}

std::istream& operator >> (std::istream& in, SerialKiller& K){
    return K.read(in);
}

std::ostream& SerialKiller::print(std::ostream& out) const{

    out<<"Name: " << this -> Name <<std::endl;
    out<<"Kill count: " << this -> killcount<<std::endl;
    out<<"IQ: "<< this -> IQ<<std::endl;

    return out;
}

std::ostream &operator << (std::ostream& out, const SerialKiller& K){
    return K.print(out);
}


///-----------------------------------------------------------------------------------------------------------------
class MissionOriented : virtual public  SerialKiller{

private:
    bool RacialMot;
    bool ReligiousMot;
    bool EthnicityMot;

public:

    bool getRA() const { return this -> RacialMot;}
    bool getRE() const { return this -> ReligiousMot;}
    bool getET() const { return this -> EthnicityMot;}

    MissionOriented(){}

    MissionOriented(char* name, int killcount, float iq, bool RA, bool RE, bool ET) :
        SerialKiller(name, killcount, iq), RacialMot(RA), ReligiousMot(RE), EthnicityMot(ET){

        if(getRA()) {std::cout<<getName()<<" has racial reasons."<<std::endl;}

        if(getRE()){std::cout<<getName()<<" has religious reasons."<<std::endl;}

        if(getET()){std::cout<<getName()<<" has ethnicity reasons."<<std::endl;}

        if(!getRA() && !getRE() && !getET())
        {std::cout << getName() << " doesn't have reasons associated with the MissionOriented's ones ";}
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
    SerialKiller::print(out);
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

    Visionary(){}

    Visionary(char* name, int killcount, float iq, bool rand, bool coverup) :
    SerialKiller(name, killcount, iq), Randomness(rand), CoverUp(coverup){

        if(getRandomness()) { std::cout<<"The victims are chosen at random, often in a disorganized manner."<<std::endl;}
        else {std::cout<<"An organized choice of victims is not usually in a Visionary's character"<<std::endl;}

        if(getCoverUp()) {std::cout<<"Little to no effort to cover up crimes is usually part of a Visionary's pattern."<<std::endl;}
        else{std::cout<<"Covering up the crime is more suited to the ControlSeeker type"<<std::endl;}

        if(!getCoverUp() && !getRandomness())
        {std::cout<<"Based on the lack of pattern like behaviour this killer doesn't seems to fall in the Visionary category"<<std::endl;}
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
        SerialKiller::print(out);
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

        ThrillSeeker(){}

        ThrillSeeker(char* name, int killcount, float IQ, bool H) : SerialKiller(name, killcount, IQ), HedonisticActs(H){
            if(getH()) {std::cout<<"Hedonistic acts are common in ThrillSeekers.";}
            else {std::cout<<"The absence of hedonistic acts strongly implies that we are not dealing with a ThrillSeeker";}
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
        SerialKiller::print(out);
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

        ControlSeeker(){};

        ControlSeeker(char* name, int killcount, float iq, bool S) :
        SerialKiller(name, killcount, iq), Souvenirs(S){

            if(getS()){std::cout<<"Taking souvenirs is highly present in ControlSeekers."<<std::endl;}
            else{std::cout<<"Note that a souvenir might be something we wouldn't consider important so keep searching."<<std::endl;}
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
        SerialKiller::print(out);
        std::cout<<"Does anything seems to miss, a possible souvenir: "<<(!getS() ? "NO" : "YES")<<std::endl;

        return out;
    }

    std::ostream& operator << (std::ostream& out, const ControlSeeker& C ){
        return C.print(out);
    }

class Hybrid : public ThrillSeeker, public MissionOriented, public Visionary, public ControlSeeker {

    public:

        Hybrid(){std::cout<<"DEFAULT";}

        Hybrid(char* name, int kc, float iq, bool ra, bool re, bool et, bool rd, bool c, bool h, bool s) :
        SerialKiller(name, kc, iq),
        MissionOriented(name, kc, iq, ra, re, et),
        ThrillSeeker(name, kc, iq,  h),
        Visionary(name, kc, iq, rd, c),
        ControlSeeker(name, kc, iq, s)
        { std::cout<<"HYBRID";}

        std::istream& read(std::istream&) override;
        std::ostream& print(std::ostream&) const override;

        friend std::istream& operator >> (std::istream& in, Hybrid& H);
        friend std::ostream& operator << (std::ostream& out, const Hybrid& H);
    };

    std::istream& Hybrid::read(std::istream& in){
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

        ThrillSeeker::print(out);
        MissionOriented::print(out);
        Visionary::print(out);
        ControlSeeker::print(out);

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
        //void removeWanted(SerialKiller* K);
    };

void WantedList::addWanted(SerialKiller *K) {
    wantedList.push_back(K);
}

void WantedList::printWanted() {
    for(auto K : wantedList){
        std::cout<<"Name: "<<K -> getName()<<std::endl;
        //std::cout<<"Is a "<< typeid(*K).name()<<std::endl;
    }
}

int main() {
    //SerialKiller S("Ted", 4, 10);

    //MissionOriented M("MARIUS", 5, 153, false, false, false);
    //SerialKiller S;
//    MissionOriented M;
//    std::cin>>M;
//    std::cout << M;
//    Visionary("Dan", 6, 150, false, false);
//    Visionary V;
//    std::cin>>V;
//    std::cout<<V;
//    ThrillSeeker T;
//    std::cin>>T;
//    std::cout<<T;

//    ControlSeeker C;
//    std::cin>>C;
//    std::cout<<C;

//    SerialKiller C("DAN", 12, 21);
//    SerialKiller B("PAN", 45, 2123);
//    std::cout<<C;
//    C = B;
//    std::cout<<C;

//    MissionOriented M("DAVID", 1, 154, false, true, false);
//    MissionOriented X("MATHEW", 9, 140, true, false, false);
//
//    std::cout<<M<<std::endl;
//
//    M = X;
//
//    std::cout<<M<<std::endl;

//    Hybrid H;
//    std::cout<<std::endl;
//    std::cin>>H;
//
//     Hybrid W;
//     std::cout<<std::endl;
//     std::cin>>W;

//    ThrillSeeker D;
//    MissionOriented M;
//
//    std::cin>>D;
//    std::cout<<std::endl;
//    std::cin>>M;

   // Hybrid("DAN", 12, 230, false, true, false, false, true, false, true);

    return 0;
}