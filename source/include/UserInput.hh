#ifndef UserInput_h
#define UserInput_h 1

#include "globals.hh"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <cstring>
#include "G4ThreeVector.hh"

class UserInput {

std::map<std::string, std::string> cfgParams;
std::string cfgFileName = "configuration.txt";
public:
  UserInput();
  ~UserInput();
  
  G4ThreeVector GetSetupPlacement(){G4ThreeVector setupPlacement = G4ThreeVector(x,y,z); return setupPlacement;}
  
public:
  double x,y,z;
};

#endif
