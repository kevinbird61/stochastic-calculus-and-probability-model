all:
	# compile the simulation
	g++ simulation.cc -o sim.out -I../utils -std=c++11
	# compile the mathematic proof
	g++ mathematic.cc -o math.out -std=c++11 
	# Feed the testdata
	# Run the simulation first: 
	./sim.out -m 5 -x 10 
	# generate with large testcase
	#./sim.out -m 5 -x 10 -n 10^6
	# And then get the maximum, to generate the mathematic result
	./math.out 10 $$(head -1 simulation.output | awk '{print $$4}')
	# Using gnuplot the plot
	gnuplot simulation.gp