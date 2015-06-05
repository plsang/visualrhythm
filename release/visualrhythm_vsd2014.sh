PATH=/net/per900a/raid0/plsang/software/gcc-4.8.1/release/bin:/net/per900a/raid0/plsang/usr/bin:/net/per900a/raid0/plsang/usr.local/bin:$PATH
LD_LIBRARY_PATH=/net/per900a/raid0/plsang/usr.local/lib64:/net/per900a/raid0/plsang/software/ffmpeg-2.0/release-shared/lib:/net/per900a/raid0/plsang/software/gcc-4.8.1/release/lib:/net/per900a/raid0/plsang/software/boost_1_54_0/release/lib:/net/per900a/raid0/plsang/usr/lib:/net/per900a/raid0/plsang/software/opencv-2.4.6.1/release/lib:/net/per900a/raid0/plsang/usr.local/lib:/usr/local/lib:$LD_LIBRARY_PATH
export PATH
export LD_LIBRARY_PATH


if [ "$#" -ne 5 ]; then
  echo "Usage: $0 <szpat> <filetype> <threshold> <start_video> <end_video> " >&2
  echo "Example: $0 dev11 mpg 70 0 1 " >&2
  exit 1
fi

count=0
indir=/net/per610a/export/das11f/ledduy/mediaeval-vsd-2013/video-rsz
outdir=/net/per610a/export/das11f/ledduy/mediaeval-vsd-2013/SBfiles/segmentation-rsz

for f in `ls /net/per610a/export/das11f/ledduy/mediaeval-vsd-2013/video/$1/*.$2`
do 
	if [ "$count" -ge $4 ] && [ "$count" -lt $5 ]; then
		echo $count
		fp="${f%}" 		#get file path
		fn="${fp##*/}"	#get file name with extension
		vid="${fn%.*}"	#get file name without extension (video ID)
		of="${vid}.txt" #output file name
		outputfile=$outdir/SbInfo_$3/$1/$of
		if [ -f $outputfile ]; then
			echo "file $of already exist!"
			let count=$count+1;
			continue;
		fi
		echo "processing video $fn"
		if [ ! -d $outdir/SbInfo_$3/$1 ]; then
		   mkdir -p $outdir/SbInfo_$3/$1
		fi
		./visualrhythm $3 0 0 $indir/$1 $fn $outputfile
	fi
	let count=$count+1;
	
done

