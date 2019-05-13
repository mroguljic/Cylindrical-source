import os

jobsDir = '13.5.'


for folderNumber in xrange(1,17):
    folder  = jobsDir+"/water"+str(folderNumber)+"/"
    command = "hadd "+folder+"Total.root "+folder+"*root"
    print command
    os.system(command)
