import math
import random
import numpy as np
import os

template="""/run/initialize
/gps/position {0} {1} 0 cm

/gps/pos/type Volume
/gps/pos/shape Cylinder
/gps/pos/radius 0.55 cm
/gps/pos/halfz 16.2 cm

/gps/particle gamma
/gps/ang/type iso

/gps/ene/mono 1.1732 MeV
/run/beamOn {2}

/gps/ene/mono 1.3325 MeV
/run/beamOn {2}"""


n_rods=24
n_phot=1000000
ratio=0.3409/2.3001 
radius=13.0
for i in range(n_rods):
	phi = 7.5+i*360./n_rods
	print(phi)
	x = radius*math.cos( phi * math.pi / 180.0 )
	y = radius*math.sin( phi * math.pi / 180.0 )
	fileName='rod'+str(i)+'.mac'
	f = open(fileName,"w")
	n=n_phot
	if i%2==1:
		n=int(n*ratio)
	f.write(template.format(x,y,n))

cwd = os.getcwd()
print(cwd)
template="""/control/macroPath {0}
/control/loop singleRun.mac runNumber 0 23 1""".format(cwd)
fileName='loop.mac'
f = open(fileName,"w")
f.write(template)
f.close()

#lista = np.random.uniform(-98., 98., 13)
randoms = []
while(len(randoms)<12):
	x,y = np.random.uniform(-98.,98.,2)
	if(x*x+y*y > 400):
		randoms.append(x)
		randoms.append(y)

positions = []
for i in randoms:
	positions.append(str(i))
configurationTemplate = """x1={0[0]}
y1={0[1]}
x2={0[2]}
y2={0[3]}
x3={0[4]}
y3={0[5]}
x4={0[6]}
y4={0[7]}
x5={0[8]}
y5={0[9]}
x6={0[10]}
y6={0[11]}
z=0.0
""".format(positions)
#print(configurationTemplate)
fileName = 'configuration.txt'
f = open(fileName,"w")
f.write(configurationTemplate)