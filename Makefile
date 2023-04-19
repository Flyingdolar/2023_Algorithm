CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDLIBS = -lm
# LDFLAGS = -L./library -I./library

CODEDIR = code
OUTDIR = out

SRCS=$(wildcard code/Q0*.c)
BINS=$(patsubst code/Q0%.c, $(OUTDIR)/%, $(SRCS))
FILE=

.PHONY: all debug clean

all: $(BINS)

$(BINS): $(SRCS) | $(OUTDIR)
	$(CC) $(CFLAGS) $< -g -o $@ $(LDLIBS)

%: $(CODEDIR)/Q0%.c | $(OUTDIR)
	$(CC) $(CFLAGS) $< -g -o $(OUTDIR)/$@ $(LDLIBS)

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
