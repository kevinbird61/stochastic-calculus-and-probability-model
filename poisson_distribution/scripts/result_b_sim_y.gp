#!/usr/bin/gnuplot
# Define 
set macros 
INPUT_Y="output/part_b_sim_Y.output"
INPUT_LY="output/part_b_sim_LY.output"

SIM_TIME=system("head -1 ".INPUT_Y." | awk '{print $2}'")
L=system("head -1 ".INPUT_Y." | awk '{print $3}'")
SLOT=system("head -1 ".INPUT_Y." | awk '{print $4}'")
P=system("head -1 ".INPUT_Y." | awk '{print $5}'")

set title "Poisson Distribution - Split Part (Simulation, Part of Y)"
set xlabel "k"
set ylabel "Probability: P(k)"
set terminal png font " Times_New_Roman,12 "
set output sprintf('image/part_b_sim_Y_%s_%s_%s.png',SIM_TIME,L,P) 

set label 11 center at graph 0.5,-0.25 ,char 1 font ",14"
set bmargin 6
# Set figure caption 
set label 11 "Figure, Simulation time=".SIM_TIME."\n {/Symbol l}=".L.", duration slot=".SLOT

# Set xtic & xlabel
set xtics rotate by 45 right
set key right

# Plot
plot \
INPUT_Y using 1:2 with linespoints linewidth 2 lt rgb "#FF0000" title "Y (derive from N)",\
INPUT_LY using 1:2 with linespoints linewidth 2 lt rgb "#0000FF" title "Y (independent poisson)"