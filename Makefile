# Makefile for compiling main.c linked with user.c

# Compiler options
CC = gcc
CFLAGS = -Wall -g
LIBS = -lncursesw -lmysqlclient
INCLUDES = -I./include

# Source directory
SRC_DIR = src

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = app

# Default target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

# Rule to compile .c to .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LIBS)

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

# Phony target to avoid conflicts with file names
.PHONY: clean
