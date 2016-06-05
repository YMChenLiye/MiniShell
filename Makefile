.PHONY:clean
CC=gcc
CFLAGS=-Wall -g
BIN=minishell
OBJS=main.o parse.o init.o execute.o
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAFS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
