CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99

ifndef DAY
DAY_OF_MONTH = $(shell date +%d)
_DAY = day-$(DAY_OF_MONTH)
else
_DAY = day-$(DAY)
endif

ifndef PART
_PART = part1
else
_PART = part$(PART)
endif

BIN_DIR = bin
BIN = $(BIN_DIR)/$(_DAY)

all: $(BIN) run clean

$(BIN): $(BIN_DIR)
	$(CC) $(CFLAGS) ./$(_DAY)/$(_PART).c -o ./$(BIN)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

run:
	./$(BIN)
