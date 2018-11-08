#!/bin/tcsh
source /cvmfs/cms.cern.ch/cmsset_default.csh
cd /users/mrogul/CMSSW_9_4_1/src
eval `scramv1 runtime -csh`
cd /users/mrogul/Work/geant4.10.04-build/bin/
source geant4.csh 
cd /users/mrogul/Work/geant_sims/shielding/build
echo $LD_LIBRARY_PATH
/users/mrogul/Work/geant_sims/shielding/build/exampleB1 /users/mrogul/Work/geant_sims/shielding/build/loop.mac >& loop.out