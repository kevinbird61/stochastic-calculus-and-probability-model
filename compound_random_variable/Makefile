example3_8:=example3_8.out
OBJS:=../utils/parse_arg.o ../utils/rand_gen.o
OBJS_3_8:=example3_8.o
OBJDIR:=output image
CXX=g++
CXXFLAGS:=-std=c++14

.DEFAULT_GOAL:=all

astyle:
	astyle --style=google --indent=spaces=2 *.cc

all: $(OBJDIR) example3_8

run: all

example3_8: $(OBJS_3_8) $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $(example3_8)

%.o: %.c %.h
	$(CXX) $(CXXFLAGS) -c $^

$(OBJDIR):
	mkdir -p $@

clean:
	rm *.o $(OBJS)