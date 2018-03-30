set title "Poisson Distribution - Merge Part (Simulation)"
set xlabel "k"
set ylabel "Probability: P(k)"
set terminal png font " Times_New_Roman,12 "
set output "part_a_sim.png"

# Set xtic & xlabel
set xtics rotate by 45 right
set key right

# Plot
plot \
"output/part_a_sim.output" using 1:2 with linespoints linewidth 2 lt rgb "#FF00FF" title "Sim - P(X+Y)"