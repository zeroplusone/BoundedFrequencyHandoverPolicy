#/bin/sh
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=100 --numberOfEnbs=1 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi25lte25`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=200 --numberOfEnbs=1 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi50lte25`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=300 --numberOfEnbs=1 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi75lte25`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=400 --numberOfEnbs=1 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi100lte25`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=100 --numberOfEnbs=2 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi25lte50`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=200 --numberOfEnbs=2 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi50lte50`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=300 --numberOfEnbs=2 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi75lte50`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=400 --numberOfEnbs=2 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi100lte50`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=100 --numberOfEnbs=3 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi25lte75`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=200 --numberOfEnbs=3 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi50lte75`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=300 --numberOfEnbs=3 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi75lte75`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=400 --numberOfEnbs=3 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi100lte75`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=100 --numberOfEnbs=4 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi25lte100`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=200 --numberOfEnbs=4 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi50lte100`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=300 --numberOfEnbs=4 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi75lte100`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --numberOfWifi=400 --numberOfEnbs=4 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig2/wifi100lte100`
