CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = bsq
SRCS = main.c  parse_map_info.c operate_strings.c  validate_map.c make_square.c
OBJS = main.o  parse_map_info.o operate_strings.o  validate_map.o make_square.o

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
