SRC=toyshell.c
PROG=shell

.PHONY: clean

all: $(PROG)

$(PROG): $(SRC)
	gcc -o $@ $<

clean:
	@rm -f $(PROG)
