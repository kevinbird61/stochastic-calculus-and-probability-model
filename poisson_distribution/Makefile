EXEC_A:=part_a.out
EXEC_B:=part_b.out
OBJS:=../utils/poisson.o ../utils/parse_arg.o
OBJS_A:=part_a.o $(OBJS)
OBJS_B:=part_b.o $(OBJS)
CXX=g++
CXXFLAGS:=-std=c++14

all: part_a part_b

part_a: $(OBJS_A)
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC_A)

part_b: $(OBJS_B)
	$(CXX) $(CXXFLAGS) $^ -o $(EXEC_B)

%.o: %.c %.h
	$(CXX) $(CXXFLAGS) -c $^

clean:
	rm $(OBJS_A) $(OBJS_B) $(EXEC_A) $(EXEC_B)