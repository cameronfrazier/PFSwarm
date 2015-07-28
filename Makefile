CC=g++
SRCDIR=./src/
INCDIR=./include/
LIST=simulation.cpp pfswarm.cpp psp.cpp satellite.cpp state.cpp
SOURCES=$(addprefix $(SRCDIR), $(LIST))
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=simulation

CFLAGS=-c -Wall $(addprefix -I, $(INCDIR))
LDFLAGS=

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o: 
	$(CC) $(CFLAGS) $< -o $@