import os

template_csh="""#!/bin/tcsh
source /cvmfs/cms.cern.ch/cmsset_default.csh
cd /users/mrogul/CMSSW_9_4_1/src
eval `scramv1 runtime -csh`
cd /users/mrogul/Work/geant4.10.04-build/bin/
source geant4.csh 
cd {2}/{3}/water{1}
echo $LD_LIBRARY_PATH
{2}/Source {2}/rod{0}.mac {1} >& rod{0}.out
"""

template_txt="""executable  =  rod{0}.csh
universe    =  vanilla
log         =  rod{0}.log
getenv      =  True
queue
"""
buildPATH = '/users/mrogul/Work/geant_sims/paperRecalc/ChangingPhi/fromGit/withWalls/build'
jobsDir   = '10.5.'

for folderNumber in xrange(1,7):
    if not os.path.exists(jobsDir+'/water'+str(folderNumber)):
        os.makedirs(jobsDir+'/water'+str(folderNumber))
	for i in xrange(24):
		fileName='water'+str(folderNumber)+'/rod'+str(i)
		
		f_csh = open(jobsDir+"/"+fileName+".csh","w")
		f_csh.write(template_csh.format(i,folderNumber,buildPATH,jobsDir))
		f_csh.close()

		f_txt = open(jobsDir+"/"+fileName+".txt","w")
		f_txt.write(template_txt.format(i,folderNumber,buildPATH,jobsDir))
		f_txt.close()

os.system('chmod 777 '+jobsDir+'/water?/*sh')
os.system('chmod 777 '+jobsDir+'/water1?/*sh')


"""/run/initialize
/gps/position {0} {1} 0 cm

/gps/pos/type Volume
/gps/pos/shape Cylinder
/gps/pos/radius 0.59 cm
/gps/pos/halfz 17.5 cm

/gps/particle gamma
/gps/ang/type iso

/gps/ene/mono 1.1732 MeV
/run/beamOn 10 #50000000

/gps/ene/mono 1.3325 MeV
/run/beamOn 10 #50000000"""
