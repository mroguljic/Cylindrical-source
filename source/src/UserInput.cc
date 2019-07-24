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

  x1 = stod(cfgParams["x1"])*cm;
  y1 = stod(cfgParams["y1"])*cm;
  x2 = stod(cfgParams["x2"])*cm;
  y2 = stod(cfgParams["y2"])*cm;
  x3 = stod(cfgParams["x3"])*cm;
  y3 = stod(cfgParams["y3"])*cm;
  x4 = stod(cfgParams["x4"])*cm;
  y4 = stod(cfgParams["y4"])*cm;
  x5 = stod(cfgParams["x5"])*cm;
  y5 = stod(cfgParams["y5"])*cm;
  x6 = stod(cfgParams["x6"])*cm;
  y6 = stod(cfgParams["y6"])*cm;
  z = stod(cfgParams["z"])*cm;
  //rootFileName = cfgParams["rootFileName"];
}

UserInput::~UserInput(){}

