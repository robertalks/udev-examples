CC = gcc
CFLAGS = -g -Wall

udev_examples:
	$(CC) $(CFLAGS) -o udev_example1 udev_example1.c -ludev
	$(CC) $(CFLAGS) -o udev_example2 udev_example2.c -ludev
	$(CC) $(CFLAGS) -o udev_example3 udev_example3.c -ludev

default: udev_examples

all: default

clean:
	rm -f udev_example1 udev_example2 udev_example3
