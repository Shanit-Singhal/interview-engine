CC = g++
CFLAGS = -std=c++17 -Wall

SRCS = interview_engine.cpp question_database.cpp performance_tracker.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = interview_engine
TEST_SRC = test_interview_engine.cpp
TEST_OBJS = question_database.o performance_tracker.o
TEST_EXEC = test_interview_engine

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRC) $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_SRC) $(TEST_OBJS)

clean:
	rm -f $(OBJS) $(EXEC) $(TEST_EXEC) test_questions.txt

.PHONY: all test clean