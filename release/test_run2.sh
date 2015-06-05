export LD_LIBRARY_PATH=/net/per900b/raid0/ledduy/usr.local/lib:/net/per900a/raid0/plsang/usr.local/lib:/usr/local/lib:$LD_LIBRARY_PATH

if [ "$#" -ne 3 ]; then
  echo "Usage: $0 <threshhold> <method> <videoid> (e.g. HVC1079...) " >&2
  exit 1
fi

./visualrhythm $1 $2 0 /net/per900a/raid0/plsang/resources/MED10_Resized $3.mp4 $3.txt
