PROGRAM:=btdc
OBJS:=$(addsuffix .o,$(basename $(wildcard *.c))) libbtd/libbtd.so

CFLAGS=-g -Wextra -Wall -Werror -pedantic -std=gnu11
LDLIBS=-lsqlite3 -luuid

all: $(PROGRAM)

$(PROGRAM): $(HEADERS) $(OBJS)
	$(LINK.c)$(LDLIBS) $^ $(OUTPUT_OPTION)

libbtd/libbtd.so:
	make -C $(dir $@)

clean:
	$(RM) $(PROGRAM) $(OBJS) $(HEADERS)
	make -C libbtd
