set title "Poisson Distribution - Split Part"
set xlabel "k"
set ylabel "Probability"
set terminal png font " Times_New_Roman,12 "
set output "image/part_b.png"

# Set xtic & xlabel
set xtics rotate by 45 right
set key right

# Plot
plot \
"output/part_b.output" using 1:2 with linespoints linewidth 2 lt rgb "#FF0000" title "P(k)", \
"output/part_b.output" using 1:3 with linespoints linewidth 2 lt rgb "#0000FF" title "P(k1)*P(k2)", \
"output/part_b.output" using 1:4 with linespoints linewidth 2 lt rgb "#00FF00" title "P(k1), k1=k*p", \
"output/part_b.output" using 1:5 with linespoints linewidth 2 lt rgb "#FF00FF" title "P(k2), k2=k*(1-p)"
