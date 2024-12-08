#gcc main.c data.c player.c display.c io.c raycast.c lib/glad/src/glad.c -I lib/glad/include -L/usr/local/lib /usr/local/lib/libSDL2.a -lm -lpthread -lrt -std=c99 
CXX := g++
CXXFLAGS := -std=c++11 -Wall --static

LIBS := -L/usr/local/lib /usr/local/lib/libSDL2.a -lm -lpthread -lrt
INCLUDES := -I include

SRCS := main.cpp engine.cpp display.cpp pmath.c object.cpp world.cpp collision.cpp lib/glad/src/glad.c lexer.c table.c token.c cono.c pscript.cpp
OBJS := $(SRCS:.cpp=.o)
EXEC := a.out

# make rule to compile C++ source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# make rule to link object files and create the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) $(INCLUDES) -o $@ $(LIBS)

# make rule to clean up generated files
clean:
	rm -f *.o a.out
