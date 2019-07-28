# the compiler: gcc for C program, define as g++ for C++
CC = gcc
CXX = g++

# Compiler flags:
CFLAGS = -std=c++11 -lpthread

# the build target
TARGET 		= ExternalSorting
FMAN 		= FileMan
MEMINFO 	= MemoryManual

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(TARGET).cpp $(CFLAGS) -o $(TARGET)

fileman:
	$(CXX) $(FMAN).cpp $(CFLAGS) -o $(FMAN) 

meminfo:
	$(CXX) $(MEMINFO).cpp $(CFLAGS) -o $(MEMINFO)

clean:
	$(RM) $(TARGET) $(FMAN) $(MEMINFO)

clear:
	$(RM) input.txt.* output.*

