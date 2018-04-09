#!/usr/bin/gnuplot
# Define 
set macros 
INPUT_X="output/part_b_sim_X.output"
INPUT_LX="output/part_b_sim_LX.output"

SIM_TIME=system("head -1 ".INPUT_X." | awk '{print $2}'")
L=system("head -1 ".INPUT_X." | awk '{print $3}'")
SLOT=system("head -1 ".INPUT_X." | awk '{print $4}'")
P=system("head -1 ".INPUT_X." | awk '{print $5}'")

set title "Poisson Distribution - Split Part (Simulation, Part of X)"
set xlabel "k"
set ylabel "Probability: P(k)"
set terminal png font " Times_New_Roman,12 "
set output sprintf('image/part_b_sim_X_%s_%s_%s.png',SIM_TIME,L,P) 

set label 11 center at graph 0.5,-0.25 ,char 1 font ",14"
set bmargin 6
# Set figure caption 
set label 11 "Figure, Simulation time=".SIM_TIME."\n {/Symbol l}=".L.", duration slot=".SLOT

# Set xtic & xlabel
set xtics rotate by 45 right
set key right

# Plot
plot \
INPUT_X using 1:2 with linespoints linewidth 2 lt rgb "#FF0000" title "X (derive from N)",\
INPUT_LX using 1:2 with linespoints linewidth 2 lt rgb "#0000FF" title "X (independent poisson)"