CC = gcc
CFLAGS = -Wall
SRCS = app.c welcomescreen.c show.c validations.c
OBJS = $(SRCS:.c=.o)
TARGET = BTS.exe

all: $(TARGET)

	$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)


