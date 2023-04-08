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
