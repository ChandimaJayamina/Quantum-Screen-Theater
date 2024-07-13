# Define the compiler and compiler flags
CC = gcc
CFLAGS = -Wall -g

# Define the target executable
TARGET = app

# Define the source files and object files
SRCS = app.c welcomescreen.c show.c validations.c
OBJS = $(SRCS:.c=.o)

# Default target to build the program
all: $(TARGET)

# Rule to link the object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the build directory
clean:
	rm -f $(TARGET) $(OBJS)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
