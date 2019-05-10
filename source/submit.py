import os
buildPATH = '/users/mrogul/Work/geant_sims/paperRecalc/ChangingPhi/fromGit/withWalls/build'
jobsDir   = '10.5.'
for folderNumber in xrange(1,7):
	os.chdir(buildPATH+'/'+jobsDir+'/water'+str(folderNumber))
	for i in xrange(24):
		command ='condor_submit rod'+str(i)+'.txt'
		print command
		os.system(command)
