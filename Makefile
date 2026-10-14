CC = gcc
CFLAGS = -Wall -Wextra -O3

# Universelle Regel: Kompiliert jede .c-Datei in den build/-Ordner
build/%: %.c | build
	$(CC) $(CFLAGS) $< -o $@

# Erstellt den build-Ordner automatisch, falls er nicht existiert
build:
	mkdir -p build