# =======================================================
#                    lolz
# =======================================================
# Directories
SRC_DIR := ./src
INC_DIR := ./inc
OBJ_DIR := ./obj
BIN_DIR := ./bin

# Help message
HELP_MESSAGE := "\
\nAcceptable targets:\n\
  \thelp  : Show this help message.\n\
  \tall   : Build all targets.\n\
  \tclean : Remove generated files.\n\
  \trun   : Run the program (executes 'all' implicitly).\n\n\
For example: 'make run'.\n\
Please note: the output of make commands are suppressed, meaning 'make run' won't show any of the build commands but will show binary output.\n\
"

# Targets
TARGET := $(BIN_DIR)/SampleQueue
DEPS := $(INC_DIR)/sampleQueue.h
OBJS := $(OBJ_DIR)/driver.o $(OBJ_DIR)/sampleQueue.o

# Phony
.PHONY: help all clean run

help:
	@echo -e $(HELP_MESSAGE)

all: $(TARGET)

# '$^' = All pre-requisite obj files, '$@' = target file itself (./bin/SampleQueue)
$(TARGET): $(OBJS) | $(BIN_DIR)
	@cc $^ -o $@

# '$<' = Pre-requisite source file (first pre-req).
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS) | $(OBJ_DIR)
	@cc -c $< -o $@

# In both cases above, '| $(DIR)' will establish the directory as a pre-requisite as well.
# The commands below are invoked, making the directories if they do not already exist.
# They are not counted in the normal pre-req order, so "$<" ignores when selecting pre-reqs.

$(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@



# Can also write 'dir/.*' to remove just contents. 
clean:
	@rm -rf $(BIN_DIR) $(OBJ_DIR)

run: $(TARGET)
	@$(TARGET)