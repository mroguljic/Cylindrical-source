import os
buildPATH = '/home/mrogulji/geant/CylinderSource/build'
jobsDir   = 'jobsDir'
for folderNumber in xrange(1,7):
	os.chdir(buildPATH+'/'+jobsDir+'/water'+str(folderNumber))
	for i in xrange(12):
		command ='condor_submit loop'+str(i)+'.txt'
		print command
		os.system(command)
