
threshold=(20 30 40 50 60 70)

logfile=/net/per610a/export/das11f/ledduy/mediaeval-vsd-2013/SBfiles/segmentation-rsz/log/SbInfo_$threshold.per900a.log
echo $logfile

for i in "${threshold[@]}"
do
    echo "output: $i"
	echo "starting with threshold $i... " >> $logfile
	date >> $logfile 
	./visualrhythm_vsd2014.sh devel2013 mpg $i 0 3 &
	./visualrhythm_vsd2014.sh devel2013 mpg $i 3 6 &
	./visualrhythm_vsd2014.sh devel2013 mpg $i 6 9 &
	./visualrhythm_vsd2014.sh devel2013 mpg $i 9 12 &
	./visualrhythm_vsd2014.sh devel2013 mpg $i 12 15 &
	./visualrhythm_vsd2014.sh devel2013 mpg $i 15 18 &
	wait
	echo "finish " >> $logfile
	date >> $logfile
done
