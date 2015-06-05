export LD_LIBRARY_PATH=/net/per900b/raid0/ledduy/usr.local/lib:/net/per900a/raid0/plsang/usr.local/lib:/usr/local/lib:$LD_LIBRARY_PATH
if [ "$#" -ne 3 ]; then
  echo "Usage: $0 <start_video> <end_video> <threshold> " >&2
  exit 1
fi
count=0
videodir=/net/per900a/raid0/plsang/dataset/MED10_Resized
metadir=/net/per900a/raid0/plsang/dataset/MED10_Resized_meta
outputdir=$metadir/sbd-t$3

if [ ! -d $outputdir ] 
then
	mkdir -p $outputdir
fi

for f in `ls $videodir/*.mp4`
do 
	if [ "$count" -ge $1 ] && [ "$count" -lt $2 ]; then
		echo $count
		fp="${f%}" 		#get file path
		fn="${fp##*/}"	#get file name with extension
		vid="${fn%.*}"	#get file name without extension (video ID)
		of="${vid}.txt" #output file name
		echo "processing video $fn"
		./visualrhythm $3 0 0 $videodir $fn $outputdir/$of
	fi
	let count=$count+1;
	
	#echo "processing video ${fn##*/}"
	#./visualrhythm 80 0 0 /net/sfv215/export/raid4/ledduy/trecvid-med-2011/devel/MED10 ${fn##*/} MED10.txt
done

