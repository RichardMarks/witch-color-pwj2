CC ?= gcc
CFLAGS ?= $(shell pkg-config sdl2_image sdl2_ttf sdl2_mixer --cflags)
LDFLAGS ?= $(shell pkg-config sdl2_image sdl2_ttf sdl2_mixer --libs)

TARGET_EXEC ?= witch-color
BUILD_DIR ?= ./bin
SRC_DIRS ?= ./src
SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -g -D DEBUG
# CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -D PRODUCTION

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)
MKDIR_P ?= mkdir -p
