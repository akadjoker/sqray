CC = g++
CFLAGS = -Wall -Wextra -g -fsanitize=address -fsanitize=undefined -fsanitize=leak -std=c++17
LDFLAGS = -lm
TARGET = main
QUICKJS_DIR = ../squirrel3


SOURCES = main.cpp


INCLUDES = -I$(QUICKJS_DIR)/include


LIBS = -L$(QUICKJS_DIR)/lib -lsqstdlib -lsquirrel -lraylib

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SOURCES) $(LIBS) $(LDFLAGS)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
