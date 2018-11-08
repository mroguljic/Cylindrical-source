#include "UserInput.hh" 
#include "G4SystemOfUnits.hh"

UserInput::UserInput(){
  std::ifstream cfgFile; 
  cfgFile.open(cfgFileName);
  std::string line;
  char * key, * value;
  while(cfgFile >> line){
    char *cstr   = &line[0u];
    key          = std::strtok (cstr,"=");
    value        = std::strtok (NULL,"=");
    cfgParams.insert(std::make_pair(key,value));
    }

  x = stod(cfgParams["x"])*cm;
  y = stod(cfgParams["y"])*cm;
  z = stod(cfgParams["z"])*cm;

}

UserInput::~UserInput(){}

