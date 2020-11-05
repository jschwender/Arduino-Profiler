# ©2020-10-04, J. Schwender
#
# Gnuplot Skript zur Visualisierung von Laufzeitunterschieden zweier Arduino Typen.
#
Title1="Micro"    ## you may adjust the titles here
Title2="Due"
#
set datafile separator "\t"
#
set xtics 
set grid xtics ytics mytics
set style fill solid
set xtics rotate by 90 right
set terminal png
set terminal png size 1000,800

set output 'ArduinosProfile.png'
set title "Runtime of commands AVR(Micro) vs. SAM3(Due)"
set ylabel "runtime in µs"
set logscale y
set key left top
set yrange [0.1:300]
#  text  mean  min   max   range   stddev   count
#   1     2     3     4      5        6       7
plot 'Arduino-1.result'  using 0:2:3:4:xticlabels(1) with yerr linecolor "red"  linewidth 2 title Title1, \
     'Arduino-2.result'  using 0:2:3:4               with yerr linecolor "blue" linewidth 2 title Title2


