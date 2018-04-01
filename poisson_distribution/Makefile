EXEC_A:=part_a.out
EXEC_B:=part_b.out
PLOT_A:=part_a.png
PLOT_B:=part_b.png
OBJS:=../utils/poisson.o ../utils/parse_arg.o ../utils/rand_gen.o ../utils/event.o
OBJS_A:=part_a.o $(OBJS)
OBJS_B:=part_b.o $(OBJS)
OBJDIR:=output image
CXX=g++
CXXFLAGS:=-std=c++14

astyle:
	astyle --style=google --indent=spaces=2 *.cc

run: $(OBJDIR) all
	# running program to generate
	./$(EXEC_A) -k 20 -s 100000
	./$(EXEC_B) -k 20 -s 100000

all: part_a part_b

part_a: $(OBJS_A)
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC_A)

part_b: $(OBJS_B)
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC_B)

%.o: %.c %.h
	$(CXX) $(CXXFLAGS) -c $^

plot_a: part_a
	gnuplot scripts/result_a.gp

plot_a_sim: part_a
	gnuplot scripts/result_a_sim.gp

plot_b: part_b
	gnuplot scripts/result_b.gp

plot_b_sim: part_b 
	gnuplot scripts/result_b_sim.gp

plot: plot_a plot_b plot_a_sim plot_b_sim

$(OBJDIR):
	mkdir -p $@

clean:
	rm $(OBJS_A) $(OBJS_B) $(EXEC_A) $(EXEC_B)

clean_plot:
	rm $(PLOT_A) $(PLOT_B)