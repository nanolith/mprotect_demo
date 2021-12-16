.PHONY: build clean

BUILD_DIR=$(PWD)/build
SRCDIR=$(PWD)/src
FIB_EXAMPLE_FORK_SOURCES=$(SRCDIR)/shared/example1_fib.c $(SRCDIR)/example_fork/main.c
FIB_EXAMPLE_FORK_OBJS=$(patsubst $(SRCDIR)/%.c,$(BUILD_DIR)/%.o,$(FIB_EXAMPLE_FORK_SOURCES))
FIB_EXAMPLE_CRASH_SOURCES=$(SRCDIR)/shared/example1_fib.c $(SRCDIR)/example_crash/main.c
FIB_EXAMPLE_CRASH_OBJS=$(patsubst $(SRCDIR)/%.c,$(BUILD_DIR)/%.o,$(FIB_EXAMPLE_CRASH_SOURCES))
FIB_EXAMPLE_FORK_CRASH_SOURCES=$(SRCDIR)/shared/example1_fib.c $(SRCDIR)/example_fork_crash/main.c
FIB_EXAMPLE_FORK_CRASH_OBJS=$(patsubst $(SRCDIR)/%.c,$(BUILD_DIR)/%.o,$(FIB_EXAMPLE_FORK_CRASH_SOURCES))

build: $(BUILD_DIR)/fib_example_fork $(BUILD_DIR)/fib_example_crash
build: $(BUILD_DIR)/fib_example_fork_crash

$(BUILD_DIR)/fib_example_fork: $(BUILD_DIR) $(FIB_EXAMPLE_FORK_OBJS)
	$(CC) -o $(BUILD_DIR)/fib_example_fork $(FIB_EXAMPLE_FORK_OBJS) \
	    -Wl,-Map=$(BUILD_DIR)/fib_example_fork.map

$(BUILD_DIR)/fib_example_crash: $(BUILD_DIR) $(FIB_EXAMPLE_CRASH_OBJS)
	$(CC) -o $(BUILD_DIR)/fib_example_crash $(FIB_EXAMPLE_CRASH_OBJS)

$(BUILD_DIR)/fib_example_fork_crash: $(BUILD_DIR) $(FIB_EXAMPLE_FORK_CRASH_OBJS)
	$(CC) -o $(BUILD_DIR)/fib_example_fork_crash $(FIB_EXAMPLE_FORK_CRASH_OBJS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/shared
	mkdir -p $(BUILD_DIR)/example_fork
	mkdir -p $(BUILD_DIR)/example_crash
	mkdir -p $(BUILD_DIR)/example_fork_crash

$(BUILD_DIR)/%.o: $(SRCDIR)/%.c
	$(CC) -g -I $(PWD)/include -c -o $@ $< 

clean:
	rm -rf $(BUILD_DIR)
