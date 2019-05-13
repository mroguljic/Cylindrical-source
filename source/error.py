import ROOT as r
from time import sleep


nBins=150
EMin=0.
EMax=1.5

jobsDir = '13.5.'

for i in xrange(1,17):
	#print i
	folder=jobsDir+'/water'+str(i)
	file=r.TFile.Open(folder+'/Total.root')
	tree=file.Get('ttree')

	histogram = r.TH1F(folder,folder,nBins, EMin, EMax)

	
	#nEntries=tree.GetEntriesFast()
	#print nEntries

	SumError=0.
	SumEnergy=0.
	
	tree.Draw('Edep>>{0}'.format(folder))

	for k in xrange(1,nBins+1):
		E_k=histogram.GetBinCenter(k)
		N_k=histogram.GetBinContent(k)
		SumError+=E_k*E_k*N_k
		SumEnergy+=E_k*N_k
	std=r.TMath.Sqrt(SumError)

	#print std
	#print SumEnergy
	print std/SumEnergy
