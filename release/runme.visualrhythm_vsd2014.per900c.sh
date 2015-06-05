
threshold=(20 30 40 50 60 70)

logfile=/net/per610a/export/das11f/ledduy/mediaeval-vsd-2013/SBfiles/segmentation-rsz/log/SbInfo_$threshold.per900c.log
echo $logfile

for i in "${threshold[@]}"
do
    echo "output: $i"
	echo "starting with threshold $i... " >> $logfile
	date >> $logfile 
	./visualrhythm_vsd2014.sh test2013 mpg $i 0 3 &
	./visualrhythm_vsd2014.sh test2013 mpg $i 3 6 &
	./visualrhythm_vsd2014.sh test2013 mpg $i 6 8 &
	./visualrhythm_vsd2014.sh test2014 mpg $i 0 3 &
	./visualrhythm_vsd2014.sh test2014 mpg $i 3 6 &
	./visualrhythm_vsd2014.sh test2014 mpg $i 6 7 &
	./visualrhythm_vsd2014.sh Clips mp4 $i 0 86 &
	wait
	echo "finish " >> $logfile
	date >> $logfile
done
