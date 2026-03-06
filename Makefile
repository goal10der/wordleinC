CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = wordle
PREFIX = /usr/local
# This is where the dictionary will live on the system
DATA_DIR = $(PREFIX)/share/wordle
DICT_PATH = $(DATA_DIR)/words.txt

all: $(TARGET)

# We pass the path to the C code using -D
$(TARGET): wordle.c
	$(CC) $(CFLAGS) -DWORDS_PATH=\"$(DICT_PATH)\" -o $(TARGET) wordle.c

# Local build (for testing in the current folder)
local:
	$(CC) $(CFLAGS) -DWORDS_PATH=\"words.txt\" -o $(TARGET) wordle.c

clean:
	rm -f $(TARGET)

install: $(TARGET)
	install -d $(DESTDIR)$(PREFIX)/bin
	install -d $(DESTDIR)$(DATA_DIR)
	install -m 755 $(TARGET) $(DESTDIR)$(PREFIX)/bin
	install -m 644 words.txt $(DESTDIR)$(DATA_DIR)/words.txt
	@echo "Successfully installed! You can now run 'wordle' from anywhere."

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	rm -rf $(DESTDIR)$(DATA_DIR)

run: local
	./$(TARGET)