#variables
CXX = g++
CXXFLAGS = -std=c++20 -lstdc++ -static-libstdc++ -Wall -Wextra -O2 
SRC_DIR = DataStructures-Algorhitms
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.cpp)
#for every cpp file , create an object
OBJ = $(patsubst $(SRC_DIR)/%.cpp , (BUILD_DIR)/%.o , $(SRC))

#the executable
TARGET = $(BUILD_DIR)/LibPlayground.exe

#default
all : $(TARGET)

#linking
$(TARGET) : $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) 


%.o : %cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#cleaning lol
clean:
	rm -f $(TARGET) $(OBJ)