import os
from subprocess import call

startRun = 6
stopRun = 7

for i in range(startRun,stopRun+1):
	dirName = 'run'+str(i)
	call('mkdir '+dirName, shell=True)
	call('cp *py '+dirName,shell=True)
	call('cp *mac '+dirName,shell=True)
	#call('cd '+dirName,shell=True)
	os.chdir('./'+dirName)
	call('python generate_macros.py',shell=True)
	os.chdir('..')
