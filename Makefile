# Defines name of program
TARGET := liblogger.a
TEST_TARGET := test

ifeq ($(TARGET_OS),windows)
	CC := x86_64-w64-mingw32-gcc
	AR := x86_64-w64-mingw32-ar
else
	CC := gcc
	AR := ar
endif

C_SRC := $(shell find src -name '*.c')
OBJ := $(patsubst src/%.c,build/%.o,$(C_SRC))

TEST_SRC := test.c
TEST_OBJ := build/test.o

CFLAGS := -Wall -Werror -Iinclude -std=c99 -MMD -MP -O2

all: $(TARGET)

$(TARGET): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test:
	$(CC) $(CFLAGS) test.c -L. -llogger -o $(TEST_TARGET)

-include $(OBJ:.o=.d)

clean:
	rm -rf build $(TARGET) $(TEST_TARGET)
