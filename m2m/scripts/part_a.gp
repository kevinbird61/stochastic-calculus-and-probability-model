#!/usr/bin/gnuplot
# Define 
set macros
INPUT="output/part_a.output"
# Get variables from input data 
SIM=system("head -1 ".INPUT." | awk '{print $2}'")          # simulation times
DEVICE=system("head -1 ".INPUT." | awk '{print $3}'")       # number of devices
PROB=system("head -1 ".INPUT." | awk '{print $4}'")         # probability
UB=system("head -1 ".INPUT." | awk '{print $5}'")           # upperbound
INT=system("head -1 ".INPUT." | awk '{print $6}'")          # interval

set title "Access Class Barring"
set xlabel "Probability (threshold)"
set ylabel "Average access delay"
set terminal png font " Times_New_Roman,12 "
set output sprintf('image/part_a_%s_%s_%s.png', SIM, DEVICE, PROB) 

set label 11 center at graph 0.5,-0.3 ,char 1 font ",14"
set bmargin 6
# Set figure caption 
set label 11 "Figure, Simulation time=".SIM."\nNumber of Devices=".DEVICE.", interval=".INT 

# Set xtic & xlabel
set xtics rotate by 45 right
set key right

# Plot
plot \
INPUT using 1:2 with linespoints linewidth 2 lt rgb "#FF0000" title "Simulation",\
INPUT using 1:3 with linespoints linewidth 2 lt rgb "#0000FF" title "Mathematic"