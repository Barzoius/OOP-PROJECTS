#include <iostream>
#include <cstring>
#include <vector>
#include <type_traits>

temmplate<int N>
using Serial = std::integral_const<bool, (N > 3)>;

class SerialKiller {};

class ThrillSeeker : public virtual SerialKiller {};

class MissionOriented : public virtual  SerialKiller {};

class Visionary : public virtual SerialKiller {};

class ControlSeeker : public virtual SerialKIller {};

class Hybrid : public ThrillSeeker, public MissionOriented, public Visionary, public ControlSeeker {};
