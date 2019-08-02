# the compiler: gcc for C program, define as g++ for C++
CC = gcc
CXX = g++

# Compiler flags:
CFLAGS = -std=c++14 -lpthread

# the build
SMART_PTR 		= SmartPointer
UNIQUE_PTR 		= unique_ptr
SHARED_PTR 		= shared_ptr

all: $(UNIQUE_PTR) $(SHARED_PTR) $(SMART_PTR)

$(SMART_PTR): $(SMART_PTR).cpp
	$(CXX) $(SMART_PTR).cpp $(CFLAGS) -o $(SMART_PTR)

$(UNIQUE_PTR): $(UNIQUE_PTR).cpp
	$(CXX) $(UNIQUE_PTR).cpp $(CFLAGS) -o $(UNIQUE_PTR)
	
$(SHARED_PTR):
	$(CXX) $(SHARED_PTR).cpp $(CFLAGS) -o $(SHARED_PTR) 

clean:
	$(RM) $(UNIQUE_PTR) $(SHARED_PTR) $(SMART_PTR)


