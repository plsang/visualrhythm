
for VAR in {1..86}
do
	echo "KILL $VAR"
	kill $(ps aux | grep '[v]isualrhythm' | awk '{print $2}')
        
done
