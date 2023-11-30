CC = gcc
CFLAGS = -Wall -Wextra -std=c99

ifndef DAY
DAY_OF_MONTH = $(shell date +%d)
DAY = day-$(DAY_OF_MONTH)
endif

BIN_DIR = bin
BIN = $(BIN_DIR)/$(DAY)

all: $(BIN) run clean

day-%: $(BIN_DIR)
	$(CC) $(CFLAGS) ./$(DAY)/main.c -o ./$(BIN)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

run:
	./$(BIN)
