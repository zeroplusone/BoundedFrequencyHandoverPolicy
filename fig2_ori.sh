#/bin/sh
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=100 --numberOfEnbs=1 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi25lte25`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=200 --numberOfEnbs=1 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi50lte25`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=300 --numberOfEnbs=1 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi75lte25`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=400 --numberOfEnbs=1 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi100lte25`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=100 --numberOfEnbs=2 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi25lte50`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=200 --numberOfEnbs=2 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi50lte50`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=300 --numberOfEnbs=2 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi75lte50`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=400 --numberOfEnbs=2 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi100lte50`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=100 --numberOfEnbs=3 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi25lte75`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=200 --numberOfEnbs=3 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi50lte75`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=300 --numberOfEnbs=3 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi75lte75`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=400 --numberOfEnbs=3 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi100lte75`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=100 --numberOfEnbs=4 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi25lte100`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=200 --numberOfEnbs=4 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi50lte100`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=300 --numberOfEnbs=4 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi75lte100`
echo `./waf --run "scratch/original --numberOfUes=600 --numberOfWifi=400 --numberOfEnbs=4 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/owifi100lte100`
