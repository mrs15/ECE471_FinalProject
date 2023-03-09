SOURCES = ../ECE471_FinalV1.X/FSM_states.c
INCLUDE_FILES = ../ECE471_FinalV1.X/FSM_states.h

TEST_SOURCES := $(wildcard UnitTests/*.cpp)

GTEST_DIR=googletest
GTEST_INC=googletest/include
TARGET = gtest

tests: gtest

gtest:
	g++ -I$(GTEST_INC) -I$(GTEST_DIR) -c $(wildcard $(GTEST_DIR)/src/gtest-all.cc) -o gtest.o

gtest: $(INCLUDE_FILES)
	g++ -I$(GTEST_INC) $(TEST_SOURCES) $(SOURCES) $(INCLUDE_FILES) gtest.o

clean:
	$(RM) $(TARGET) 