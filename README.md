# Arduino-Profiler
Analysis of command runtime may be important.

This profiler toolset alows you to analyze run time of commands on Arduino.

Requires: PC with Arduino-IDE, Adruino. datamash, gnuplot.

(Tested on Ubuntu 20.10 with Arduino Mini and Due.)

Howto:

Run the profiler program on the Arduino while serial monitor running.
Wait until enough data is collected, you should have more than one run
in order to detect properly the full range of variations in runtime.
It may take some hours to collect some hundret runs. You may comment
out commands you are not interested in or add new ones. Note that this profiler
consumes lot of memory, it may not work on every Arduino platform without
adaption.

Copy the content of the monitor window into a file named Arduino-1.csv,
or for a second platform you want to compare Arduino-2.csv.

Run the shell script "profiler.sh" in order to process the data.
Datamash is used to get statistic results into another result file.
This result file is then plotted using gnuplot. Result is a png file
with a graphic. Look in the examples folder.


Note:
The command Serial.print of the standard lib is very hard to measure,
al it spoils the monitor output and puts heavily load on the Arduino
connection to the PC, therefore this command is not testet.

Arduino Due has hardware-UARTs which seem not to be able to run
faster than 115200 bps. That makes this command much slower than
on ATmega32u4 for example.

Some commands like direct port access with "PORTB = …" do not work 
on Arduino Due, the measurement will return 0.

If you compare sets of runtime results, make sure that the 
scope of commands is equal.
