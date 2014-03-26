CC = g++

SRC = src
INC = include
CPPFLAGS = -g -Wall
TESTFLAGS = -I/usr/include/cppunit
TESTLDFLAGS = -lcppunit -ldl
LIB = -pthread -lm
OBJ = obj
BIN = bin
DEBUG = -DDEBUG

TESTOBJ = test-obj
TESTSRC = test

MAKEDEPEND = $(CC) -M $(CPPFLAGS) -I$(INC) -o $*.d $<
SOURCES = $(wildcard $(SRC)/*.cc)
OBJECTS = $(patsubst %.cc,$(OBJ)/%.o,$(notdir $(wildcard $(SRC)/*.cc)))
DOBJECTS = $(patsubst %.o, %.od, $(OBJECTS))
TESTSOURCES = $(wildcard $(TESTSRC)/test-*.cc)
TESTOBJECTS = $(patsubst %.cc,$(TESTOBJ)/%.o,$(notdir $(wildcard $(TESTSRC)/test-*.cc)))
TARGET = rover

all: $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) $(LIB) -o $(BIN)/$(TARGET)

debug: $(DOBJECTS)
	$(CC) $(CPPFLAGS) $(DOBJECTS) $(LIB) -o $(BIN)/$(TARGET)

run: all
	$(BIN)/$(TARGET)

$(OBJ)/%.o : %.cc
	$(MAKEDEPEND);
	@rm -f *.d
	$(CC) -c $(CPPFLAGS) -I$(INC) -o $@ $<

$(OBJ)/%.od : %.cc
	$(MAKEDEPEND);
	@rm -f *.d
	$(CC) -c $(CPPFLAGS) $(DEBUG) -I$(INC) -o $@ $<

test-debug: $(DOBJECTS) $(TESTOBJECTS) $(TESTOBJ)/test-main.o
	$(CC) $(CPPFLAGS) $(TESTOBJ)/*.o $(filter-out $(OBJ)/main.od, $(DOBJECTS)) $(LDFLAGS) $(LIB) $(TESTLDFLAGS) -o $(TESTOBJ)/tests
	$(TESTOBJ)/tests

test: $(OBJECTS) $(TESTOBJECTS) $(TESTOBJ)/test-main.o
	$(CC) $(CPPFLAGS) $(TESTOBJ)/*.o $(filter-out $(OBJ)/main.o, $(OBJECTS)) $(LDFLAGS) $(LIB) $(TESTLDFLAGS) -o $(TESTOBJ)/tests
	$(TESTOBJ)/tests

$(TESTOBJ)/test-main.o: $(TESTSRC)/test-main.cc
	$(CC) $(CPPFLAGS) $(TESTFLAGS) -c $< -o $(TESTOBJ)/test-main.o

$(TESTOBJ)/%.o: $(TESTSRC)/%.cc
	$(CC) $(CPPFLAGS) -I$(INC) $(TESTFLAGS) -c $< -o $@



vpath %.cc $(SRC)

doc:
	@doxygen doc/Doxyfile

.PHONY: doc

clean: clean-test
	@rm -f *.d $(OBJ)/*.o $(OBJ)/*.od *.bak *~ *% $(BIN)/$(TARGET) $(INC)/*.gch 

clean-test:
	@rm -f $(TESTOBJ)/*o

.PHONY: rebuild
rebuild: clean all

.PHONY: rebuild-test
rebuild-test: clean test

.PHONY: rebuild-debug
rebuild-debug: clean debug

.PHONY: rebuild-test-debug
rebuild-test-debug: clean test-debug

