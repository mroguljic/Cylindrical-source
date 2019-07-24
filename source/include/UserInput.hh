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
  
  G4ThreeVector GetSetupPlacement1(){G4ThreeVector setupPlacement = G4ThreeVector(x1,y1,z); return setupPlacement;}
  G4ThreeVector GetSetupPlacement2(){G4ThreeVector setupPlacement = G4ThreeVector(x2,y2,z); return setupPlacement;}
  G4ThreeVector GetSetupPlacement3(){G4ThreeVector setupPlacement = G4ThreeVector(x3,y3,z); return setupPlacement;}
  G4ThreeVector GetSetupPlacement4(){G4ThreeVector setupPlacement = G4ThreeVector(x4,y4,z); return setupPlacement;}
  G4ThreeVector GetSetupPlacement5(){G4ThreeVector setupPlacement = G4ThreeVector(x5,y5,z); return setupPlacement;}
  G4ThreeVector GetSetupPlacement6(){G4ThreeVector setupPlacement = G4ThreeVector(x6,y6,z); return setupPlacement;}
  std::string GetRootFileName(){return rootFileName;}

public:
  double x1,y1;
  double x2,y2;
  double x3,y3;
  double x4,y4;
  double x5,y5;
  double x6,y6;
  double z;
  std::string rootFileName; 
};

#endif
