    TARGET_EXEC := hash_map_test
    
DBG_CFLAGS := -D DEBUG -g -Wall
LDFLAGS := -lm

BUILD_DIR := ./build
SRC_DIR := ./src

SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/utils/*.c) 
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEBUG_OBJS := $(SRCS:%=$(BUILD_DIR)/debug/%.o)
UTIL_OBJS := $(SRCS:%=$(BUILD_DIR)/utils/%.o)

RELEASE := $(BUILD_DIR)/$(TARGET_EXEC)
DEBUG := $(BUILD_DIR)/debug/$(TARGET_EXEC)

$(RELEASE): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) 
	
$(DEBUG): $(DEBUG_OBJS)
	$(CC) $(DEBUG_OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/debug/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(DBG_CFLAGS) -c $< -o $@

release: 
	$(RELEASE)

debug: $(DEBUG)
	$(DEBUG)

clean:
	rm -rf $(BUILD_DIR) $(DBGBUILD_DIR)

