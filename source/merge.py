import os

jobsDir = '19.6.'


for folderNumber in xrange(1,6):
    folder  = jobsDir+"/water"+str(folderNumber)+"/"
    command = "hadd "+folder+"Total.root "+folder+"*root"
    print command
    os.system(command)
