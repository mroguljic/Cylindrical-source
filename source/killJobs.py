import os

startId = 2721512
stopId  = 2721595

for i in xrange(startId,stopId+1):
	command='condor_rm '+str(i)
	print command
	os.system(command)