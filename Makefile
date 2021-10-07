CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = bsq
SRCS = start_processing.c operate_strings.c  validate_map.c make_square.c
OBJS = start_processing.o operate_strings.o  validate_map.o make_square.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.c%.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: all clean re
clean:
	-rm -f $(OBJS)

fclean:
	-rm -f $(TARGET) $(OBJS)

re: fclean all
