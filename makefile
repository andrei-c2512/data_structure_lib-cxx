#variables
CXX = g++

SRC_DIRS = src
BUILD_DIR = build

DEBUG_DIR = $(BUILD_DIR)/debug
RELEASE_DIR = $(BUILD_DIR)/release
INCLUDE_DIRS = include
LIB_DIR= lib


# if you add additional .lib , .a , include folders , please add the arguments here
COMMON_FLAGS=-std=c++20 -lstdc++ -static-libstdc++ -Wall -Wextra -MMD
DEBUG_FLAGS= $(COMMON_FLAGS) -g
RELEASE_FLAGS= $(COMMON_FLAGS) -O2


COMPILE_FLAGS=$(COMMON_FLAGS) -I$(INCLUDE_DIRS)

SRC = $(wildcard $(SRC_DIR)/*.cpp)
#for every cpp file , create an object
OBJS_DEBUG = $(foreach D,$(SRC_DIRS),$(patsubst %.cpp,%.o,$(subst $(D),$(DEBUG_DIR),$(wildcard $(D)/*.cpp))))
OBJS_RELEASE = $(foreach D,$(SRC_DIRS),$(patsubst %.cpp,%.o,$(subst $(D),$(RELEASE_DIR),$(wildcard $(D)/*.cpp))))

LIB_NAME_DEBUG=TinyDS-d.a
LIB_NAME_RELEASE=TinyDS.a

vpath %.cpp $(SRC_DIRS)

prepare:
	mkdir -p $(DEBUG_DIR)
	mkdir -p $(RELEASE_DIR)
	mkdir -p $(LIB_DIR)


clangd:
	@echo "Updating compile_flags.txt for clangd"
	@echo "$(COMPILE_FLAGS)" > temp.txt
	@cat temp.txt | tr ' ' '\n' > compile_flags.txt
	@rm temp.txt

$(DEBUG_DIR)/%.o : %.cpp
	$(CXX) $(DEBUG_FLAGS) $(COMPILE_FLAGS) -c $< -o $@

$(RELEASE_DIR)/%.o : %.cpp
	$(CXX) $(RELEASE_FLAGS) $(COMPILE_FLAGS) -c $< -o $@

lib-d : prepare clangd $(OBJS_DEBUG)
	@ar rcs $(LIB_DIR)/$(LIB_NAME_DEBUG) $(OBJS_DEBUG)


lib : prepare clangd $(OBJS_RELEASE)
	@ar rcs $(LIB_DIR)/$(LIB_NAME_RELEASE) $(OBJS_RELEASE)

#cleaning lol
clean:
	@rm -rf $(BUILD_DIR)


