import os
buildPATH = '/users/mrogul/Work/geant_sims/paperRecalc/changingH_r100/recalc/build'
jobsDir   = '13.5.'
for folderNumber in xrange(1,17):
	os.chdir(buildPATH+'/'+jobsDir+'/water'+str(folderNumber))
	for i in xrange(24):
		command ='condor_submit rod'+str(i)+'.txt'
		print command
		os.system(command)
