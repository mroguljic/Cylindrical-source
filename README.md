# Cylindrical-source
Geant4 simulation of a cylindrical Cobalt-60 source. The source rack consists of 24 guiding tubes with cobalt pills placed inside each of them.
The geometry of the whole setup can be seen in DetectorConstruction and it consists of the source rack, walls of the room and a shielding setup with a small silicon box placed in the corner of the room. Shielding has been constructed in FreeCAD and afterwards imported to Geant4 by converting it to a .gdml file. It consists of ~200 lead bricks. Most of the bricks are adjancent to other bricks which causes them to share surfaces which can (most probably will) cause issues in Geant. For that reason, before exporting to gdml, all the bricks were "joinConnected" in FreeCAD. Shielding reduced the dose rate by ~500 times.

The "dosimeter" in this version the setup is a silicon box which immitates an electronic chip. It is located inside the shielding.

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

![alt text](https://github.com/mroguljic/Cylindrical-source/blob/master/source/image.png)

