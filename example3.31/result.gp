set title "Example 3.31"
set xlabel "Testcase(steps)"
set ylabel "Probability"
set terminal png font " Times_New_Roman,12 "
set output "example3_31.png"

# Set xtic & xlabel
MAX="`head -1 simulation.output | awk '{print $4}'`"
set xtic 1,1,MAX
set xtics rotate by 45 right
set key right

# Plot
plot \
"simulation.output" using 1:2 with linespoints linewidth 2 lt rgb "#FF0000" title "simulation(Example 2.5)", \
"mathematic.output" using 1:2 with linespoints linewidth 2 lt rgb "#0000FF" title "mathematic(Example 2.5)", \
"mathematic_3_31.output" using 1:2 with linespoints linewidth 2 lt rgb "#00FF00" title "mathematic(Example 3.31)"