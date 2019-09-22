LIBS = -lm
CC = gcc
GCPP = g++
CFLAGS = -g -pthread 
SOURCES = lrucache.cpp

TARGET = lrucache

default: all

all: clean $(TARGET) 

$(TARGET):
	$(GCPP) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LIBS)

clean:
	rm -rf $(TARGET)
	
