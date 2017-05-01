#/bin/sh
nodeNum=400
xRange=5000
yRange=5000
duration=3600
cutTime=1000
walkTime=1250
repeatTime=5

fileName="./results/RW_n"$nodeNum"t"$walkTime
for((i=0; i<repeatTime; i=i+1))
do
    outputFile=$fileName"_"$i
    echo `./bin/bm -f $outputFile RandomWalk -n $nodeNum -x $xRange -y $yRange -d $duration -i $cutTime -t $walkTime`
    echo `./bin/bm NSFile -f $outputFile`
done
