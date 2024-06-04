CC = gcc
CFLAGS = -Wall -O2 -lm
TARGET = donut
SRCS = donut.c
OBJS = $(SRCS:.c=.o)
PREFIX = /usr/local

# Include config.h for configuration options
CFLAGS += -I.

# Set CONFIG_ENABLE_SECOND_DONUT to 1 to enable second donut, or 0 to disable it
CONFIG_ENABLE_SECOND_DONUT = 1

ifeq ($(CONFIG_ENABLE_SECOND_DONUT), 1)
    CFLAGS += -DENABLE_SECOND_DONUT
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Depend on config.h to recompile when it changes
$(OBJS): config.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

install: $(TARGET)
	install -d $(PREFIX)/bin
	install -m 755 $(TARGET) $(PREFIX)/bin

uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)

.PHONY: all clean run install uninstall
