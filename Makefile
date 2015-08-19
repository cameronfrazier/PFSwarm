CC=g++
SRCDIR=./src/
INCDIR=./include/
LIST=swarmsettings.cpp pfswarm.cpp psp.cpp satellite.cpp state.cpp forcefunctions.cpp simulation.cpp 
SOURCES=$(addprefix $(SRCDIR), $(LIST))
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=simulation

CFLAGS=-c -Wall $(addprefix -I, $(INCDIR)) -std=c++11
LDFLAGS=

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -std=c++11

.cpp.o: 
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -f $(EXECUTABLE) *.o