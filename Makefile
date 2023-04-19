CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDLIBS = -lm
# LDFLAGS = -L./library -I./library

CODEDIR = code
OUTDIR = out

SRCS=$(wildcard code/Q0*.c)
BINS=$(patsubst code/Q0%.c, $(OUTDIR)/%, $(SRCS))
FILE=

.PHONY: all clean

all: $(BINS)

# $(BINS): $(SRCS) | $(OUTDIR)
$(BINS): $(OUTDIR)/% : $(CODEDIR)/Q0%.c | $(OUTDIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

%: $(CODEDIR)/Q0%.c | $(OUTDIR)
	$(CC) $(CFLAGS) $< -o $(OUTDIR)/$@ $(LDLIBS)

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean:
	rm -rf $(OUTDIR)
