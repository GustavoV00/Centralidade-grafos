C_FILES = $(wildcard src/*.c)
O_FILES = $(C_FILES:src/%.c=build/%.o)
CC = gcc
CFLAGS = -Wall -g

CC_VERBOSE = $(CC)
CC_NO_VERBOSE = @echo "Building $@..."; $(CC)

ifeq ($(VERBOSE),YES)
  V_CC = $(CC_VERBOSE)
  AT := 
else
  V_CC = $(CC_NO_VERBOSE)
  AT := @
endif

.PHONY: all clean
.DEFAULT: all

all: floodit

run:
	./floodit

anima:
	cat ./tests/exemplo_mapa_100_100_10.txt ./tests/exemplo_solucao_100_100_10.txt | ./tests/anima

floodit: $(O_FILES)
	$(V_CC) -o $@ $^

docs:
	doxygen configDoxygen

build:
	@mkdir -p build

build/%.o: src/%.c | build
	$(CC) -c $< -o $@

clean:
	@echo Removing object files
	$(AT)-rm -f $(O_FILES)
	@echo Removing application
	$(AT)-rm -f floodit
	@echo Removing build directory
	$(AT)-rm -rf build
	@echo Removing doxygen directory
	$(AT)-rm -rf doxygen
