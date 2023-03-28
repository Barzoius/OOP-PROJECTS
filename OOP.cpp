#include <iostream>
#include <cstring>

class SerialKiller {};

class ThrillSeeker : public virtual SerialKiller {};

class MissionOriented : public virtual  SerialKiller {};

class Visionary : public virtual SerialKiller {};

class ControlSeeker : public virtual SerialKIller {};

class Hybrid : public ThrillSeeker, public MissionOriented, public Visionary, public ControlSeeker {};
