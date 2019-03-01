PROG = wf
PROGT = wf_tree
HDR = obj_dict.h obj_reader.h
OBJ = obj_dict.o obj_dict_tree.o obj_reader.o
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
