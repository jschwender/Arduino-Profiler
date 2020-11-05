# Arduino-Profiler
Analysis of command runtime is important.

Run a program on the Arduino while serial monitor running.
Wait until enough data is collected, you should have more than one run
in order to detect properly the full range of variations in runtime.
It may take some hours to collect some hundret runs.

Copy the contenct of the monitor window into a file.

Run the shell script "profiler.sh" in order to process the data.
Datamash is used to get statistic results into another result file.
This result file is plotted using gnuplot.

It provides an overview of some selected commands of the Arduino,
and the runtime is compared to data from another Arduino hardware.

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
