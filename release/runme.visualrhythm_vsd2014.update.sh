

logfile=/net/per610a/export/das11f/ledduy/mediaeval-vsd-2013/SBfiles/segmentation-rsz/log/SbInfo_update.per900c.log
echo $logfile


echo "starting... " >> $logfile
date >> $logfile 
./visualrhythm_vsd2014.sh test2013 mpg 20 0 1 &
./visualrhythm_vsd2014.sh test2013 mpg 30 0 1 &
./visualrhythm_vsd2014.sh test2013 mpg 40 0 1 &
wait
./visualrhythm_vsd2014.sh test2013 mpg 50 0 1 &
./visualrhythm_vsd2014.sh test2013 mpg 60 0 1 &
./visualrhythm_vsd2014.sh test2013 mpg 70 0 1 &
wait
echo "finish " >> $logfile
date >> $logfile

