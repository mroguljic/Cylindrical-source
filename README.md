# Cylindrical-source
Geant4 simulation of a cylindrical Cobalt-60 source. The source rack consists of 24 guiding tubes with cobalt pills placed inside each of them.
The geometry of the whole setup can be seen in DetectorConstruction and it consists of the source rack, walls of the room and a small water orb
which acts as a dosimeter in the simulation. Position of the dosimeter can be changed in configuration.txt (values are in cm).

Tested on ubuntu 14.04. LTS  
Simulations are performed using Geant (4.10.3)            - https://geant4.web.cern.ch/  
To install geant4 and compile the code, cmake 3 is needed -https://cmake.org/download/    
Python 2 (or 3 with some minor changes) is required

To compile, create a directory (Cylindrical-source) and copy the source directory in it. From Cylindrical-source directory, do:
```
mkdir build  
cd build  
cmake -DGeant4_DIR=...../geantInstallation/lib/Geant4-10.3.3 ../source  
make  
```
Edit generateMacros.py (update the path, change number of photons you wish to simulate etc.)

```
source ..../geantInstallation/bin/geant4.sh (or .csh)
python generateMacros.py
./Source loop.mac
python totalDose.py
```

If you wish to just look at the geometry, run
```
./Source
```

