import math

template="""/control/macroPath {3}
/run/initialize
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

buildPATH = '/users/mrogul/Work/geant_sims/paperRecalc/changingH_r50/recalc/build'


n_rods=24
n_phot=100000
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
	f.write(template.format(x,y,n,buildPATH))

# template="""/control/macroPath {0}
# /control/loop singleRun.mac runNumber 0 23 1"""
# fileName='loop.mac'
# f = open(fileName,"w")
# f.write(template.format(buildPATH))
