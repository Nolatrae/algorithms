CC = g++
CFLAGS = -std=c++20 -Wall -pedantic
SOURCES = main.cpp
CLASS = NDArray.h

ifeq ($(OS), Windows_NT)
	RM = del
	TARGET = main.exe
else
	RM = rm
	TARGET = main
endif

all:
	$(CC) $(CFLAGS) $(CLASS) -o $(TARGET) $(SOURCES)
clean:
	echo $(OS)
	$(RM) $(TARGET)

run: all
	$(TARGET)