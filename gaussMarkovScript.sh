#/bin/sh
nodeNum=400
xRange=5000
yRange=5000
duration=3600
cutTime=1000
maxSpeed=3
speedStd=2
repeatTime=5

fileName="./results/GM_n"$nodeNum"t"$walkTime
for((i=0; i<repeatTime; i=i+1))
do
    outputFile=$fileName"_"$i
    echo `./bin/bm -f $outputFile GaussMarkov -n $nodeNum -x $xRange -y $yRange -d $duration -i $cutTime -h $maxSpeed -s $speedStd`
    echo `./bin/bm NSFile -f $outputFile`
done
