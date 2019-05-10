import os


for folderNumber in xrange(1,7):
    folder  = "water"+str(folderNumber)+"/"
    command = "hadd "+folder+"Total.root "+folder+"*root"
    print command
    os.system(command)
