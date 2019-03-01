PROG = wf
PROGT = wf_tree
HDR = dict.h reader.h
OBJ = dict.o dict_tree.o reader.o
MAIN = wf.c

CFLAGS += -Wall -g

all: $(PROG) $(PROGT)

$(PROG): $(OBJ) $(MAIN)
	$(CC) $(CFLAGS) -DVAR=dictionary_create -o $@ $^

$(PROGT): $(OBJ) $(MAIN)
	$(CC) $(CFLAGS) -DVAR=dictionary_create_tree -o $@ $^



$(OBJ): $(HDR)
$(MAIN): $(HDR)

clean:
	$(RM) $(OBJ) $(PROG) $(PROGT)
