#include <iostream>
#include <cstring>
#include <vector>
#include <type_traits>

// 'K' stands for killer

template<int N>
using Serial = std::integral_constant<bool, (N > 3)>;

class SerialKiller {
private:
  int IQ;
  Serial count;
  char* Name;
  
public:
  
  SerialKiller(){}
  
      SerialKiller(const char* n)
    {
        Name = new char[strlen(n) + 1];
        strcpy(Name, n);
    }
};

class ThrillSeeker : public virtual SerialKiller {};

class MissionOriented : public virtual  SerialKiller {};

class Visionary : public virtual SerialKiller {};

class ControlSeeker : public virtual SerialKiller {};

class Hybrid : public ThrillSeeker, public MissionOriented, public Visionary, public ControlSeeker {};
