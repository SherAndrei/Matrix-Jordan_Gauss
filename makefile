#Commands
MKDIR := mkdir
RMDIR := rm -rf

#Folders to make life easier
BIN 	:= ./bin
OBJ 	:= ./obj
INCLUDE := ./hdr
SRC 	:= ./src

#Compiler features
CC     := gcc
CFLAGS := -Werror -Wextra -Wpedantic -Wall -I$(INCLUDE)
LIBS   := -lm

#Variables
EXE  := $(BIN)/main
SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))

# $@ - the left side of the :
# $^ - the right side of the :
# $< - the first item in the dependencies list
# -c flag says to generate the object file

$(EXE): $(OBJS) | $(BIN)
	$(CC) $^ -o $@ $(LIBS)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BIN) $(OBJ):
	$(MKDIR) $@

.PHONY: clean debug release

clean:
	$(RMDIR) $(OBJ) $(BIN)

debug: CFLAGS += -g -O0
debug: $(EXE)
release: CFLAGS += -O3
release: $(EXE)