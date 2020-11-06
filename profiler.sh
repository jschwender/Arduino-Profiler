#!/bin/bash
#  File preparation for visual representation of runtime of commands on AVR controller
#  Run the Code on the Arduino with Serial Monitor. After sime time you will have lots of lines in the Monitor.
#  Mark them all, Copy and Paste them into a cvs file. This bash script here processes the numbers
#  using datamash to create a file, which is plotted with GNUplot.
#  
#
export LC_ALL=C

prep_csv2() {
    sed -e "s/;/\t/g" -e "/^$/d" "$1"|datamash --sort groupby 4 mean 3 min 3 max 3 range 3 sstdev 3 count 3 |sort -t "	" -n -k 2 |grep -v "dummy" > "$2"
}

xsort() {
    rm -f  "$2"
    i=1
    while read XXX
    do
    YYY=$(echo $XXX|sed "s/*/\\\*/g")
#    echo $YYY
        grep  "^$YYY"$'\t' "$1" >> "$2"   || echo "$XXX"
    #    echo "$i"
        i=$(( i+1 ))
    done <cmdorder
}

prep_csv2 Arduino-1.csv Arduino-1.result 
prep_csv2 Arduino-2.csv Arduino-2.res
prep_csv2 Arduino-3.csv Arduino-3.res

awk -F"	" '{printf"%s\t\n", $1}' Arduino-1.result > cmdorder

xsort Arduino-2.res Arduino-2.result
xsort Arduino-3.res Arduino-3.result

#rm -f cmdorder

gnuplot ArduinosProfiler.gnuplot

