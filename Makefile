CC=g++
PROGRAM=calc
FLAGS=-Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -std=c++20 -g 
.PHONY: compile clean
all: clean compile

compile: $(PROGRAM).cpp
	$(CC) $(FLAGS) -o $(PROGRAM) $(PROGRAM).cpp

clean:
	rm -rf $(PROGRAM)
	rm -rf $(PROGRAM).dSYM 
