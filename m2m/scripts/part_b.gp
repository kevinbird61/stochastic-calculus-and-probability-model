#!/usr/bin/gnuplot
# Define 
set macros
INPUT="output/part_b.output"
# Get variables from input data 
PREAM=system("head -1 ".INPUT." | awk '{print $2}'")            # preamable (start)
DEVICE=system("head -1 ".INPUT." | awk '{print $3}'")           # number of devices
SIM=system("head -1 ".INPUT." | awk '{print $4}'")              # simulation times
RANGE=system("head -1 ".INPUT." | awk '{print $5}'")            # range of preamble
INT=system("head -1 ".INPUT." | awk '{print $6}'")              # interval

set title "Random Access Successful Probability"
set xlabel "Number of Preambles"
set ylabel "Successful Probability"
set terminal png font " Times_New_Roman,12 "
set output sprintf('image/part_b_%s_%s_%s_%s_%s.png',SIM,DEVICE,PREAM,RANGE,INT) 

set label 11 center at graph 0.5,-0.3 ,char 1 font ",14"
set bmargin 6
# Set figure caption 
set label 11 "Figure, Simulation time=".SIM.",Number of Devices=".DEVICE."\nNumber of Preamble=".PREAM.", interval=".INT 

# Set xtic & xlabel
set xtics rotate by 45 right
set key right bottom

# Plot
plot \
INPUT using 1:2 with linespoints linewidth 2 lt rgb "#FF0000" title "Simulation",\
INPUT using 1:3 with linespoints linewidth 2 lt rgb "#0000FF" title "Mathematic"