#!/usr/bin/gnuplot

set title "Poisson Distribution - Merge Part"
set xlabel "k"
set ylabel "Probability: P(X+Y=k)"
set terminal png font " Times_New_Roman,12 "
set output "image/part_a.png"

# Set xtic & xlabel
set xtics rotate by 45 right
set key right

# Plot
plot \
"output/part_a.output" using 1:2 with linespoints linewidth 2 lt rgb "#FF0000" title "P(X+Y)", \
"output/part_a.output" using 1:3 with linespoints linewidth 2 lt rgb "#0000FF" title "P(X)*P(Y)"