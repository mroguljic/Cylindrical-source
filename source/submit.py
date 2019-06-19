import os
buildPATH = '/users/mrogul/Work/geant_sims/paperRecalc/changingR/build'
jobsDir   = '19.6.'
for folderNumber in xrange(1,6):
	os.chdir(buildPATH+'/'+jobsDir+'/water'+str(folderNumber))
	for i in xrange(24):
		command ='condor_submit rod'+str(i)+'.txt'
		print command
		os.system(command)
