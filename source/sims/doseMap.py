import ROOT as r
import math
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
from PIL import Image

def analyseROOT(filename):
	X=[]
	Y=[]
	W=[]
	rFile 	= r.TFile.Open(filename)
	for i,event in enumerate(rFile.Step):
		if(i%1000000==0):
			print(i)
		x=event.x
		y=event.y
		w=event.depEnergy

		X.append(x)
		Y.append(y)
		W.append(w)

	dataToSave=[X,Y,W]

	np.save(filename.split('.')[0]+'_data',dataToSave)


def convertToGyPerS(inFile,outFile,simulatedPhotons=27.6,activity=2.25): #simulatedphotons in millions, activity in Pbq
	data = np.load(inFile)
	xmin =-1000
	xmax =1000
	ymin =-1000
	ymax =1000
	nBins=100
	h,xedges,yedges,image = plt.hist2d(data[0],data[1],range=[[xmin,xmax],[ymin,ymax]],bins=nBins,weights=data[2],cmin=0.001)

	deltaX = np.abs(xedges[0]-xedges[1])/100. #to get it in dm
	deltaY = np.abs(yedges[0]-yedges[1])/100.
	mass   = deltaX*deltaY*1.*1. #1 dm is the height, 1 kg/dm^3 density
	mevFactor= 2.0*activity*160 #Activity in PBq mutliplied with Mev-> J factor
	print("Mass of one bin in kg - ", mass)
	conversionFactor = mevFactor/(mass*simulatedPhotons*np.power(10,6))
	print("Conversion from MeV to Gy/s - ",conversionFactor)

	h=conversionFactor*h
	np.save(outFile,h)

	img = plt.imshow(h)
	plt.axis('off')
	plt.colorbar()
	plt.show()

#analyseROOT('run3.root')
convertToGyPerS('run3_data.npy','run3_doseRate.npy')


# img = plt.imshow(h)
# plt.axis('off')
# #plt.colorbar()
# plt.savefig('out_one.png',bbox_inches='tight')

# fig = plt.figure()
# fig.set_size_inches(3.,3.)
# ax = plt.Axes(fig, [0., 0., 1., 1.])
# ax.set_axis_off()
# fig.add_axes(ax)
# ax.imshow(h, aspect='equal',origin='lower',orientation='horizontal')
# plt.savefig('out_two.png')