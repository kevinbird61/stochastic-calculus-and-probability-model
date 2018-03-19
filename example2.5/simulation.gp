set title "Example 2.5 simulation"
set xlabel "Testcase"
set ylabel "Percentage"
set terminal png font " Times_New_Roman,12 "
set output "simulation.png"

# Get variable
MAX="`head -1 simulation.output | awk '{print $4}'`"
set xtic 1,1,MAX
set key right

# Plot
plot \
"simulation.output" using 1:2 with linespoints linewidth 2 lt rgb "#FF0000" title "simulation", \
"mathematic.output" using 1:2 with linespoints linewidth 2 lt rgb "#00FF00" title "mathematic"