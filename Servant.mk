CXX = g++ -std=gnu++0x
CXXFLAGS = -Wall -g -D SERVANT_UNIT_TEST
INCLUDES = -I/usr/X11R6/include
LIBS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXi -lXext -lX11 -lm -lcrypto -lboost_serialization -lboost_thread -ldl -lpthread -lboost_system
OBJS = Servant.o
PROGRAM = Servant.out

all:$(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(INCLUDES) $(LIBS) -o $(PROGRAM)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) -c $<

.PHONY: clean
clean:
	rm -f *o $(PROGRAM)
