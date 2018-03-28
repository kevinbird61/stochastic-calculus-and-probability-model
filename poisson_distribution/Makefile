EXEC_A:=part_a.out
EXEC_B:=part_b.out
PLOT_A:=part_a.png
PLOT_B:=part_b.png
OBJS:=../utils/poisson.o ../utils/parse_arg.o
OBJS_A:=part_a.o $(OBJS)
OBJS_B:=part_b.o $(OBJS)
CXX=g++
CXXFLAGS:=-std=c++14

run: all
	# running program to generate
	./$(EXEC_A) -k 40

all: part_a part_b

part_a: $(OBJS_A)
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC_A)

part_b: $(OBJS_B)
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC_B)

%.o: %.c %.h
	$(CXX) $(CXXFLAGS) -c $^

plot_a: part_a
	gnuplot result.gp

plot: plot_a 

clean:
	rm $(OBJS_A) $(OBJS_B) $(EXEC_A) $(EXEC_B)

clean_plot:
	rm $(PLOT_A) $(PLOT_B)