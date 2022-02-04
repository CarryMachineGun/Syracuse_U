#===========================================
# Makefile for Task-2
# Author: Endadul Hoque <enhoque@syr.edu>
#===========================================

.PHONY: clean

PROG = prog
SRC = foo.c
THINGS_TO_REMOVE = *.log *.out $(PROG)
EX = sample.ex
OUT = test.out

#==================================#

all: build 

build: $(PROG)
	@echo "Building ... done"

$(PROG): $(SRC)
	gcc -Werror -Wall -o $@ $<

test: clean build $(EX)
	@echo "Running and checking the result"
	@./$(PROG) > $(OUT) 2>&1 && \
	  ( diff -u $(OUT) $(EX) && \
	  echo "Test (output-file: $(OUT), expected-outcome: $(EX)): Passed" || \
	  echo "Test (output-file: $(OUT), expected-outcome: $(EX)): Failed. Check '$(OUT)' and '$(EX)'" )

clean:
	rm -f $(THINGS_TO_REMOVE)
