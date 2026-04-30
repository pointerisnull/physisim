CXX := g++
CXXFLAGS := -std=c++11 -Wall --static

LIBS := -L/usr/local/lib /usr/local/lib/libSDL2.a -lm -lpthread -lrt
INCLUDES := -I include

SRCS := $(wildcard src/core/*.cpp src/physics/*.cpp src/physics/*.c src/lang/*.cpp src/lang/*.c lib/glad/src/glad.c) src/main.cpp 
OBJS := $(SRCS:.cpp=.o)
EXEC := a.out

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(INCLUDES) -o $@ $(LIBS)

clean:
	rm -f src/*.o src/core/*.o src/lang/*.o src/physics/*.o a.out
