import os

jobsDir = '10.5.'


for folderNumber in xrange(1,7):
    folder  = jobsDir+"/water"+str(folderNumber)+"/"
    command = "hadd "+folder+"Total.root "+folder+"*root"
    print command
    os.system(command)
