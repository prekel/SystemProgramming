# A basic makefile for "circle".

CC = gcc
CFLAGS = -Wall -g -std=c99
LDFLAGS = -lm

circle : circle.o circulararea.o
	$(CC) $(LDFLAGS) -o $@ $^

circle.o : circle.c
	$(CC) $(CFLAGS) -o $@ -c $<

circulararea.o: circulararea.c
	$(CC) $(CFLAGS) -o $@ -c $<