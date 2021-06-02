CC = gcc
CFLAGS = -Wall -ansi
LDFLAGS = -lMLV -std=gnu99
EXEC = projet

all : $(EXEC)

projet: bin/main.o bin/ship.o bin/graph.o bin/menu.o bin/background.o bin/event_res.o
	$(CC) -o projet bin/main.o bin/ship.o bin/graph.o bin/menu.o bin/background.o bin/event_res.o $(CFLAGS) $(LDFLAGS)

bin/main.o: src/main.c
	$(CC) -c src/main.c -o bin/main.o $(CFLAGS) $(LDFLAGS)

bin/event_res.o: src/event_res.c
			$(CC) -c src/event_res.c -o bin/event_res.o $(CFLAGS) $(LDFLAGS)

bin/ship.o: src/ship.c
	$(CC) -c src/ship.c -o bin/ship.o $(CFLAGS) $(LDFLAGS)

bin/graph.o: src/graph.c header/ship.h header/background.h
	$(CC) -c src/graph.c -o bin/graph.o $(CFLAGS) $(LDFLAGS)

bin/menu.o: src/menu.c
	$(CC) -c src/menu.c -o bin/menu.o $(CFLAGS) $(LDFLAGS)

bin/background.o: src/background.c
	$(CC) -c src/background.c -o bin/background.o $(CFLAGS) $(LDFLAGS)

clean:
	rm -f bin/*.o

mrproper: clean
	rm -f $(EXEC)
