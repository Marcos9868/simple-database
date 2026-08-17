CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =

INCLUDE_DIRS = $(shell find . -type d -not -path './.git*' -not -path './.ccls-cache*')
CFLAGS += $(addprefix -I, $(INCLUDE_DIRS))

TARGET = main

SRCS = $(shell find . -name '*.c' -not -path './.git*' -not -path './.ccls-cache*')
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

show:
	@echo "Source files:"
	@echo "$(SRCS)"
	@echo ""
	@echo "Object files:"
	@echo "$(OBJS)"
	@echo ""
	@echo "Include directories:"
	@echo "$(INCLUDE_DIRS)"
	@echo ""
	@echo "CFLAGS:"
	@echo "$(CFLAGS)"

.PHONY: clean show
