#/bin/sh
echo `./waf --run "scratch/BFHP --numberOfUes=200 --traceFile='scratch/RW_n200t2500.ns_movements'" > ./result/fig1/RW_n200`
echo `./waf --run "scratch/BFHP --numberOfUes=400 --traceFile='scratch/RW_n400t2500.ns_movements'" > ./result/fig1/RW_n400`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --traceFile='scratch/RW_n600t2500.ns_movements'" > ./result/fig1/RW_n600`
echo `./waf --run "scratch/BFHP --numberOfUes=800 --traceFile='scratch/RW_n800t2500.ns_movements'" > ./result/fig1/RW_n800`
echo `./waf --run "scratch/BFHP --numberOfUes=1000 --traceFile='scratch/RW_n1000t2500.ns_movements'" > ./result/fig1/RW_n1000`
echo `./waf --run "scratch/BFHP --numberOfUes=200 --traceFile='scratch/GM_n200.ns_movements'" > ./result/fig1/GM_n200`
echo `./waf --run "scratch/BFHP --numberOfUes=400 --traceFile='scratch/GM_n400.ns_movements'" > ./result/fig1/GM_n400`
echo `./waf --run "scratch/BFHP --numberOfUes=600 --traceFile='scratch/GM_n600.ns_movements'" > ./result/fig1/GM_n600`
echo `./waf --run "scratch/BFHP --numberOfUes=800 --traceFile='scratch/GM_n800.ns_movements'" > ./result/fig1/GM_n800`
echo `./waf --run "scratch/BFHP --numberOfUes=1000 --traceFile='scratch/GM_n1000.ns_movements'" > ./result/fig1/GM_n1000`