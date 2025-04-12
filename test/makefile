CXX=g++



SRC_DIRS = src
BUILD_DIR = build

DEBUG_DIR = $(BUILD_DIR)/debug
RELEASE_DIR = $(BUILD_DIR)/release
INCLUDE_DIRS = ../include include
TEST_LIB_DIR = ../lib
LIB_DIR= lib

COMMON_FLAGS= -std=c++20 -Wall -Wextra -lstdc++ -static-libstdc++ 
DEBUG_FLAGS= -g
RELEASE_FLAGS= -O2

LIB_RELEASE=TinyDS.a
LIB_DEBUG=TinyDS-d.a

COMPILE_FLAGS= $(addprefix -I,$(INCLUDE_DIRS)) -L$(TEST_LIB_DIR) -L$(LIB_DIR) $(COMMON_FLAGS) 

SRC = $(wildcard $(SRC_DIR)/*.cpp)

OBJS_DEBUG = $(foreach D,$(SRC_DIRS),$(patsubst %.cpp,%.o,$(subst $(D),$(DEBUG_DIR),$(wildcard $(D)/*.cpp))))
OBJS_RELEASE = $(foreach D,$(SRC_DIRS),$(patsubst %.cpp,%.o,$(subst $(D),$(RELEASE_DIR),$(wildcard $(D)/*.cpp))))


vpath %.cpp $(SRC_DIRS)

TARGET=Test.exe


set-up:
	git clone https://github.com/google/googletest
	mkdir googletest/build
	cd googletest/build && cmake ..
	mkdir -p lib
	mkdir -p include/googletest
	mkdir -p include/googlemock
	mv googletest/googletest/include/* include/googletest/ 
	mv googletest/googlemock/include/* include/googlemock/ 
	mv googletest/build/lib/* lib 
	rm -rf googletest
clean-set-up:
	rm -rf googletest
	rm -rf lib
	rm -rf include
prepare:
	mkdir -p $(DEBUG_DIR)
	mkdir -p $(RELEASE_DIR)

$(DEBUG_DIR)/%.o : %.cpp
	$(CXX) $(DEBUG_FLAGS) $(COMPILE_FLAGS) -c $< -o $@

$(RELEASE_DIR)/%.o : %.cpp
	$(CXX) $(RELEASE_FLAGS) $(COMPILE_FLAGS) -c $< -o $@

debug: $(OBJS_DEBUG) prepare
	$(CXX) $(DEBUG_FLAGS) $(COMPILE_FLAGS) $(OBJS_DEBUG) -l:$(LIB_DEBUG) -o $(DEBUG_DIR)/$(TARGET)

release: $(OBJS_RELEASE) prepare
	$(CXX) $(RELEASE_FLAGS) $(COMPILE_FLAGS) $(OBJS_RELEASE) -l:$(LIB_RELEASE) -o $(RELEASE_DIR)/$(TARGET)

clangd:
	@echo "Updating compile_flags.txt for clangd"
	@echo "$(COMPILE_FLAGS)" > temp.txt
	@cat temp.txt | tr ' ' '\n' > compile_flags.txt
	@rm temp.txt
clean:
	rm -rf $(BUILD_DIR)
files:
	@echo "Source files: $(SRC
