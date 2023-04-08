#include <iostream>
#include <cstring>
#include <vector>
#include <type_traits>

// 'K' stands for killer

template<int N>
using Serial = std::integral_constant<bool, (N > 3)>;

class ITF{

public:
    virtual std::ostream& print(std::ostream&) const = 0;
    virtual std::istream& read(std::istream&) = 0;
     
};

class SerialKiller: public virtual ITF {
private:
  int IQ;
  Serial<count>;
  char* Name;
  
public:
  
  ///---GETTERS---///
  char* getName() const { return this->Name; }
  int getKillCount() const { return this -> killcount; }
  float getIQ() const { return this -> IQ; }
  
  SerialKiller(){
      Name = new char[strlen("Anonim") + 1];
      strcpy(Name, "Anonim")
      std::cout<<getName()<<std::endl<<"Additional information required to determine whether or not this person represents a danger.";  
  }
  
   SerialKiller(char* name, int killcount ) : killcount(killcount) {

      Name = new char[strlen(name) + 1];
      strcpy(Name, name);

      if (killcount >= 3)
          std::cout <<  this-> Name<<" is a Serial Killer.";
      else
          std::cout <<  this -> Name<<" is not a Serial Killer.";
   }
  
  SerialKiller(char* name, int killcount, float iq ) :killcount(killcount), IQ(iq) {

      Name = new char[strlen(name) + 1];
      strcpy(Name, name);

      if(getKillCount() >= 3)
          if(getIQ() >= 150)
              std::cout << getName() <<" is a SerialKiller with an IQ of at least 150 making him a possible fit for the  MissionOriented or Visionary type.";
          else
              {std::cout<< getName() <<" is a SerialKiller with an IQ under 150 so probably a ThrillSeeker or a ControlSeeker type.";}
      else
          std::cout<< getName() << " is not a Serial Killer.";

  }
  
      SerialKiller(const char* n)
    {
        Name = new char[strlen(n) + 1];
        strcpy(Name, n);
    }
    
    std::istream& read(std::istream&);
    std::ostream& print(std::ostream&) const;

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

class ThrillSeeker : public virtual SerialKiller, public ITF {};

class MissionOriented : public virtual  SerialKiller {

private:
    bool RacialMot;
    bool ReligiousMot;
    bool EthnicityMot;
    bool Sadism;

public:

    bool getRA() const { return this -> RacialMot;}
    bool getRE() const { return this -> ReligiousMot;}
    bool getET() const { return this -> EthnicityMot;}

    MissionOriented(char* name, int killcount, float iq, bool RA, bool RE, bool ET) :
        SerialKiller(name, killcount, iq), RacialMot(RA), ReligiousMot(RE), EthnicityMot(ET){

        if(getRA()) {std::cout<<getName()<<" has racial reasons."<<std::endl;}

        if(getRE()){std::cout<<getName()<<" has religious reasons."<<std::endl;}

        if(getET()){std::cout<<getName()<<" has ethnicity reasons."<<std::endl;}

        if(!getRA() && !getRE() && !getET())
        {std::cout << getName() << " doesn't have reasons associated with the MissionOriented's ones ";}
    }


};

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
        std::cout<<"Random choice of victims: "<<getRandomness()<<std::endl;
        std::cout<<"Marks of a cover up: "<<getCoverUp()<<std::endl;

        return out;
    }

    std::ostream& operator << (std::ostream& out, const Visionary& V){
        return V.print(out);
    }

class ThrillSeeker : public virtual SerialKiller, public ITF {};

class ControlSeeker : public virtual SerialKiller, public ITF {};

class Hybrid : public ThrillSeeker, public MissionOriented, public Visionary, public ControlSeeker, public ITF {};
