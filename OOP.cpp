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
  
  SerialKiller(int x)  {
      if (x == 1)
          std::cout << "TED";
      else
          std::cout << "MORON 1";
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
