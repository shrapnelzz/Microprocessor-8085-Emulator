IDIR = ./header
CC = clang++
CFLAGS=-I$(IDIR) -std=c++11

ODIR=object

LIBS=-lm

SRCS = $(wildcard core/*.cpp) $(wildcard instructions/*.cpp) $(wildcard utils/*.cpp)
OBJS = $(patsubst %.cpp,$(ODIR)/%.o,$(notdir $(SRCS)))

DEPS = $(IDIR)/MASTER.h

VPATH = core:instructions:utils

$(ODIR)/%.o: %.cpp $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

emulator: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ emulator
