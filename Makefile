CC = gcc
CXX = g++
DEBUG = -ggdb
LFLAGS = -Wall -Werror
IDIR = include/vicpad
INC = -I $(IDIR)
CFLAGS = $(LFLAGS) $(DEBUG) -c
CXXFLAGS = $(LFLAGS) $(DEBUG) $(INC) -c -std=c++11
LDFLAGS = -lncurses
SRCDIR = src
BINDIR = bin
BDIR = build

_DEPS = app.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = app.o
OBJ = $(patsubst %,$(BDIR)/%,$(_OBJ))

default: all

$(BDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(BDIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

	
all: $(OBJ)
	$(CXX) $(LFLAGS) $(DEBUG) -std=c++11 $(wildcard build/*) -o $(BINDIR)/vicpad $(LDFLAGS)
	
.PHONY: clean

clean:
	rm -f $(BINDIR)/vicpad $(BUILD)/*.o
