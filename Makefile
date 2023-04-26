CC = gcc
CPP = g++
CFLAGS = -Wall -Wextra -std=c11
CPPFLAGS = -Wall -Wextra -std=c++11
LDLIBS = -lm
# LDFLAGS = -L./library -I./library

CODEDIR = code
OUTDIR = out

SRCS=$(wildcard code/Q0*.c)
BINS=$(patsubst code/Q0%.c, $(OUTDIR)/%, $(SRCS))

SRCPP=$(wildcard code/Q0*.cpp)
BINPP=$(patsubst code/Q0%.cpp, $(OUTDIR)/%p, $(SRCPP))

.PHONY: all clean

all: $(BINS) $(BINPP)

# $(BINS): $(SRCS) | $(OUTDIR)
$(BINS): $(OUTDIR)/% : $(CODEDIR)/Q0%.c | $(OUTDIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

$(BINPP): $(OUTDIR)/%p : $(CODEDIR)/Q0%.cpp | $(OUTDIR)
	$(CPP) $(CPPFLAGS) $< -o $@ $(LDLIBS)

%: $(CODEDIR)/Q0%.c | $(OUTDIR)
	$(CC) $(CFLAGS) $< -o $(OUTDIR)/$@ $(LDLIBS)

%p: $(CODEDIR)/Q0%.cpp | $(OUTDIR)
	$(CPP) $(CPPFLAGS) $< -o $(OUTDIR)/$@ $(LDLIBS)

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
	mkdir $(OUTDIR)
