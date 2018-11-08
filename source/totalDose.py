fileName='AllRodsSummary.txt'
f = open(fileName,'r')
doseSum=0. 	#doseSum should be in nanoGy to get Gy/s as output
counter=0

#This assumes that dose in AllRodsSummary are either in nanoGy or picoGy
for line in f:
	counter+=1
	temp=float(line.split(' ')[0])
	if(line.split(' ')[1]=='picoGy'):
		temp=temp/1000.
	doseSum+=temp
print(doseSum)
print( '-----------'+fileName+'-----------')

#number of photons in the high-activity rod during 1 run
#example: 12 high-activity rods, 12 low; I simulate 48 runs
#on high activity 12 for 1.33MeV and 12 for 1.17MeV photons
#on low activity 12 for 1.33MeV and 12 for 1.17MeV photons = total 48 runs
#n_phot is the number of photons in the high-activity rod during 1 run
n_phot=10000

ratio=0.3409/2.3001 
numberOfEventsPerRun=n_phot*(1+ratio)/(2*1000000.) #average number of emmited photons per run 
totalNumberOfPhotons=numberOfEventsPerRun*counter #in millions
print( 'Total number of photons '+str(totalNumberOfPhotons)+'*10^6')
activity=2.5939 #in PBq
doseRate=2*activity*doseSum/(totalNumberOfPhotons)
print( 'Dose rate in Gy/s '+str(doseRate))
print( 'Number of summands '+str(counter))


f.close()