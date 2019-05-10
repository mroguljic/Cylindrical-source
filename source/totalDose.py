totalDose = open('TotalDose.txt','w')

for i in xrange(1,7):
	fileName='water'+str(i)+'/AllRodsSummary.txt'
	f = open(fileName,'r')
	doseSum=0. 	#doseSum should be in nanoGy
	counter=0

	for line in f:
		counter+=1
		temp=float(line.split(' ')[0])
		if(line.split(' ')[1]=='picoGy'):
			temp=temp/1000.
		#print temp
		doseSum+=temp
	print '-----------'+fileName+'-----------'

	#numberOfEventsPerRun=int(input('Enter the number of events per run (in millions):'))
	numberOfEventsPerRun=57.4 #in millions, 100(active rod)+14.8(passive rod) / 2
	totalNumberOfPhotons=numberOfEventsPerRun*counter #in millions
	print 'Total number of photons '+str(totalNumberOfPhotons)+'*10^6'
	activity=2.64 #in PBq
	doseRate=2*activity*doseSum/(totalNumberOfPhotons)
	print 'Dose rate in Gy/s '+str(doseRate)
	print 'Number of summands '+str(counter)

	#print 'Dose rate is '+str(doseRate)+' Gy/s'
	totalDose.write(str(doseRate)+'\n')

	f.close()
