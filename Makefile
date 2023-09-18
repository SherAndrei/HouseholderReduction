CC      := gcc
CFLAGS  := -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align \
		  -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security \
		  -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long  \
		  -Wcast-qual -Wno-suggest-attribute=format -Wpedantic -Werror=declaration-after-statement \
		  -Wmissing-declarations -Werror=strict-prototypes
LDFLAGS := # -fsanitize=address -fno-omit-frame-pointer -static-libasan
LIBS    := -lm

release: CFLAGS += -O3 -DNDEBUG
release: all

asan: CFLAGS += -fsanitize=address
asan: LDFLAGS += -fsanitize=address
asan: all

all: SolveLinearEquations.out

SolveLinearEquations.out: SolveLinearEquations.o HouseholderReduction.o
	$(CC) $^ -o $@ $(LIBS) $(LDFLAGS) $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean debug release

clean:
	rm -f *.out *.o

debug: CFLAGS += -g -O0
debug: all
