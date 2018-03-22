all:
	# compile the mathematic model
	g++ mathematic.cc -o math_3_31.out -I../utils -std=c++11
	# compile and run the simulation process in example-2.5 
	g++ ../example2.5/simulation.cc -o sim_2_5.out -I../utils -std=c++11
	# run simulation first
	./sim_2_5.out -m 5 -x 10 -n 1000000
	# run mathematic now
	./math_3_31.out -r 5 -m 30 > mathematic.output
	# then plot 
	gnuplot result.gp