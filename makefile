DEPS=scanner.h parser.h symboltable.h
OBJS=$(DEPS:.h=.o) main.o
CC=gcc
CFLAGS=-I. -Wall

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean: 
	rm main *.o
