#!/usr/bin/gnuplot
# Define 
set macros
INPUT="output/part_a_sim.output"
# Get variables from input data 
SIM_TIME=system("head -1 ".INPUT." | awk '{print $2}'")
L1=system("head -1 ".INPUT." | awk '{print $3}'")
L2=system("head -1 ".INPUT." | awk '{print $4}'")
SLOT=system("head -1 ".INPUT." | awk '{print $5}'")
COUNT=system("head -1 ".INPUT." | awk '{print $6}'")
COUNT_X=system("head -1 ".INPUT." | awk '{print $7}'")
COUNT_Y=system("head -1 ".INPUT." | awk '{print $8}'")

set title "Poisson Distribution - Merge Part (Simulation)"
set xlabel "k"
set ylabel "Probability: P(k)"
set terminal png font " Times_New_Roman,12 "
set output sprintf('image/part_a_sim_%s_%s_%s.png', SIM_TIME, L1, L2) 

set label 11 center at graph 0.5,-0.25 ,char 1 font ",14"
set bmargin 6
# Set figure caption 
set label 11 "Figure, Simulation time=".SIM_TIME."\n {/Symbol l}_1=".L1.", {/Symbol l}_2=".L2.", duration slot=".SLOT

# Set xtic & xlabel
set xtics rotate by 45 right
set key right

# Plot
plot \
INPUT using 1:2 with linespoints linewidth 2 lt rgb "#FF0000" title "Sim - P(X+Y)",\
INPUT using 1:3 with linespoints linewidth 2 lt rgb "#0000FF" title "Sim - P(X)*P(Y)"