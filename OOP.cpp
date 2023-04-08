#include <iostream>
#include <cstring>
#include <vector>
#include <type_traits>

// 'K' stands for killer

template<int N>
using Serial = std::integral_constant<bool, (N > 3)>;

class ITF{};

class SerialKiller: public ITF {
private:
  int IQ;
  Serial<count>;
  char* Name;
  
public:
  
  SerialKiller(){}
  
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
};

class ThrillSeeker : public virtual SerialKiller, public ITF {};

class MissionOriented : public virtual SerialKiller, public ITF {};

class Visionary : public virtual SerialKiller, public ITF{};

class ControlSeeker : public virtual SerialKiller, public ITF {};

class Hybrid : public ThrillSeeker, public MissionOriented, public Visionary, public ControlSeeker, public ITF {};
