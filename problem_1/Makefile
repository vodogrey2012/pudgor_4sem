PROG = wf
PROGT = wf_tree
TESTS = dict_gtest
HDR = dict.h reader.h
OBJ = dict.o dict_tree.o reader.o
MAIN = wf.c
GMAIN = dict_gtest.cpp
GOBJ_TREE = dict_tree.o dict_gtest.o

GMAIN = d
GTEST_DIR = /home/yauheni/programs/googletest/googletest
GTEST_LIB_DIR = /home/yauheni/programs/googletest/gtest/lib
USER_DIR = .
CPPFLAGS += -isystem $(GTEST_DIR)/include
GTEST_LIBS = libgtest.a libgtest_main.a
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11


CFLAGS += -Wall -g

all: $(PROG) $(PROGT) $(GTEST_LIBS) $(TESTS)

clean:
	$(RM) $(OBJ) $(PROG) $(PROGT) $(GTEST_LIBS) $(TESTS) *.o

$(PROG): $(OBJ) $(MAIN)
	$(CC) $(CFLAGS) -DVAR=dictionary_create -o $@ $^

$(PROGT): $(OBJ) $(MAIN)
	$(CC) $(CFLAGS) -DVAR=dictionary_create_tree -o $@ $^

$(OBJ): $(HDR)
$(MAIN): $(HDR)


gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
		$(GTEST_DIR)/src/gtest_main.cc

libgtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

libgtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

dict_gtest.o : $(USER_DIR)/dict_gtest.cpp \
                     $(USER_DIR)/dict.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/dict_gtest.cpp

$(TESTS) : $(GOBJ) $(GTEST_LIBS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -L$(GTEST_LIB_DIR) -lgtest_main -lpthread $^ -o $@


