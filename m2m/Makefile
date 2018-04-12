EXEC_A:=part_a.out
EXEC_B:=part_b.out
OBJS:=../utils/parse_arg.o ../utils/rand_gen.o ../utils/event.o
OBJS_A:=part_a.o $(OBJS)
OBJS_B:=part_b.o $(OBJS)
OBJDIR:=output image
CXX=g++
CXXFLAGS:=-std=c++14

.DEFAULT_GOAL:=all

astyle:
	astyle --style=google --indent=spaces=2 *.cc

all: $(OBJDIR) part_a part_b

plot: 

part_a: $(OBJS_A)
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC_A)

part_b: $(OBJS_B)
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC_B)

%.o: %.c %.h
	$(CXX) $(CXXFLAGS) -c $^

$(OBJDIR):
	mkdir -p $@

clean:
	rm $(OBJS_A) $(OBJS_B) $(EXEC_A) $(EXEC_B)