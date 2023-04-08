#include <iostream>
#include <cstring>
#include <vector>
#include <type_traits>

// 'K' stands for killer

/// Note that this represents th boilerplate code part 
/// There are no functionalities yet 

template<int N>
using Serial = std::integral_constant<bool, (N > 3)>;

class ITF{

public:
    virtual std::ostream& print(std::ostream&) const = 0;
    virtual std::istream& read(std::istream&) = 0;
};

class SerialKiller : public virtual ITF {

private:
  char* Name;
  int killcount;
  float IQ;
  std::vector<SerialKiller> WANTEDList;

public:

  char* getName() const { return this->Name; }
  int getKillCount() const { return this -> killcount; }
  float getIQ() const { return this -> IQ; }
  //std::vector<SerialKiller> GetWantedList() const { return this -> WANTEDList; }

  SerialKiller(char* name, int killcount ) : killcount(killcount) {

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

};

std::istream& SerialKiller::read(std::istream& in){
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
class MissionOriented : public virtual  SerialKiller {

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

};

std::istream& MissionOriented::read(std::istream& in) {
    SerialKiller::read(in);
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

class Visionary : public virtual SerialKiller{

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

};

    std::istream& Visionary::read(std::istream& in){
        SerialKiller::read(in);
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

class ThrillSeeker : public virtual SerialKiller {

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

};

    std::istream& ThrillSeeker::read(std::istream& in){
        SerialKiller::read(in);
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

class ControlSeeker : public virtual SerialKiller {

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

};
    std::istream& ControlSeeker::read(std::istream& in){
        SerialKiller::read(in);
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
//class Hybrid : public ThrillSeeker, public MissionOriented, public Visionary, public ControlSeeker {};


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
    return 0;
}

