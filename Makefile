# The way of manage files and compile is inspired by an youtube video:https://www.youtube.com/watch?v=Dyz9O7s7B8w&t=1144s,which is a great. 

# pre
SRC_DIR = src
BUILD_DIR = ./
cc = clang
SRC_FILES =$(wildcard $(SRC_DIR)/*.c) 
EXE = gol
OBJ = $(SRC_FILES:.c=.o)
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -L/opt/homebrew/lib
COMPIER_FLAGS = -std=c99 -Wall -g
LINKER_FLAGS = -lSDL2 -lSDL2_image

# all:
# 	$(cc) $(COMPIER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) $(SRC_FILES) -o $(BUILD_DIR)$(EXE)
 
.c.o:
	$(cc) $(COMPIER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -c -o $@ $<

$(EXE): $(OBJ)
	$(cc) $(OBJ)  $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS)  -o $(BUILD_DIR)$(EXE) 


main.o:main.c state.h

clean:
	rm -f $(OBJ) $(EXE)