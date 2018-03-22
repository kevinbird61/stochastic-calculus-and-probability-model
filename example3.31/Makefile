all:
	# compile the mathematic model
	g++ mathematic.cc -o math_3_31.out -I../utils -std=c++11
	# compile and run the simulation process in example-2.5 
	g++ ../example2.5/simulation.cc -o sim_2_5.out -I../utils -std=c++11
	# compile the mathematic model in example-2.5
	g++ ../example2.5/mathematic.cc -o math_2_5.out -std=c++11 
	# run simulation first
	./sim_2_5.out -m 5 -x 10 -n 1000000
	# And then get the maximum, to generate the mathematic result
	./math_2_5.out 10 $$(head -1 simulation.output | awk '{print $$4}')
	# run mathematic now
	./math_3_31.out -r 5 -m 30 > mathematic_3_31.output
	# then plot 
	gnuplot result.gp